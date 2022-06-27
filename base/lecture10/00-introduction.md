# 第10回 デバイス遠隔操作

こちらを始める前に [第8回](../lecture08/00-introduction.md) の資料を元に、

- 8-1 デバイス準備、8-2 デバイスの動作理解 でデバイスがどう動くかの理解
- 8-5 Arduino IDE 準備、8-6 JSON ライブラリ準備、8-7 MQTT ライブラリ準備

を進めておきましょう。

## 10-1 デバイスの動作理解

今回のデバイス動作の大まかな流れを把握します。

![image](https://i.gyazo.com/1bf31bee68324ecbd6812944ea5c7bb8.jpg)

今回も [Arduino UNO Wi-Fi Rev.2](https://www.marutsu.co.jp/pc/i/33411858/) というデバイスを使っていきましょう。

![image](https://i.gyazo.com/ee0ed30e23bfc22144d6a52b775d5bfa.png)

Raspberry Pi の授業で使った LED を使ってデバイスと Node-RED を MQTT でやり取りする IoT の仕組みをつくり、LED の点灯を遠隔操作します。

流れを説明していきましょう。

![image](https://i.gyazo.com/3547abb9a8e161be2f8aeb7515185231.png)

まず、自分の MQTT Broker (beebotte) で今回の仕組みはやりとりします。Node-RED からは `{"led":1}` という JSON データをパブリッシュします。トピックは `ttc2022/res` です。

![image](https://i.gyazo.com/7a501696ac623e60721c1ee2259164ea.png)

デバイスは、トピック `ttc2022/res` をサブスクライブします。この `{"led":1}` という JSON データを受け取ると、デジタル出力 LED を点灯します。

## 10-2 回路説明

![image](https://i.gyazo.com/ee42f07ceb14057e909c25da3dbf0c97.jpg)

デバイスにつなげる回路や動作の説明をします。

### 10-2-1 LED

![image](https://i.gyazo.com/8cdd56ad2c48be155114c877a2ed03c1.jpg)

LED を用意しましょう。

![image](https://i.gyazo.com/c81f4f826b63f9142e459f6fa5db67a6.jpg)

Arduino 側ではデジタル出力で D2 を使います。

### 10-2-2 その他のパーツの準備

![image](https://i.gyazo.com/8cdd56ad2c48be155114c877a2ed03c1.jpg)

橙橙茶金の 330Ω の抵抗を準備します。

![image](https://i.gyazo.com/90847c9a6ad415233e4d220d284f9582.jpg)

- 長めの赤ケーブル
- 短めの黒ケーブル

を準備します。

![image](https://i.gyazo.com/68a50881c024eecc8296526abecf3583.jpg)

ブレッドボードも準備しましょう。

## 10-3 回路取り付け

デバイスにつなげる回路を取り付けます。

![image](https://i.gyazo.com/7a501696ac623e60721c1ee2259164ea.png)

今回 IoT の仕組みを作る前に、このエリア、つまり LED を点灯するデジタル出力の回路と動作だけで確認し成功させます。

これから IoT が加わり複雑な仕組みになるので、まず、電子工作としての回路と LED 点灯に絞って動作確認をしたい意図があります。

小さく進めて試していくのはプロトタイピングとしても大切なので、体験していきますしょう。

![image](https://i.gyazo.com/80b82460e3c83dacc7dad74aadd2d0a6.jpg)

Arduino の電源はまだ OFF にしておきましょう。

### 10-3-1 今回の回路図

![image](https://i.gyazo.com/a087e18b2b6add16ab4269cc6455b6e5.png)

このような回路で取り付けます。ブレッドボードの番号をよく見ながら取り付けてみましょう。

### 10-3-2 デジタル出力だけのプログラムを準備

Arduino にプログラムを書き込んでアナログ入力だけのチェックをしましょう。

メニュー > ファイル > 新規ファイル をクリックします。

![image](https://i.gyazo.com/feb362e740c05cdd469a96111abd9382.png)

新規ファイルを準備します。

以下のプログラムを新規ファイルにコピーアンドペーストしましょう。 `TTC-Demo-2022-LED-Blink-Simple` というファイル名で保存しましょう。

```c
int LED_PIN = 2;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  delay(1000);
}
```

保存できたら次へ進みます。

### 10-3-3 デジタル出力だけのプログラム

![image](https://i.gyazo.com/ee42f07ceb14057e909c25da3dbf0c97.jpg)

回路をつないだ Arduino UNO WiFi Rev2 を PC とつなぎます。

![image](https://i.gyazo.com/ca02fff1c8001e2bfe484ad5a294f917.png)

ボード設定を行い、書き込みボタンをクリックして書き込みます。実際に点滅するか確認しましょう。

### 10-3-4 デジタル出力だけのプログラムの簡単な説明

TODO : デジタル出力だけのプログラムの簡単な説明

## 10-4 プログラムの準備

いよいよ、Node-RED から遠隔操作でデバイスの LED を点灯する IoT の仕組みです。

今回のプログラムを準備します。

### 10-4-1  新規ファイル準備

メニュー > ファイル > 新規ファイル をクリックします。

![image](https://i.gyazo.com/feb362e740c05cdd469a96111abd9382.png)

新規ファイルを準備します。

### 10-4-2 プログラムをコピーアンドペーストして保存

以下のプログラムを新規ファイルにコピーアンドペーストしましょう。

そして、`TTC-Demo-2022-LED-Blink-MQTT` というファイル名で保存しましょう。

```c
// WiFiNINA ライブラリ
#include <SPI.h>
#include <WiFiNINA.h>
 
// MQTT をつなぐためのライブラリ
// 今回追加インストールする
#include <PubSubClient.h>  // インストールすれば色がつく
// JSON を扱いやすくするライブラリ
#include <ArduinoJson.h> // こちらは色がついてなくてOK
 
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

// LED のピン番号
int LED_PIN = 2;
 
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

  // LED ピンを出力にして指定
  pinMode(LED_PIN, OUTPUT);
 
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
      doc["led"] = 0;
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
  const int led = jsonData["led"];
 
  // データの表示
  Serial.print("led = ");
  Serial.println(led);

  // led の JSON データの 1 か 0 によって点灯が変わる
  if(led == 0){
    digitalWrite(LED_PIN, LOW);
    Serial.print("LOW");
  } else if(led == 1){
    digitalWrite(LED_PIN, HIGH);
    Serial.print("HIGH");
  }
 
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

## 10-5 プログラムの設定

今回のプログラム内の設定をします。

### 10-5-2 Wi-Fi の設定

```c
// Wi-FiのSSID
char *ssid = "Wi-FiのSSID";
// Wi-Fiのパスワード
char *password = "Wi-Fiのパスワード";
```

前章と同じく Wi-Fi の設定を行います。

### 10-5-3 自分の MQTT ブローカーを設定

Beebotte については、今回は自分の MQTT ブローカーを使って行いましょう。

![image](https://i.gyazo.com/6054873655c282ccdb7c38e98a97942d.png)

自分の Beebotte にアクセスしてトークン設定を準備しましょう。

```c
// 今回使いたい Beebotte のブローカーのアドレス
const char *mqttEndpoint = "mqtt.beebotte.com";
// 今回使いたい Beebotte のポート
const int mqttPort = 1883;
// 今回使いたい Beebotte のユーザー名
const char *mqttUsername = "今回使いたい Beebotte のユーザー名";
// 今回使いたい Beebotte のパスワード
const char *mqttPassword = "";
```

仮に `token_1234567890` の場合は `const char *mqttUsername = "今回使いたい Beebotte のユーザー名";` の部分を `const char *mqttUsername = "token_1234567890";` と変更します。

## 10-6 メインプログラムの簡単な説明

今回のメインプログラムの簡単な説明です。

TODO : メインプログラムの簡単な説明

## 10-7 プログラムの書き込み

Arduino IDE にプログラムを書き込みます。

![image](https://i.gyazo.com/7af357caade502812ae210732cec208a.png)

Arduino UNO WiFi Rev2 へ書き込む前にシリアルモニタを起動しておきましょう。今回は設定値は 9600 bps です。

![image](https://i.gyazo.com/ca02fff1c8001e2bfe484ad5a294f917.png)

ボード設定を行い、書き込みボタンをクリックして書き込みます。

## 10-8 プログラムの動作確認 Arduino IDE

プログラムと回路の動作を Arduino IDE で確認します。

![image](https://i.gyazo.com/3ef6f3661c136eba28f0fb2d2bd6fc57.png)

まず、Wi-Fi がつながり MQTT ブローカーに接続されていることが確認できます。

![image](https://i.gyazo.com/99b38ae64663dd0b440f8c2ce2496c32.png)

このように、接続時に `{"message":"Connected","led":0}` というデータが送られて、自分で自分自身の値を受け取って LED が OFF になり、データを待ち受ける状態になります。

## 10-9 プログラムの動作確認 デバイス＋ Node-RED

プログラムと回路の動作を Node-RED で確認します。

![image](https://i.gyazo.com/4aa1fe7158015d1c9b318092665cd52f.png)

以前の授業で使った ttc2022/res を受信する inject ノードに mqtt out ノードをつないだフローで確認します。

### 10-9-1 MQTT ブローカーを設定

![image](https://i.gyazo.com/e7238113227430c05fecbda952bea439.png)

mqtt out ノードをダブルクリックして、プロパティを表示します。サーバの設定が `My MQTT Broker` と `Teacher MQTT Broker` が、授業中にすでに設定されていますが、自分の環境がそうなっているか確認します。

![image](https://i.gyazo.com/ac052bdb1dc3f73fcc595cdfc75bcde0.png)

その上で `My MQTT Broker` を選択します。設定できたら、完了をクリックします。

![image](https://i.gyazo.com/943b4630e0163a28b3c7973b4d060418.png)

ワークスペースまで戻ったらデプロイをクリックします。

### 10-9-2 My MQTT Broker の設定も確認しておきましょう

![image](https://i.gyazo.com/ac052bdb1dc3f73fcc595cdfc75bcde0.png)

`My MQTT Broker` を選択したとき、時間があれば、設定で自分の Beebotte のトークンが設定されているかも確認しましょう。

![image](https://i.gyazo.com/14c7bb157dd46a71ef647fb72baf16aa.png)

ここのユーザ名が自分の Beebotte のトークンになっていて、Arduino のプログラムの方と同じであればうまくうごくはずです。

### 10-9-3 inject ノード設定

![image](https://i.gyazo.com/4193ac6d94824e07868cf20c1142eee3.png)

inject ノードをダブルクリックしてプロパティを表示します。

![image](https://i.gyazo.com/6091b76931c3fb459eb47ec0906ec54f.png)

- 名前
  - ON
- msg.payload の設定
  - データタイプ
    - JSON
  - 内容
    - `{"led":1}`

と設定します。

![image](https://i.gyazo.com/943b4630e0163a28b3c7973b4d060418.png)

デプロイします。

## 10-10 遠隔操作実践

Node-RED からデバイスを遠隔操作します。

![image](https://i.gyazo.com/198cb7abd7b3a73a03fd6ae71535f77c.png)

データを送ってみて点灯するか inject ノードでデータを送って確かめてみましょう。

![image](https://i.gyazo.com/ee42f07ceb14057e909c25da3dbf0c97.jpg)

このように点灯します！

![image](https://i.gyazo.com/2219ead6f92747fe2d78f2c69930da46.png)

シリアルモニタでもデータ受信が確認できます。

### 10-10-1 OFF する仕組みも加えよう

![image](https://i.gyazo.com/e8dfda4ea5f605616bcf424d69f529f2.png)

つづいて inject ノードをもう一つ加えます。

![image](https://i.gyazo.com/08f68b8d9b67ad0c67051e22cd6ee563.png)

追加した inject ノードは

- 名前
  - OFF
- msg.payload の設定
  - データタイプ
    - JSON
  - 内容
    - `{"led":0}`

と設定します。

![image](https://i.gyazo.com/943b4630e0163a28b3c7973b4d060418.png)

デプロイします。

![image](https://i.gyazo.com/41e47b15164d994a40d7904d5206de45.jpg)

このように消灯します！