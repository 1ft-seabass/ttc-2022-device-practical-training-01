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
```

ここまでは、以後使う様々な設定を変数で宣言しています。

```c
// JSON 送信時に使う buffer
char pubJson[255];
```

このあと JSON のオブジェクトを文字列に格納するための変数として pubJson を宣言しています。


```c
// PubSubClient まわりの準備
WiFiClient httpClient;
PubSubClient mqttClient(httpClient);
```

MQTT まわりのやり取りを行う PubSubClient を準備しています。`WiFiClient httpClient;` によって、WiFi 接続後に指定されたインターネットIPアドレスとポートに接続できるクライアントを作成します。何かしらのつなぐためのクライアントとしての準備です。

`PubSubClient mqttClient(httpClient);` によって、PubSubClient が MQTT に特化して MQTT クライアントを準備します。以後、`mqttClient` という変数で MQTT まわりのやり取りを行います。

## 起動時に動作する setup 関数

起動時に動作する setup 関数の前半では、おもに Wi-Fi の接続をしています。

```c
void setup() {
  Serial.begin(9600);
```

Arduino 上で Serial 関数の Serial.begin によってボーレート（1秒間にどれくらい送れるかというデータ転送レートのbps値）に合わせておくとデータが受信できます。今回は 9600 bps です。

```c
  // WiFi 接続開始
  Serial.print("WiFi Connecting WPA SSID: ");
  Serial.println(ssid);
```

シリアルモニタ上で `WiFi Connecting WPA SSID: ` という文字列を出した後、今回つなぐ Wi-Fi の SSID を表示してチェックできるようにしています。

```c
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    // Connect to WPA/WPA2 network:
    WiFi.begin(ssid, password);
    Serial.print(".");
  }
```

`WiFi.status()` が `WL_CONNECTED` という接続成功の値になるまで待つことで、Wi-Fi の接続を待っています。

`WiFi.begin(ssid, password);` の部分で、WPA/WPA2 の Wi-Fi ネットワークへつないでいます。`Serial.print(".");` でつながるまで、ずっと `..........` とピリオドを出し続けることで読み込み中を表現しています。

```c
  // 接続完了メッセージ
  Serial.print("WiFi Connected");
  printCurrentNet();
  printWifiData();
 
  delay(2000);
```

接続完了後に接続した現在のネットワーク状況を表示します。この関数はプログラムの後半に記述されているので、のちほど紹介します。

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
```

まず setup 後半では、PubSubClient の mqttClient ので、MQTT の接続先設定・MQTT のデータを受け取った時（購読時）の動作を設定をした後に、実際の MQTT の接続するために `mqttConnect` 関数を呼び出します。

```c
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
```

ここはやや長めに書いてありますが MQTT クライアントが自分の名前をクライアント ID として送受信時に宣言していますが、同じ MQTT ブローカー上で名前が被ると、誰が誰のデータをやり取りしているか判断できず混乱するのでランダムな値を生成するようにしています。

この名前の前半の固定値は `char *deviceID = "UNO-Rev2-WiFi";` として上部の方で設定しているので、可能であれば、`"UNO-Rev2-WiFi-seigo-328y69"` のように自分の名前＋ランダムっぽい値を自分で加えると、より被りにくい名前になるのでおススメです。

ちなみに、Node-RED の場合は、気を効かせてクライアント IDを勝手にランダムのIDにしてくれています。

```c
  // 接続されるまで待ちます
  while (!mqttClient.connected()) {
    if (mqttClient.connect(clientID,mqttUsername,mqttPassword)) {
      Serial.println("- MQTT Connected.");
```

`while (!mqttClient.connected()) {` によって MQTT ブローカーにつながるまで待っています。実際の接続は `mqttClient.connect(clientID,mqttUsername,mqttPassword)` で行っています。

```c
      // subTopic 変数で指定されたトピックに向けてデータを送ります
      int qos = 0;
      mqttClient.subscribe(subTopic, qos);
      Serial.println("- MQTT Subscribe start.");
      Serial.println(subTopic);
```

subTopic 変数で指定されたトピックに向けてデータを送っています。`mqttClient.subscribe(subTopic, qos);` によって実際には設定しています。

MQTT メッセージを受け取るトピックは `char *subTopic = "ttc2022/res";` として上部の方で設定しています。

