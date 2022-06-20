# 第8回 デバイス MQTT 接続

## デバイス準備

今回動かすデバイスを準備し仕様を把握します。

![image](https://i.gyazo.com/1bf31bee68324ecbd6812944ea5c7bb8.jpg)

今回使うデバイスは [Arduino UNO Wi-Fi Rev.2](https://www.marutsu.co.jp/pc/i/33411858/) というデバイスを使います。

- 参考資料
  - Arduino 本家のストア → https://store.arduino.cc/products/arduino-uno-wifi-rev2

![image](https://i.gyazo.com/f7ea66b470cd613debf930ce43ef02c4.png)

別の授業で使い始めている Arduino UNO とほぼ同じ大きさ、かつ、ほぼ同じピン配置で、Wi-Fi や Bluetooth にもつながります。

ですので、電子工作をしやすい Arduino の中でも、入門機として有名な Arduino UNO のナレッジを活用することができ IoT ができるということです。

くわしい仕様は以下も参考になります（英語ですが）

- UNO WiFi Rev2 | Arduino Documentation | Arduino Documentation
  - https://docs.arduino.cc/hardware/uno-wifi-rev2

早速使っていきましょう。

## デバイスの動作理解

今回動かすデバイスの動作を大まかに把握します。

Arduino UNO とほぼ同じ大きさ、かつ、ほぼ同じピン配置ですので、そのあたりの仕組みは別の授業でも勉強しているので割愛します。

![image](https://i.gyazo.com/c4819a34c438df5b7bcd062ca8e3f8a8.jpg)

Wi-Fi を動かす部分は、この WiFiNINA モジュールというのが担当していて、Arduino 公式のライブラリ（汎用性の高い複数のプログラムを再利用可能な形でひとまとまりにしたもの）を自分の Arduino プログラムに読み込むことで操作することができます。

- WiFiNINA - Arduino Reference
  - https://www.arduino.cc/reference/en/libraries/wifinina/

この授業では、

- Arduino IDE で Arduino UNO Wi-Fi Rev.2 を書き込む設定を行う
- Wi-Fi ライブラリをインストールし Wi-Fi に接続する
- MQTT に接続するライブラリ、JSON データを扱いやすくするライブラリをインストールする
- MQTT ブローカにつながる Arduino プログラムをコピーアンドペーストで持ってくる
- 講師の beebotte MQTT ブローカにつながるように設定し動作確認
- 自分の beebotte MQTT ブローカにつながるように設定し動作確認

という流れを進めていきます。

また、

- Arduino IDE で Arduino UNO Wi-Fi Rev.2 を書き込む設定を行う
- Wi-Fi ライブラリをインストールし Wi-Fi に接続する

部分は、すでに生形先生と Wi-Fi が接続する対応はできていると聞いていているので、

- MQTT に接続するライブラリ、JSON データを扱いやすくするライブラリをインストールする

から進めていきます。

## 参考：Arduino IDE で Arduino UNO Wi-Fi Rev.2 を書き込む設定

すでに設定済みの前提で進めますが、おさらいしたい方は、以下を参考にしてみてください。

![image](https://www.1ft-seabass.jp/memo/uploads/2022/02/arduino-uno-wifi-rev2-setup-and-blink_01-800x450.jpg)

- Arduino UNO WiFi Rev.2 でセットアップして Blink サンプルを動かすメモ – 1ft-seabass.jp.MEMO
  - https://www.1ft-seabass.jp/memo/2022/03/01/arduino-uno-wifi-rev2-setup-and-blink/

## 参考：Wi-Fi ライブラリをインストールし Wi-Fi に接続する

すでに設定済みの前提で進めますが、おさらいしたい方は、以下を参考にしてみてください。

![image](https://www.1ft-seabass.jp/memo/uploads/2022/02/arduino-uno-wifi-rev2-wifi_01-800x420.jpg)

- Arduino UNO WiFi Rev.2 で Wi-Fi をつないでみるメモ – 1ft-seabass.jp.MEMO
  - https://www.1ft-seabass.jp/memo/2022/03/02/arduino-uno-wifi-rev2-wifi/

## Arduino IDE 準備

Arduino IDE を デバイスと接続して書き込める準備をします。

![image](https://i.gyazo.com/cc05d2e4dfc4e8489c78f30c8d460673.png)

Arduino を起動しましょう。

![image](https://i.gyazo.com/524eabc9660b969484c7042d969eda6f.png)

メニュー > ファイル > 新規ファイル をクリックします。

![image](https://i.gyazo.com/feb362e740c05cdd469a96111abd9382.png)

新規ファイルを準備します。

### Arduino バージョン

![image](https://i.gyazo.com/c7ff9e72a15bb029deeb10cc121c01c3.png)

Arduino バージョンは 1.8.13 ですが、1.8 台であれば大丈夫です。

## JSON ライブラリ準備

Arduino IDE に JSON データを扱うライブラリを準備します。

### Arduino IDE におけるライブラリ管理

![image](https://i.gyazo.com/f1204d9c7e8fa7cac7ae93590ced3e5b.png)

Arduino IDE ではライブラリ（汎用性の高い複数のプログラムを再利用可能な形でひとまとまりにしたもの）をライブラリマネージャで管理できます。ライブラリインストールや削除、すでにインストールされているものの確認など GUI で手軽に行うことができます。

以前は、Arduino のライブラリフォルダに直接 zip ファイルを展開するなど、かなりデリケートな作業の必要がありましたが、ライブラリマネージャでしたら GUI だけで操作が完結します。

![image](https://i.gyazo.com/fc94a1bcbe97ad41c89e297b2802e201.png)

ツール > ライブラリを管理 でライブラリマネージャを起動します。

### JSON を扱いやすくする ArduinoJson をインストール

この作業はインストールなので、一度だけ対応すれば OK です。

![image](https://i.gyazo.com/0926b156ff8ee87a9a8b626d80bbeb92.png)

ツール > ライブラリを管理 でライブラリマネージャを起動します。

![image](https://i.gyazo.com/b8b223beedfe7b134fe5380e1920e584.png)

`ArduinoJson` で検索して、`完全同名` のライブラリを探します。

マウスを乗せると、バージョンとインストールのボタンが右下に出るので `6.18.5` のバージョンを指定してインストールボタンをクリックします。

![image](https://i.gyazo.com/ec1d0688667c161c941eced03a1bade9.png)

インストールできたら、ひょっとすると、リストが一番上に戻ってしまうかもしれませんが、根気よく `ArduinoJson` に移動して INSTALLED になっていたら成功です。

### ArduinoJson の情報は充実

![image](https://i.gyazo.com/ce0d85128ef8b9dd91734f1176607439.png)

https://arduinojson.org/ というウェブサイトを持っていて情報が充実しています。

![image](https://i.gyazo.com/35ae79ee668a291a65845fb495bb1f32.png)

ソースコードのサンプルもあり、すぐに使いやすくなっています。

## MQTT ライブラリ準備

Arduino IDE に MQTT データを扱うライブラリを準備します。

### MQTT のやり取りできるライブラリ PubSubClient をインストールする

この作業はインストールなので、一度だけ対応すれば OK です。

Arduino のライブラリ管理から検索してインストールできます。

![image](https://i.gyazo.com/0926b156ff8ee87a9a8b626d80bbeb92.png)

ツール > ライブラリを管理 でライブラリマネージャを起動します。

![image](https://i.gyazo.com/6a82b0efb54bc4a78c3faf643f8b8494.png)

`PubSubClient` で検索して、`完全同名` のライブラリを探します。

![image](https://i.gyazo.com/1e50c2b9a016c7a733822ae9d40bc020.png)

マウスを乗せると、バージョンとインストールのボタンが右下に出るので `2.8` のバージョンを指定してインストールボタンをクリックします。

![image](https://i.gyazo.com/5d4ab17b5a0bf7dc323f20ff5efedf3b.png)

インストールできたら、ひょっとすると、リストが一番上に戻ってしまうかもしれませんが、根気よく `PubSubClient` に移動して INSTALLED になっていたら成功です。

### めちゃめちゃ余談ですが

PubSubClient の作者は Node-RED のメイン開発者でもある　Nick O'Leary さんです。

- knolleary/pubsubclient: A client library for the Arduino Ethernet Shield that provides support for MQTT.
  - https://github.com/knolleary/pubsubclient

講師も一度会ったことがあります。

- IBM HursleyでのNode-RED開発チームとのミーティングにてNode-RED UG Japanの一員として活動報告＆デモを担当しました – 1ft-seabass.jp.MEMO
  - https://www.1ft-seabass.jp/memo/2018/11/07/node-red-ug-jp-ibm-hursley-mtg-resume/

## プログラムの準備

Arduino IDE でプログラムを準備します。さきほどから新規作成したままのファイルに以下をコピーアンドペーストしましょう。

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

こちらをコピーアンドペーストできたら `TTC-Demo-2022-MQTT-Onefile-src` というファイル名で保存しましょう。

### ライブラリが反映されているかを確認

![image](https://i.gyazo.com/5f517b717591981ef10af6796f772c87.png)

この段階で、SPI、WifiNINA、PubSubClient に色がついていればインストいーるされています。（ ArduinoJSON は色がつきませんが一旦気にしなくてOKです）

### 必要な動作はすでにできあがっているので、まずは設定していきましょう。

今回のプログラムは

## MQTT 接続設定

プログラムの中の MQTT 接続の設定を行います。

### まず Wi-Fi の設定

```c
// Wi-FiのSSID
char *ssid = "<Wi-FiのSSID>";
// Wi-Fiのパスワード
char *password = "<Wi-Fiのパスワード>";
```

こちらに、今回の授業で使う Wi-Fi 設定に置き換えましょう。（ここは口頭で伝えます）

`<Wi-FiのSSID>` を置き換える場合、`<` から `>` まで含めて選択して上書きしましょう。`<Wi-Fiのパスワード>` 部分も同様です。

変更ができたら忘れず保存しましょう。

### 講師 MQTT ブローカへ MQTT 接続設定

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

この部分に注目します。ブローカーのアドレス、ポート、パスワードはすでに設定が済んでいます。

`<今回使いたい Beebotte のユーザー名>` を講師の MQTT ブローカに上書きします。

`<今回使いたい Beebotte のユーザー名>` を置き換える場合、`<` から `>` まで含めて選択して上書きしましょう。

## プログラムの書き込み

Arduino IDE からデバイスにプログラムを書き込みます。

![image](https://i.gyazo.com/1bf31bee68324ecbd6812944ea5c7bb8.jpg)

Arduino UNO WiFi Rev2 を PC とつなぎます。

![image](https://i.gyazo.com/2589738d5047043ac84efa28b992c14c.png)

ボードを Arduino megaAVR Boards > Arduino UNO WiFi Rev2 と設定しましょう。

![image](https://i.gyazo.com/24744e8a898bbbf060132d1dfe01c45f.png)

シリアルポートを、Arduino UNO WiFi Rev2 と書いてあるポートを選択します。このあたりが、Arudino 公式ボードだとちゃんと名前が出るので便利ですね。

## プログラムの動作確認1

デバイスが動いているかどうかを Arduino IDE で確認します。

### シリアルモニタ起動

動作確認はシリアルモニタで行います。

シリアルモニタは、Arduino 上で Serial 関数の Serial.begin によってボーレート（1秒間にどれくらい送れるかというデータ転送レートのbps値）に合わせておくとデータが受信できます。

```c
void setup() {
  Serial.begin(9600);
```

今回の場合、このように 9600 bps で設定されています。

![image](https://i.gyazo.com/7af357caade502812ae210732cec208a.png)

Arduino UNO WiFi Rev2 へ書き込む前にシリアルモニタを起動しておきましょう。

シリアルモニタを起動後、右下の設定値を

- LFのみ
- 9600 bps

とデータ転送レートを合わせておきましょう。

なお、シリアルコンソールに送信する場合には Serial.print 関数を使います。たとえば、プログラム中に `Serial.print("WiFi Connected");` という記述がある場合 `WiFi Connected` と表示されます。

### プログラムを書き込んでみる

![image](https://i.gyazo.com/ca02fff1c8001e2bfe484ad5a294f917.png)

ということで、書き込みボタンをクリックして書き込みます。

![image](https://i.gyazo.com/38ebbeda8eb9318c201258513b56f4dd.png)

書き込みが済むと、Wi-Fi 設定が合っていれば、接続され、このようにログが出れば成功です。

## プログラムの動作確認2

デバイスのデータが届いているか Node-RED で確認します。

![image](https://i.gyazo.com/f1c0153bf6e75e3a0d10bb24833d42fd.png)

前回使った ttc2022/res を受信する mqtt in ノードに debug ノードをつないだフローで確認します。

![image](https://i.gyazo.com/ee0ccf76f1ae63366ba4ccc96baa8026.png)

サーバの指定を Teacher MQTT Broker に設定できているか確認しましょう。問題なければデバックタブを表示してデータの受信を待ちます。

### Arduino プログラム側では接続時にデータを送信している

Arduino プログラム側で mqttConnect という関数の部分で MQTT の接続を行っています。

接続成立後に、すぐ MQTT ブローカに一度 `{"message":"Connected"}` という JSON データを送っています。

このあたりです。

```c
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
```

`// 初回データ送信 publish ///////////` 以降がデータ送っています。

- DynamicJsonDocument という ArduinoJSON から提供された型でこれから作成する JSON データのベースとなる doc という変数を宣言
- doc に message という値を設定し `Connected` というデータを入れる
- serializeJson で doc を解析することで `{"message":"Connected"}` というデータとなる
- serializeJson の第 2 引数で、事前に pubJson と宣言した JSON 送信時に使う buffer 型に `{"message":"Connected"}` を渡す
- `mqttClient.publish(pubTopic, pubJson);` で第 1 引数で pubTopic 変数で指定されたトピック ttc2022/res を指定していて、トピックに向けて `{"message":"Connected"}` のデータを送っています

ということを行っています。

### デバイスを再起動して接続を待つ

![image](https://i.gyazo.com/1bf31bee68324ecbd6812944ea5c7bb8.jpg)

では、再度 USB を抜き差ししてデバイスを再起動してみましょう。

![image](https://i.gyazo.com/f3fbae9365e18d67b1ef57fb67a5fa66.png)

ここまでの設定がうまくいっていれば、Node-RED 側で接続時にデータが受信されています。

