# メインプログラムの流れ

## まずはライブラリの準備

```c
// WiFiNINA ライブラリ
#include <SPI.h>
#include <WiFiNINA.h>
 
// MQTT をつなぐためのライブラリ
// 今回追加インストールする
#include <PubSubClient.h>  // インストールすれば色がつく
// JSON を扱いやすくするライブラリ
#include <ArduinoJson.h> // こちらは色がついてなくてOK
```

## Wi-Fi まわりの設定

```c
// Wi-FiのSSID
char *ssid = "<Wi-FiのSSID>";
// Wi-Fiのパスワード
char *password = "<Wi-Fiのパスワード>";
```

## MQTT まわりの設定

```c
// 今回使いたい Beebotte のブローカーのアドレス
const char *mqttEndpoint = "mqtt.beebotte.com";
// 今回使いたい Beebotte のポート
const int mqttPort = 1883;
// 今回使いたい Beebotte のユーザー名
const char *mqttUsername = "<今回使いたい Beebotte のユーザー名>";
// 今回使いたい Beebotte のパスワード
const char *mqttPassword = "";

// デバイスID
// デバイスIDは機器ごとにユニークにします
// YOURNAME を自分の名前の英数字に変更します
// デバイスIDは同じMQTTブローカー内で重複すると大変なので、後の処理でさらにランダム値を付与してますが、名前を変えるのが確実なので、ちゃんと変更しましょう。
char *deviceID = "UNO-Rev2-WiFi";
 
// MQTT メッセージをに知らせるトピック
char *pubTopic = "ttc2022/res";
 
// MQTT メッセージを受け取るトピック
char *subTopic = "ttc2022/res";
 
// JSON 送信時に使う buffer
char pubJson[255];
 
// PubSubClient まわりの準備
WiFiClient httpClient;
PubSubClient mqttClient(httpClient);
 
```

## 起動時に動作する setup 関数

起動時に動作する setup 関数

```c
void setup() {
  Serial.begin(9600);
 
  // WiFi 接続開始
  Serial.print("WiFi Connecting WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    // Connect to WPA/WPA2 network:
    WiFi.begin(ssid, password);
    Serial.print(".");
  }
 
  // 接続完了メッセージ
  Serial.print("WiFi Connected");
  printCurrentNet();
  printWifiData();
 
  delay(2000);
```

### MQTT に接続する setup 後半と mqttConnect

setup 後半は Wi-Fi の接続ができて MQTT ブローカーに接続します。

```c
 
  // MQTT の接続先設定
  mqttClient.setServer(mqttEndpoint, mqttPort);
  // MQTT のデータを受け取った時（購読時）の動作を設定
  mqttClient.setCallback(mqttCallback);
  // MQTT の接続
  mqttConnect();
 
}

void mqttConnect() {
 
  // MQTT clientID のランダム化（名称重複対策）
  char clientID[40] = "clientID";
  String rndNum = String(random(0xffffff), HEX);
  String deviceIDRandStr = String(deviceID);
  deviceIDRandStr.concat("-");
  deviceIDRandStr.concat(rndNum);
  deviceIDRandStr.toCharArray(clientID, 40);
  Serial.println("[MQTT]");
  Serial.println("");
  Serial.println("- clientID ");
  Serial.println(clientID);
 
  // 接続されるまで待ちます
  while (!mqttClient.connected()) {
    if (mqttClient.connect(clientID,mqttUsername,mqttPassword)) {
      Serial.println("- MQTT Connected.");
 
      // subTopic 変数で指定されたトピックに向けてデータを送ります
      int qos = 0;
      mqttClient.subscribe(subTopic, qos);
      Serial.println("- MQTT Subscribe start.");
      Serial.println(subTopic);
 
      // 初回データ送信 publish ///////////
      // データ送信のための JSON をつくる
      DynamicJsonDocument doc(1024);
      doc["message"] = "Connected";
      // pubJson という変数に JSON 文字列化されたものが入る
      serializeJson(doc, pubJson);
      // pubTopic 変数で指定されたトピックに向けてデータを送ります
      mqttClient.publish(pubTopic, pubJson);
    } else {
      // MQTT 接続エラーの場合はつながるまで 5 秒ごとに繰り返します
      Serial.print("Failed. Error state=");
      Serial.println(mqttClient.state());
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

```

## MQTT データ受信時の処理 mqttCallback

mqttCallback は MQTT データ受信時の処理を行っています。MQTT データ受信時のみ、実行されるものです。

```c
// JSON を格納する StaticJsonDocument を準備
StaticJsonDocument<2048> jsonData;
```

```c 
// MQTT のデータを受け取った時（購読時）の動作を設定
void mqttCallback (char* topic, byte* payload, unsigned int length) {
 
  // データ取得
  String str = "";
  Serial.print("Received. topic=");
  Serial.println(topic);
  for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
      str += (char)payload[i];
  }
  Serial.print("\n");
 
  // 来た文字列を JSON 化して扱いやすくする
  // 変換する対象は jsonData　という変数
  DeserializationError error = deserializeJson(jsonData, str);
 
  // JSON パースのテスト
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
 
  // 以下 jsonData 内が JSON として呼び出せる
  Serial.println("MQTT Subscribed data");
 
  // データの取り出し
  // https://arduinojson.org/v6/example/parser/
  const char* message = jsonData["message"];
 
  // データの表示
  Serial.println(message);
 
}
```

## 起動後、動作し続ける loop 関数

loop 関数は MQTT 接続の維持をしています。SubPubClient ライブラリの処理が中心です。

接続の維持は `mqttClient.loop();` です。

常に `mqttClient.connected()` で接続状態をチェックして、もし切断されたら `mqttConnect` MQTT 接続関数を実行して復帰できるようにする対応をしています。

```c

// 常にチェックして切断されたら復帰できるようにする対応
void mqttLoop() {
  if (!mqttClient.connected()) {
      mqttConnect();
  }
  mqttClient.loop();
}
 
void loop() {
  // 常にチェックして切断されたら復帰できるようにする対応
  mqttLoop();
}
```

## Wi-Fi 接続時のシリアルコンソール通知まわり

WiFiNINA ライブラリの初期プログラムにもついている、Wi-Fi 接続時の基本的なコード。

Wi-Fi でつながった IP アドレスや MAC アドレスなどを取得して表示。

```c
void printWifiData() {
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);
 
  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  printMacAddress(mac);
}
 
void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
 
  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  printMacAddress(bssid);
 
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);
 
  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}
 
void printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    if (i > 0) {
      Serial.print(":");
    }
  }
  Serial.println();
}
```
