# 第10回 デバイス遠隔操作

こちらを始める前に [第8回](../lecture08/00-introduction.md) の資料を元に、

- 8-1 デバイス準備、8-2 デバイスの動作理解 でデバイスがどう動くかの理解
- 8-5 Arduino IDE 準備、8-6 JSON ライブラリ準備、8-7 MQTT ライブラリ準備

を進めておきましょう。

## 10-1 デバイスの動作理解

今回のデバイス動作の大まかな流れを把握します。

![image](https://i.gyazo.com/1bf31bee68324ecbd6812944ea5c7bb8.jpg)

今回も [Arduino UNO Wi-Fi Rev.2](https://www.marutsu.co.jp/pc/i/33411858/) というデバイスを使っていきましょう。

![image](https://i.gyazo.com/01ec38729dab790a0ae73464daeec412.png)

Raspberry Pi の授業で使った LED を使ってデバイスと Node-RED を MQTT でやり取りする IoT の仕組みをつくり、LED の点灯を遠隔操作します。

## 10-2 回路説明

デバイスにつなげる回路や動作の説明をします。

### 10-2-1 LED

![image](https://i.gyazo.com/8cdd56ad2c48be155114c877a2ed03c1.jpg)

LED を用意しましょう。



Arduino 側ではデジタル入力の D2 を使います。

### 10-2-2 その他のパーツの準備

![image](https://i.gyazo.com/8cdd56ad2c48be155114c877a2ed03c1.jpg)

橙橙茶金の 330Ω の抵抗を準備します。

![image](https://i.gyazo.com/90847c9a6ad415233e4d220d284f9582.jpg)

- 長めの赤ケーブル
- 短めの黒ケーブル

を準備します。

![image](https://i.gyazo.com/68a50881c024eecc8296526abecf3583.jpg)

ブレッドボードも準備しましょう。

## 回路取り付け

デバイスにつなげる回路を取り付ける

## プログラムの説明

今回のプログラムの動きを把握します。

## プログラムの準備

今回のプログラムを準備します。

## プログラムの設定

今回のプログラム内の設定をします。

## プログラムの書き込み

Arduino IDE にプログラムを書き込みます。

## プログラムの動作確認1

プログラムと回路の動作を Arduino IDE で確認します。

## プログラムの動作確認2

プログラムと回路の動作を Node-RED で確認します。

## 遠隔操作実践

Node-RED からデバイスを遠隔操作します。