```c
      // 初回データ送信 publish ///////////
      // データ送信のための JSON をつくる
      DynamicJsonDocument doc(1024);
      doc["message"] = "Connected";
      // pubJson という変数に JSON 文字列化されたものが入る
      serializeJson(doc, pubJson);
      // pubTopic 変数で指定されたトピックに向けてデータを送ります
      mqttClient.publish(pubTopic, pubJson);
```

こちらは、接続したての時に初回データ送信を行ってデータ送信や接続チェックをしやすくしています。

接続成立後に、すぐ MQTT ブローカに一度 `{"message":"Connected"}` という JSON データを送っています。

`// 初回データ送信 publish ///////////` 以降がデータ送っています。

以後は、

- DynamicJsonDocument という ArduinoJSON から提供された型でこれから作成する JSON データのベースとなる doc という変数を宣言
- doc に message という値を設定し `Connected` というデータを入れる
- serializeJson で doc を解析することで `{"message":"Connected"}` というデータとなる
- serializeJson の第 2 引数で、事前に pubJson と宣言した JSON 送信時に使う buffer 型に `{"message":"Connected"}` を渡す
- `mqttClient.publish(pubTopic, pubJson);` で第 1 引数で pubTopic 変数で指定されたトピック ttc2022/res を指定していて、トピックに向けて `{"message":"Connected"}` のデータを送っています

ということを行っています。

```c
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

この部分は、接続されるまで、MQTT 接続エラーの場合はつながるまで 5 秒ごとに再接続を繰り返しています。

## MQTT データ受信時の処理 mqttCallback

mqttCallback は MQTT データ受信時の処理を行っています。MQTT データ受信時のみ、実行されるものです。

```c
// JSON を格納する StaticJsonDocument を準備
StaticJsonDocument<2048> jsonData;
```

ArduinoJSON の持つ StaticJsonDocument という型で JSON を格納する変数を準備します。

```c 
// MQTT のデータを受け取った時（購読時）の動作を設定
void mqttCallback (char* topic, byte* payload, unsigned int length) {
```

mqttCallback は setup 関数の `mqttClient.setCallback(mqttCallback);` で、MQTT のデータを受け取った時（購読時）の動作として設定されています。

- topic
  - MQTT のデータを受け取った時のトピック
- payload
  - 受け取ったデータが byte データで来る
  - 実際に使うときは、char や String などに変換して使う
- length
  - 受け取ったデータの長さ

という内容を受け取っています。

```c
  // データ取得
  String str = "";
  Serial.print("Received. topic=");
  Serial.println(topic);
  for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
      str += (char)payload[i];
  }
  Serial.print("\n");
```

上記の引数を元に for ループを回してデータをつないで、受け取ったデータを一つの変数 str に集めます。

以後は受け取った文字列を ArduinoJSON を使って JSON データに解析（デシリアライズ）します。

```c
  // 来た文字列を JSON 化して扱いやすくする
  // 変換する対象は jsonData　という変数
  DeserializationError error = deserializeJson(jsonData, str);
```

`deserializeJson(jsonData, str);` で受け取った文字列をJSON データに解析（デシリアライズ）します。もし、JSON 解析がエラーがでる場合は `DeserializationError error` が受け止めます。

```c
  // JSON パースのテスト
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
```

`DeserializationError error` をみて JSON の解析の成功をチェックします。うまくいけば、このあとに進みます。

```c
  // 以下 jsonData 内が JSON として呼び出せる
  Serial.println("MQTT Subscribed data");
```

ここが呼び出せるということは、うまく JSON が受け取れています。

```c
  // データの取り出し
  // https://arduinojson.org/v6/example/parser/
  const char* message = jsonData["message"];
```

たとえば、`{"message":"Connected"}` のデータが受け取れていると ArduinoJSON によって解析され `message` には `Connected` の文字列が取得できます。

```c 
  // データの表示
  Serial.println(message);
 
}
```

最後に、うまく JSON 内の message 値が取得出来ているかをシリアルモニタに表示します。

## 起動後、動作し続ける loop 関数

loop 関数は MQTT 接続の維持をしています。SubPubClient ライブラリの処理が中心です。

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

接続の維持は `mqttClient.loop();` です。

常に `mqttClient.connected()` で接続状態をチェックして、もし切断されたら `mqttConnect` MQTT 接続関数を実行して復帰できるようにする対応をしています。

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
