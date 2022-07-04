# センサー通知実習

## 演習概要

今回の Node-RED 動作の大まかな流れを把握します。

![image](https://i.gyazo.com/d69f0a82e9d9ecb77b6c5ddeea4cd435.png)

[第9回の仕組み](../lecture09/00-introduction.md) で取得した部屋の明るさをセンサーが捉えて、Node-RED に送りその明るさに応じて LINE Notify ノードによって LINE アプリに通知を送ります。

## デバイス準備→書き込み→デバイス動作確認

![image](https://i.gyazo.com/fa7747862927454bf64c9866d5cc1fa7.jpg)

以前行なったセンサー値を取得するプログラムをデバイスに書き込み準備します。

TODO : [第9回の仕組み](../lecture09/00-introduction.md)

## デバイス連携 フロー作成

今回の Node-RED デバイス連携部分のフローを作成します。

## MQTT 設定

今回の Node-RED フローの MQTT 接続設定をします。

## データ受信確認

Node-RED がデバイスからデータ受信を部分確認します。

## LINE Notify フロー追加

Node-RED LINE Notify 連携部分のフローを追加します。

TODO : 連結する形

## LINE Notify 確認

Node-RED から LINE Notify へのメッセージ送信を部分を確認します。

## フロー実践

フロー全体の動作を確認します。

TODO : JSONata での値を含めた変更
TODO : ダッシュボードノード　ボタンを押すとデータを送る
TODO : ダッシュボードノード　グラフ表示
TODO : おさらい