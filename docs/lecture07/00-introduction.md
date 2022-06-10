# 第7回 MQTT データ連携演習

## MQTT 送受信の概要

MQTT の送受信に関して大きく概念を理解する

- 教材
  - サブテキスト

前回の授業で MQTT の送受信は、MQTT ブローカがデータのやり取りを仲立ちして、送信したデータが届くことが体感できました。

![image](https://i.gyazo.com/55d6c0ed8745fac2966a95a2c497c322.png)

MQTT プロトコル上で、データやりとりする要素として

- メッセージ
  - MQTT 上でやりとりするデータ
- MQTT ブローカ
  - メッセージを受け取って、メッセージを配る
- Publisher
  - メッセージを送る（発行する）クライアント
- Subscriber
  - メッセージを受け取る（購読する）クライアント

が、います。

## パブリッシュ概要

データ送信に関するパブリッシュ（発行）に把握する。

- 教材
  - サブテキスト

Publisher はメッセージを送る（発行する）クライアントです。

## サブスクライブ概要

データ受信に関するサブスクライブ（購読）を把握する。

- 教材
  - サブテキスト

Subscriber はメッセージを受け取る（購読する）クライアント

## トピック概要

MQTT のトピックの役割や指定の仕方を把握する。

- 教材
  - サブテキスト

トピックはメッセージの送り先や指定したメッセージを受け取る機能です。Publisher と Subscriber で共通でトピックを扱います。

 - Publisher では MQTT ブローカに対してトピックでメッセージの送り先を指定して送ることができます。
 - Subscriber では MQTT ブローカに対してトピックで指定したメッセージを受け取ることができます。

トピックは `/` で階層構造が表現できます。

```
ttc2022/res
```

みなさんは、すでに Beebotte では、このように ttc2022 の階層の res という指定をしました。これは Beebotte の MQTT ブローカ仕様 https://beebotte.com/docs/mqtt として決められていますが、MQTT の仕様としては、自由に決められるものです。

住所のイメージに近いかもしれません。

```
東京都/中野区/東中野/4丁目/2/3/東京テクニカルカレッジ
```

また Subscriber が購読時では 1 つのトピック指定で複数のトピックを同時に指定できる、ワイルドカードと呼ばれるものがあり `#` や `+` が使えます。

```
東京都/中野区/東中野/4丁目/#
```

`#` でこのように指定すると、それ以降の階層がなんでもとれるよう指定できます。つまり東京都中野区東中野4丁目全域のデータがとれます。

```
東京都/中野区/+/4丁目/+
```

`+` でこのように指定すると、指定した階層はすべて取得できます。この場合は、東京都中野区の様々な町（中野とか新井とか）の 4 丁目内のデータがとれます。

この発想で、仮にある施設で温度・湿度・気圧のセンサーデータがパブリッシュされているとしましょう。

```
building/F1/sensors/temperature
building/F1/sensors/humidity
building/F1/sensors/pressure
building/F2/sensors/temperature
building/F2/sensors/humidity
building/F3/sensors/pressure
  |
  |
building/F10/sensors/temperature
building/F10/sensors/humidity
building/F10/sensors/pressure
```

この場合、

```
building/+/sensors/temperature
```

各階の温度データが取得できます。

```
building/F1/sensors/#
```

1階の温度・湿度・気圧データが取得できます。

## パブリッシュフロー作成

Node-RED でデータ送信フローを作成します。

- 教材
  - サブテキスト

今回は、

## パブリッシュ実践

Node-RED でデータ送信フローを動かして確認します。

- 教材
  - サブテキスト

## サブスクライブフロー作成

Node-RED でデータ受信フローを作成します。

- 教材
  - サブテキスト

## サブスクライブ実践

Node-RED でデータ受信フローを動かして確認します。

- 教材
  - サブテキスト

## HTTP との違い

主に MQTT 受信に関しての HTTP との違い・メリットを把握。

- 教材
  - サブテキスト

HTTP は以前ざっくり学びましたが、IoT でももちろん使われているものです。HTTP リクエストとレスポンスでできていて仕様は シンプルで、長く使われているので Web の世界の仕組みを応用しやすいところは良いポイントです。

ですが、データを送るためにたとえば HTTP ヘッダーが必要だったり、受け取るときも HTTP ステータスコードが必要だったりとオーバーヘッドの大きさが、それほどパワーのないデバイスを扱う IoT においては影響が大きく負担になることもあります。

また、HTTP は、基本的に 1 対 1 の通信でやりとりされるので、大量のデバイスからセンサーデータを受け取るような IoT のユースケースの時に、どんどん通信が増えて、ここでも負担になる可能性があります。

その点において、MQTT は以下の点が優れています。

- MQTT では非同期に1対複数のやりとりができる。仮に接続が増えても MQTT ブローカが（さばける限りは）効率的にデータがやりとりできる
- HTTP と比べて MQTT はデータが軽量なので IoT で扱うようなデバイスでも負担が少なくできる
- MQTT はデータを再送できる機能があり HTTP と比べて確実なデータ送信ができる

## IoT における MQTT

IoT における MQTT の重要性や使いどころを把握します。

- 教材
  - サブテキスト

ここまで HTTP との違いや MQTT の仕様を Node-RED を交えて体験してきました。

身近な事例を交えながら、MQTT を使うイメージを高めていきましょう。

- M5Stack で MQTT から Node-RED 経由で JSON データでまとめてシナリオを渡してビジュアルが変わる仕組みを作ったメモ – 1ft-seabass.jp.MEMO
  - https://www.1ft-seabass.jp/memo/2020/10/31/controlling-m5stack-from-node-red-mqtt-json-senarios/
- Node-RED MQTTブローカー経由でNefryBT＋フルカラーテープLEDを動かすメモ – 1ft-seabass.jp.MEMO
  - https://www.1ft-seabass.jp/memo/2017/10/10/nefrybt-mqtt-tape-led/
- E-textile Electric fabric “nüno” のデータをM5StackからMQTTでつないでNode-REDにつなげるメモ – 1ft-seabass.jp.MEMO
  - https://www.1ft-seabass.jp/memo/2019/07/27/etextile-nuno-meets-mqtt-and-nodered/