# 第9回 デバイスセンサーデータ送信

## デバイスの動作理解

今回のデバイス動作の大まかな流れを把握します。

![image](https://i.gyazo.com/7a1a641d071ac50041f9e649ffd693c3.jpg)

Raspberry Pi の授業で使った CDS セルを使って光の明るさを取得する明るさセンサーを使ってデバイスと Node-RED を MQTT でやり取りする IoT の仕組みをつくります。

![image](https://i.gyazo.com/6cd4418770feca26bb7f02648a2ed0b1.png)

流れを説明していきましょう。

![image](https://i.gyazo.com/1fd1cde56f782ffca869ebf28a0c9152.png)

CDS セルを使って光の明るさを取得する明るさセンサーが周辺の明るさを取得します。

![image](https://i.gyazo.com/3ea8931c9f20653b167af6146779b306.png)

明るさセンサーは CDS セルを含めた回路によって明るさを電流の量で検出します。デバイスは、この電流の量をアナログ入力で受け取ります。

![image](https://i.gyazo.com/07d7947ae1bfeb20841e4acf717af326.png)

デバイスは、アナログ入力による値を Wi-Fi と通じて自分の MQTT ブローカーにパブリッシュします
- WiFiNINA で Wi-Fi に接続し、PubSubClient で MQTT ブローカーに接続します
- トピックは ttc2022/res です

![image](https://i.gyazo.com/85591278164da323a69b8356c2b7a401.png)

パブリッシュする際、Node-RED でデータを扱いやすくするために、今回のデータを `{"light":288}` というJSON データを作成して送ります。
  - JSON データは ArduinoJSON で作成します

![image](https://i.gyazo.com/c09038cc4978b636590793026b6d001b.png)

みなさんの Node-RED ではトピック ttc2022/res をサブスクライブしてデータ受信を待ちます
- 無事、データがやりとりできると Node-RED は明るさの値が受信できます

## 回路説明

デバイスにつなげる回路や動作の説明をします。

### 光に反応する CDS セル

![image](https://i.gyazo.com/5aa4063874881b374c954d277fc955c2.jpg)

CDS セルを用意しましょう。このパーツは、光に反応し電気の流れる量つまり抵抗が変わります。

- 暗いとき
  - 抵抗が少なくなり、電流が多くなります。
- 明るいとき
  - 抵抗が多くなり、電流が少なくなります。

CDS セルは極性はなく電流の流れを気にせず取り付けることができます。

![image](https://i.gyazo.com/781bcceb71909617af778811d4287718.jpg)

Arduino 側では電流の流れを検知するアナログ入力の A0 を

### その他のパーツの準備

![image](https://i.gyazo.com/930c0851f0bf6928e486ef08b74fb850.jpg)

茶黒橙金の 10KΩ の抵抗を準備します。

![image](https://i.gyazo.com/4fd96f1ab56d17be72321ae58a295ba7.jpg)

- 長めの黄ケーブル
- 長めの赤ケーブル
- 短めの黒ケーブル

を準備します。

![image](https://i.gyazo.com/68a50881c024eecc8296526abecf3583.jpg)

ブレッドボードも準備しましょう。

## 回路取り付け

デバイスにつなげる回路を取り付けます。

![image](https://i.gyazo.com/8ea51c32f2f926e87d1162febbdee461.png)

今回 IoT の仕組みを作る前に、このエリア、つまりアナログ入力の回路と動作だけで確認し成功させます。

これから IoT が加わり複雑な仕組みになるので、まず、電子工作としての回路とセンサー値取得に絞って動作確認をした意図があります。小さく進めて試していくのはプロトタイピングとしても大切なので、体験していきますしょう。

![image](https://i.gyazo.com/80b82460e3c83dacc7dad74aadd2d0a6.jpg)

Arduino の電源はまだ OFF にしておきましょう。

### 今回の回路図

![image](https://i.gyazo.com/723e444f9a184cb6bf5a6a28a1828a8b.png)

このような回路で取り付けます。ブレッドボードの番号をよく見ながら取り付けてみましょう。

### アナログ入力だけのチェック

Arduino にプログラムを書き込んでアナログ入力だけのチェックをしましょう。

メニュー > ファイル > 新規ファイル をクリックします。

![image](https://i.gyazo.com/feb362e740c05cdd469a96111abd9382.png)

新規ファイルを準備します。

以下のプログラムを新規ファイルにコピーアンドペーストしましょう。

```c
int sensorPin = A0;
int sensorValue = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Analog Read");
}

void loop() {
  sensorValue = analogRead(sensorPin);
  Serial.print("light = ");
  Serial.println(sensorValue);
  delay(1000);
}
```

こちらをコピーアンドペーストできたら `TTC-Demo-2022-AnalogInput-Light-Simple` というファイル名で保存しましょう。

![image](https://i.gyazo.com/fa7747862927454bf64c9866d5cc1fa7.jpg)

回路をつないだ Arduino UNO WiFi Rev2 を PC とつなぎます。

![image](https://i.gyazo.com/7af357caade502812ae210732cec208a.png)

Arduino UNO WiFi Rev2 へ書き込む前にシリアルモニタを起動しておきましょう。今回は設定値は 9600 bps です。

![image](https://i.gyazo.com/ca02fff1c8001e2bfe484ad5a294f917.png)

ボード設定を行い、書き込みボタンをクリックして書き込みます。

![image](https://i.gyazo.com/9e39635ab0972f0739d0ea18dd550036.png)

シリアルコンソールで動作するか確認しましょう。

![image](https://i.gyazo.com/219c1d17523fa694dbbe75e98d0fe429.jpg)

手をかぶせて暗くして変化をみてみましょう。

![image](https://i.gyazo.com/9daa3fd074a9de0ba7d37ae4d824b8ce.png)

このように変化します。

### アナログ値取得プログラムの簡単な説明

```c
int sensorPin = A0;
int sensorValue = 0;
```

まず、値の初期値を決めています。sensorPin はアナログ入力を受け取るためのピンの値です。sensorValue はセンサー値を格納するものです。

```c
void setup() {
  Serial.begin(9600);
  Serial.println("Analog Read");
}
```

起動時に動作する setup 関数では、`Serial.begin(9600);` をつかってシリアル接続時のデータ転送速度を 9600 bps に設定しています。これは Arduino IDE のシリアルコンソールで同じデータ転送速度に合わせると文字列が受信できます。

`Serial.println("Analog Read");` で、シリアルコンソールに `Analog Read` と起動時にチャックしやすいように文字列を送信しています。

```c
void loop() {
  sensorValue = analogRead(sensorPin);
  Serial.print("light = ");
  Serial.println(sensorValue);
  delay(1000);
}
```

起動後、動作し続ける loop 関数では、`analogRead(sensorPin)` によってアナログ入力値を受け取っています。`Serial.print("light = ");` と `Serial.println(sensorValue);` でシリアルコンソールに `light = 288` と値を送っています。

` delay(1000);` で、1秒ごとにこの処理を繰り返すように遅延させています。

## プログラムの説明

![image](https://i.gyazo.com/e7556ca5b37f0d27fdd087289ce46e45.png)

いよいよ、デバイスと Node-RED を MQTT でやり取りする IoT の仕組みです。今回のプログラムの動きを把握します。

## プログラムの準備

今回のプログラムを準備します。

メニュー > ファイル > 新規ファイル をクリックします。

![image](https://i.gyazo.com/feb362e740c05cdd469a96111abd9382.png)

新規ファイルを準備します。

以下のプログラムを新規ファイルにコピーアンドペーストしましょう。

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
char *ssid = "<Wi-FiのSSID>";
// Wi-Fiのパスワード
char *password = "<Wi-Fiのパスワード>";

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

// 光センサー関連の変数
int sensorPin = A0;
int sensorValue = 0;
long messageSentAtSendMQTT = 0;

// 光センサー送信間隔
int wait_time = 5000;
 
// JSON 送信時に使う buffer
char pubJson[255];
 
// PubSubClient まわりの準備
WiFiClient httpClient;
PubSubClient mqttClient(httpClient);
 
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

  // センサーを wait_time ミリ秒で指定された間隔で送信
  long spanTimeSendMQTT = millis() - messageSentAtSendMQTT;
  if (spanTimeSendMQTT > wait_time) {
    messageSentAtSendMQTT = millis();
    // センサー値取得
    sensorValue = analogRead(sensorPin);
    Serial.print("light = ");
    Serial.println(sensorValue);
    // センサー値 publish 
    DynamicJsonDocument doc(1024);
    doc["light"] = sensorValue;
    serializeJson(doc, pubJson);
    mqttClient.publish(pubTopic, pubJson);
  }
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

こちらをコピーアンドペーストできたら `TTC-Demo-2022-Light-MQTT` というファイル名で保存しましょう。

### メインプログラムの簡単な説明

TODO : メインプログラムの簡単な説明

## プログラムの設定

今回のプログラム内の設定をします。

```c
// Wi-FiのSSID
char *ssid = "<Wi-FiのSSID>";
// Wi-Fiのパスワード
char *password = "<Wi-Fiのパスワード>";
```

前章と同じく Wi-Fi の設定を行います。

```c
// 今回使いたい Beebotte のブローカーのアドレス
const char *mqttEndpoint = "mqtt.beebotte.com";
// 今回使いたい Beebotte のポート
const int mqttPort = 1883;
// 今回使いたい Beebotte のユーザー名
const char *mqttUsername = "<今回使いたい Beebotte のユーザー名>";
// 今回使いたい Beebotte のパスワード
const char *mqttPassword = "";
```

Beebotte については、今回は自分の MQTT ブローカーを使って行いましょう。

## プログラムの書き込み

Arduino IDE にプログラムを書き込みます。

![image](https://i.gyazo.com/7af357caade502812ae210732cec208a.png)

Arduino UNO WiFi Rev2 へ書き込む前にシリアルモニタを起動しておきましょう。今回は設定値は 9600 bps です。

![image](https://i.gyazo.com/ca02fff1c8001e2bfe484ad5a294f917.png)

ボード設定を行い、書き込みボタンをクリックして書き込みます。

## プログラムの動作確認1

プログラムと回路の動作を Arduino IDE で確認します。

![image](https://i.gyazo.com/3ef6f3661c136eba28f0fb2d2bd6fc57.png)

まず、Wi-Fi がつながり MQTT ブローカーに接続されていることが確認できます。

![image](https://i.gyazo.com/45ed5690487091dafad784637f5808b9.png)

つづいて、5秒ごとにセンサーデータが取得されていることを確認しましょう。

![image](https://i.gyazo.com/af52bcb8cc80352585fe5e392400f726.png)

手で影を作って値の変化も見てみましょう。（回路が間違っていると値が変化しない場合があります。）


## プログラムの動作確認2

プログラムと回路の動作を Node-RED で確認します。

![image](https://i.gyazo.com/f1c0153bf6e75e3a0d10bb24833d42fd.png)

前回使った ttc2022/res を受信する mqtt in ノードに debug ノードをつないだフローで確認します。

![image](https://i.gyazo.com/4f2d78d1c51ab404ee657bdefac53170.png)

サーバの指定を Teacher MQTT Broker に設定します。問題なければデバックタブを表示してデータの受信を待ちます。

![image](https://i.gyazo.com/f7f4ecdd40effbfbd2647712a83340a7.png)

Arudino を動作させてデータが受信されるか見てみましょう。

## センサー値の変化を確認

センサーの値の変化を Node-RED で確認します。

![image](https://i.gyazo.com/5abe3be18a230eaecd2b07bfaf142ab9.png)

手をかぶせて光センサーの値が変化するか試してみましょう。

TODO:しきい値での対応を入れる

## TechFeed の話

![image](https://i.gyazo.com/0dde1513639b3133e8d8165b0382b732.jpg)

今回 IoT の良い情報源として [TechFeed](https://techfeed.io/) をお伝えします。

> エンジニアに最高の情報を、最高の形で届ける。
> 
> 海外情報は自動翻訳してお届け。ハイレベルな情報はエキスパートがご紹介。そしてあなたも発信できる。

とのことで、国内だけでなく海外の情報にも触れやすいです。

![image](https://i.gyazo.com/a62fdf82aaa5a5cb74980b1cdef05572.jpg)

もちろん [IoT チャンネル](https://techfeed.io/channels/IoT) もあります。私もエキスパートとして、なるべく1日1記事はピックアップしようとしています。

これを機会にぜひ登録して IoT に関する情報を追いかけましょう！