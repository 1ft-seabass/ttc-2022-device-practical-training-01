# サーボを動かしてみよう

![image](https://i.gyazo.com/6159ef068fb9eada7a5c954f5ceef0fc.jpg)

## 10-1-1 パーツの準備

![image](https://i.gyazo.com/d01b83c7d7f8781c0a9a1f937918fbbb.jpg)

サーボを用意します。

![image](https://i.gyazo.com/57ee7573918cf47c8143e367a11fed7e.jpg)

![image](https://i.gyazo.com/4fd96f1ab56d17be72321ae58a295ba7.jpg)

- 長めの黄ケーブル
- 長めの赤ケーブル
- 短めの黒ケーブル

を準備します。

## 10-1-2 サーボとケーブルをつなぎます

![image](https://i.gyazo.com/2104f01b46c0a4c3ce97c67404db5849.jpg)

サーボ側の穴を確認します。

![image](https://i.gyazo.com/6159ef068fb9eada7a5c954f5ceef0fc.jpg)

ケーブルを差し込みます。

- サーボ側の黄色ケーブルがある穴
  - 黄色ケーブル
- サーボ側の赤ケーブルがある穴
  - 赤ケーブル
- サーボ側の茶色ケーブルがある穴
  - 黒ケーブル

![image](https://i.gyazo.com/409275787ee28b516e0adb5bcbf6d59b.jpg)

サーボの部品を用意します。

![image](https://i.gyazo.com/4e8facd18d0200a75814856648462e43.jpg)

サーボにはめこみます。

## 10-1-3 回路図

こちらの回路図に合わせてとりつけます。

![image](https://i.gyazo.com/c06acb72b4ac63692030e7146eba5aba.png)

## 10-1-4  ソースコード1

Arduino IDE でファイルを新規作成して以下のソースコードをコピーアンドペーストして `TTC-Demo-2022-Servo-Simple` で保存。

```c
#include <Servo.h>

Servo myservo;

void setup() {
  // 今回は2ピン
  myservo.attach(2);
}

void loop() {
  myservo.write(0);
  delay(5000);
  myservo.write(180);
  delay(5000);
  myservo.write(90);
  delay(5000);
}
```

書き込んで、サーボが回るか定期チェックします。

## 10-1-5 ソースコード2

Arduino IDE でファイルを新規作成して以下のソースコードをコピーアンドペーストして `TTC-Demo-2022-Servo-MQTT` で保存。

```c
// WiFiNINA ライブラリ
#include <SPI.h>
#include <WiFiNINA.h>
 
// MQTT をつなぐためのライブラリ
// 今回追加インストールする
#include <PubSubClient.h>  // インストールすれば色がつく
// JSON を扱いやすくするライブラリ
#include <ArduinoJson.h> // こちらは色がついてなくてOK

// Servo の宣言
#include <Servo.h>
 
// Wi-FiのSSID
char *ssid = "Wi-FiのSSID";
// Wi-Fiのパスワード
char *password = "Wi-Fiのパスワード";

// 今回使いたい Beebotte のブローカーのアドレス
const char *mqttEndpoint = "mqtt.beebotte.com";
// 今回使いたい Beebotte のポート
const int mqttPort = 1883;
// 今回使いたい Beebotte のユーザー名
const char *mqttUsername = "今回使いたい Beebotte のユーザー名";
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

// Servo のピン番号
int SERVO_PIN = 2;

// Servo
Servo myservo;
 
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

  // Servo 設定
  myservo.attach(SERVO_PIN);
 
  delay(2000);
 
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
      doc["servo"] = 0;
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
 
// JSON を格納する StaticJsonDocument を準備
StaticJsonDocument<2048> jsonData;
 
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
  const int servo = jsonData["servo"];
 
  // データの表示
  Serial.print("servo = ");
  Serial.println(servo);

  // サーボの角度に反映
  myservo.write(servo);
 
}
 
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

Wi-Fi と自分の MQTT ブローカーへの設定を行って書き込みます。

## 10-1-6 Node-RED の変更

inject ノードの送るデータを変更してみましょう。

![image](https://i.gyazo.com/83e9a71f40ab25d6d3272a4f56b270bd.png)

servo という値にして、角度を整数で送ってあげます。0～180まで操作できます。