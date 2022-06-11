# 第7回 MQTT データ連携演習

## MQTT 送受信の概要

MQTT の送受信に関して大きく概念を理解する

- 教材
  - サブテキスト

前回の授業で MQTT の送受信は、MQTT ブローカがデータのやり取りを仲立ちして、送信したデータが届くことが体感できました。

![image](https://i.gyazo.com/3cbc0a8248c21bca8b0719a9623ec3de.png)

MQTT プロトコル上で、データやりとりする要素として、以下のようにあります。

- メッセージ
  - MQTT 上でやりとりするデータ
- トピック
  - メッセージの送り先や指定したメッセージを受け取る機能
- MQTT ブローカ
  - メッセージを受け取って、メッセージを配る
- Publisher
  - メッセージを送る（発行する）クライアント
- Subscriber
  - メッセージを受け取る（購読する）クライアント

まず、トピックはメッセージの送り先や指定したメッセージを受け取る機能です。Publisher と Subscriber で共通でトピックを扱います。

前回の授業で設定したトピックは ttc2022/res でしたが、それを例にします。

![image](https://i.gyazo.com/a12f376874ec401ad2107d53f93b11bb.png)

- Publisher は MQTT ブローカに対してトピックでメッセージの送り先を指定して送ることができます。
- Subscriber は MQTT ブローカに対してトピックで指定したメッセージを受け取ることができます。

この仕組みでデータのやり取りを行っていました。

![image](https://i.gyazo.com/62023965804747c723b4bd1fd741da5f.png)

MQTT ブローカがデータのやり取りを指揮してくれるので、Publisher が発行したメッセージは、発行したトピックを購読している Subscriber 側が複数でもすべて受信することができます。ですので、前回、生徒みんなでデータを送りあってもデータが飛び交うことができたのです。

![image](https://i.gyazo.com/616011e99de06bfbdc9714e306727459.png)

もちろん、購読するトピックが違えば、今回の ttc2022/res にメッセージを送る Publisher のデータを受け取ることができません。

### トピックの階層構造

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

## サブスクライブフロー作成

Node-RED でデータ受信フローを作成します。

- 教材
  - サブテキスト

今回のデータ受信フローは、講師の MQTT ブローカーにもう一度つないで、今度は別のトピックを購読してダミーの温度・湿度センサーデータを受け取り、IoT データの購読を体験します。

### 自分の MQTT ブローカーをちゃんと命名する

このあと、データ受信フローを体験するために、もう一度、講師の MQTT ブローカーへの接続を行います。

そのため、MQTT ブローカーの接続が 2 つになります。

- 自分の MQTT ブローカー（現在接続中）
- 講師の MQTT ブローカー（これからつなぐ）

ですので、自分の MQTT ブローカーをちゃんと命名しましょう。

![image](https://i.gyazo.com/cfd67d9d85b907db0505d6d6ac13c5b2.png)

mqtt in ノードをクリックして、現在選択中のサーバが自分の MQTT ブローカー `mqtt.beebotte.com:1883` になっていることを確認して鉛筆ボタンをクリックして編集します。

![image](https://i.gyazo.com/2ef7a8197f0651ded148bbd065136461.png)

mqtt-broker ノードのプロパティです。

![image](https://i.gyazo.com/d604feb5bc72f743611bb698f9ce5aaf.png)

名前の部分が現在空欄になっているので `mqtt.beebotte.com:1883` という名前になっていました。

![image](https://i.gyazo.com/e13812d9c42b2a7d22ebe00414f9e61c.png)

名前の欄に `My MQTT Broker` と記入して、更新ボタンをクリックします。

![image](https://i.gyazo.com/bdaa148098133b6d90ed73176da57e00.png)

mqtt in ノードでのサーバ選択時も `My MQTT Broker` となり分かりやすくなりました。

### 新しいフローを作成

![image](https://i.gyazo.com/99585d19d1c5bd08ec34d21e05e61339.png)

mqtt in ノードと debug ノードを新しくつくります。

### 講師の MQTT ブローカーを追加

新しく作った mqtt in ノードのプロパティで講師の MQTT ブローカーを追加します。（以前のつくったフローにある mqtt in ノードは編集しないよう注意してください。）

![image](https://i.gyazo.com/2b5b3a7f5cd6f4e780f70e1279a09791.png)

サーバで `新規に mqtt-broker を追加` を選択し、

![image](https://i.gyazo.com/a15345fb6c2312b3309e5e3330524f03.png)

鉛筆ボタンをクリックして編集します。

![image](https://i.gyazo.com/4cc85d0df52e2e64eddc22c62337477c.png)

mqtt-broker 設定のプロパティです。

- 名前
  - Teacher MQTT Broker
- 接続
  - サーバ
    - mqtt.beebotte.com
  - ポート
    - 1883

![image](https://i.gyazo.com/3328dc86ec4ba36c07134523e60605f3.png)

- セキュリティ
  - ユーザ名
    - Slack で伝えるトークン
  - パスワード
    - （なにも書かない）

パスワードは何も書かず空欄でOKです。

設定ができたら、追加ボタンをクリックします。

### mqtt in ノードで新しいトピックを設定

![image](https://i.gyazo.com/d346452ec8130d2f1c89684992e9eaff.png)

MQTT ブローカを設定して追加ボタンをクリックすると、mqtt in ノードのプロパティに戻るはずです。

トピックを以下のように変更します。

- トピック
  - ttc2022/sensor

![image](https://i.gyazo.com/eab4be1c4e188aee9581749553399a00.png)

設定ができたら、デプロイをクリックして反映させます。

## サブスクライブ実践

Node-RED でデータ受信フローを動かして確認します。

- 教材
  - サブテキスト

センサーデータは 10 秒に一度発行されます。

![image](https://i.gyazo.com/2aaeec5a9bf6dd0e77cc620c81ea0580.png)

フローがうまく動けば、デバッグタブでこのようにデータ受信できます。

### JSON データとして受信する

このデータはまだ文字列の状態で受信しています。ですが、これは JSON データです。JSON を解釈してより詳細のデータが取得できるよう実践していきましょう。

今回の mqtt in ノードのプロパティを見てみましょう。

![image](https://i.gyazo.com/cca4f42b255cf6563040c37780b36806.png)

出力の項目がデフォルトでは `自動判別` になっています。

![image](https://i.gyazo.com/b99581f2ab8f10ef44774273ca07c256.png)

出力を `JSONオブジェクト` に選択して、完了ボタンをクリックします。

![image](https://i.gyazo.com/eab4be1c4e188aee9581749553399a00.png)

設定ができたら、デプロイをクリックして反映させます。

![image](https://i.gyazo.com/d6dabdb4dbe50641f0852743ade37ce2.png)

デバッグタブで JSON と解釈されデータ受信できます。

![image](https://i.gyazo.com/95fcbd835bce3e6c2ef505227ae0a719.png)

デバッグタブでは JSON データの構造がこのように見ることができます。

![image](https://i.gyazo.com/e3de1eba6487e0e461c6d6b74aeeb73d.png)

この三角ボタンをクリックして、実際に操作して構造をみてましょう。

### debug ノードをもう一つ追加して温度データだけ見てみる

IoT センサーデータの検証時は特定の値を追うケースが多いので、やり方を体験しておきましょう。

![image](https://i.gyazo.com/16ebce8cb282dfe8bb012a676540c2ef.png)

今回のフローに debug ノードをもう一つ追加します。

![image](https://i.gyazo.com/9d00db0181c67d1fc50a40228431fe22.png)

新しく追加した debug ノードのプロパティで対象を `msg.payload.temperature` に変更します。

![image](https://i.gyazo.com/edc4430644c6ca41d135c3a59aa1466a.png)

フローはこのようになります。

![image](https://i.gyazo.com/eab4be1c4e188aee9581749553399a00.png)

設定ができたら、デプロイをクリックして反映させます。

![image](https://i.gyazo.com/53fd5fa9ea7c95cace98d2fee820ae11.png)

このように JSON データの中の temperature だけをデバックタグで確認し温度データだけ見ることができます。

## パブリッシュフロー作成

Node-RED でデータ送信フローを作成します。

- 教材
  - サブテキスト

今回は、

## パブリッシュ実践

Node-RED でデータ送信フローを動かして確認します。

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