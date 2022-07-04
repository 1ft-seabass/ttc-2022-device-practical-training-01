# LINE Notify API 演習

## 12-1 演習概要

今回の Node-RED 動作の大まかな流れを把握します。

![image](https://i.gyazo.com/5e069bdbcfa1b742ebc6e60aebcf6fab.png)


## 12-2 フロー準備

今回の Node-RED フローを作成します。

### 12-2-1 ひとまずフローを全部選択して削除します

![image](https://i.gyazo.com/a4540fb1b4ae851b96978b5916dcd434.png)

まず、今回の 2 回の授業でつくるフローに集中するため、マウスでドラッグして選択して DELETE キーを押して以前のフローを削除します。

MQTT の設定については、ちゃんと保持されているので大丈夫です。

![image](https://i.gyazo.com/8325d656243200bdb6a3038fe4185eb8.png)

右下の + や - 、ナビデータで全体を確認してちゃんと削除できているか、確認しましょう。

## 12-3 インストール

Node-RED で node-red-contrib-line-messaging-api ノードをインストールします。

![image](https://i.gyazo.com/cefbac6bf2f4ed2a7bcd43668754d2a8.png)

インストール方法については、メインテキスト 4.1 「ノードの追加」を確認します。

### 12-3-1 node-red-contrib-line-messaging-api のインストール

右上のメニューからパレットの管理を選択し、ノードを追加タブをクリックします。

![image](https://i.gyazo.com/d34533f2121a058f738053dbe569b593.png)

検索エリアで node-red-contrib-line-messaging-api と検索します。

![image](https://i.gyazo.com/f4c5e7e4e78f8b1f8bb70790c7763475.png)

node-red-contrib-line-messaging-api ノードがでてくるので ノードを追加ボタンをクリックします。

![image](https://i.gyazo.com/4e77a504f4ffe3e7eda850cacae7a981.png)

追加ボタンをクリック。

![image](https://i.gyazo.com/3363d8d868b06f72e58582cb4c31f266.png)

インストールがはじまります。

![image](https://i.gyazo.com/3f76df2d9dacead696791d6a06b2aef5.png)

インストール完了画面がでます。

![image](https://i.gyazo.com/3346529bf5c5fcaae3934f2ed6c01d1c.png)

パレットに node-red-contrib-line-messaging-api 一式が追加されました。

![image](https://i.gyazo.com/9033bc48ccf1167a6974babdd6788f72.png)

こちらの Notify ノードを使います。

## 12-4 フロー作成

![image](https://i.gyazo.com/bd32b73de73d9cd164aefba556330a1a.png)

inject ノードと Notify ノードでこのようなフローを作成します。

### 12-4-1 inject ノード設定

inject ノードは文字列が送れるようにします。

![image](https://i.gyazo.com/a1cfdc7bba9247330b554432d9558ef9.png)

inject ノードをダブルクリックしてプロパティを設定します。

- データタイプ
  - 文字列
- 対象
  - msg.payload
- データ
  - やっほー

と設定します。

### 12-4-2 Notify ノード設定

事前に前回設定した LINE Notify トークンを用意しましょう。

今回の Node-RED フローの LINE Notify 設定を行います。

![image](https://i.gyazo.com/bd32b73de73d9cd164aefba556330a1a.png)

Notify ノードをダブルクリックしてプロパティを設定します。

![image](https://i.gyazo.com/2e3da8b38259ba510ef150eab2cc6ec5.png)

LINE Notify ノードのプロパティで LINE Notify AccessToken 項目に入力して設定します。

![image](https://i.gyazo.com/559c24c8eeb6cd2ceb1a8e184ddc195a.png)

このように入力したものは伏字になっています。

![image](https://i.gyazo.com/943b4630e0163a28b3c7973b4d060418.png)

設定ができたらデプロイします。

## 12-5 フロー実行＆確認

LINE Notify API の設定ができたか確認します。フローを動作させて LINE でメッセージを確認します。

![image](https://i.gyazo.com/895157df89c2ef3c8127e202c065eb76.png)

PC 版アプリのツールを起動しておきましょう。

![image](https://i.gyazo.com/d3d1145becfe8c444c2a968098e749e6.png)

inject ノードをクリックして、メッセージを送ってみます！

![image](https://i.gyazo.com/7f090ccb9d25c86e19299267bf4bc698.png)

## 12-6 フロー変更1

今回の フローを変更し送信するメッセージを変えてみましょう。

![image](https://i.gyazo.com/fd6b288fe0639f323c600080e4fccda2.png)

change ノードを使います。メッセージの値を変更・移動・削除するノードです。

inject ノードと似ていますが、inject ノードはデータの起点として最初にデータを決めて送りますが、change ノードは途中でデータが変更できるので、仕組みを大きく作っていくときは重宝します。

詳しくは、メインテキストの 4.2 change ノードにも書かれています。

![image](https://i.gyazo.com/d7259dd72576e316c8c2470553a490d3.png)

まず、change ノードを途中に入れてメッセージを変更するので、inject ノードを Notify ノードの間を少し延ばします。

![image](https://i.gyazo.com/6471da357a57333c74703e06f78edef9.png)

change ノードをinject ノードを Notify ノードの間に挿入します。

![image](https://i.gyazo.com/a4c196702d5e65d1759fa6c653039cc9.png)

change ノードのプロパティをこのように変更します。

- 名前
  - 部屋が明るくなりました
- ルール
  - 値の代入 msg.payload
  - 対象の値
    - 部屋が明るくなりました

![image](https://i.gyazo.com/943b4630e0163a28b3c7973b4d060418.png)

設定ができたらデプロイします。

![image](https://i.gyazo.com/7cb38530a84d8f4fbb81ba269e987627.png)

inject ノードを実行してみましょう。

![image](https://i.gyazo.com/6c174d8f74d21daa4468e2eab61e6b93.png)

このようにメッセージが「やっほー」から「部屋が明るくなりました」に変更されます。

## 12-7 フロー変更2

今回のフローを変更し0/1値に応じたメッセージをします。

![image](https://i.gyazo.com/c5c3672b0281350f981a331d32c84315.png)

switch ノードというプロパティの値に応じてメッセージを振り分けるノードを使って、0/1値に応じたメッセージを送ります。

- 数値 1 のとき
  - 「部屋が明るくなりました」
- 数値 0 のとき
  - 「部屋が暗くなりました」

このように動作させます。

![image](https://i.gyazo.com/2b12e07adfd0a7537af03ee9fa39cd05.png)

switch ノードを、inject ノードと change ノードの間に入れるので少し延ばします。

![image](https://i.gyazo.com/60bb99824d87eccb8844dc99832ccfc7.png)

switch ノードを間に入れます。

![image](https://i.gyazo.com/47a290ab15e90dcb6aba343b64fb4658.png)

switch ノードのプロパティはこのように設定します。

- プロパティ
  - msg.payload
- 振り分けルール
  - 1 番目
    - データタイプ
      - 数値
    - 評価
      - `==`
    - 値
      - 1
  - 2 番目
    - データタイプ
      - 数値
    - 評価
      - `==`
    - 値
      - 0

![image](https://i.gyazo.com/d0713ebed955f7acb745d68f569e8b09.png)

このように設定するとポートが2つ並びます。

![image](https://i.gyazo.com/507b3b43d114ee7f39e1e9f5f8df19b3.png)

そのまま上のポートは、振り分けルール 1 つ目の msy.payload = 1 だったときの振り分け先になり「部屋が明るくなりました」のメッセージが送信されます。

### 12-7-1「部屋が暗くなりました」のメッセージの振り分けを作る

![image](https://i.gyazo.com/c54c3f7c48a88dcd32e38f41f81e5088.png)

新しく change ノードを配置します。

![image](https://i.gyazo.com/9df04f58c38566857c40cef987f18bbe.png)

振り分けルール 2 つ目の msy.payload = 0 だったときの振り分け先である下のポートにつなぎます。

![image](https://i.gyazo.com/036a994f1f13962f3e844bcdeb12ff22.png)

新しい追加した change ノードから Notify ノードにつなぎます。

![image](https://i.gyazo.com/0e20f1fd0c46dde1af9e20e8de0945ec.png)

新しい追加した change ノードのプロパティはこのように変更します。

- 名前
  - 部屋が暗くなりました
- ルール
  - 値の代入 msg.payload
  - 対象の値
    - 部屋が暗くなりました

### 12-7-2 送るデータを変更する

![image](https://i.gyazo.com/d04b6ad6d4ea3176bc04b96c1bf407e4.png)

やっほーの inject ノードの値を 1 にしましょう。

- データタイプ
  - 数値
- 対象
  - msg.payload
- データ
  - 1

![image](https://i.gyazo.com/f11c61d044ea713ba53e5214e311caf7.png)

もうひとつ 0 のデータを送るために inject ノードを加えます。

![image](https://i.gyazo.com/d89fdcdc990ad7f1b19721e674dc5486.png)

新しく追加した inject ノードをswitch ノードにつなぎます。

![image](https://i.gyazo.com/72422fbb88dc9627cb2ee2dc1f0c3eb5.png)

新しく追加した inject ノードの値を 0 にしましょう。

- データタイプ
  - 数値
- 対象
  - msg.payload
- データ
  - 0

![image](https://i.gyazo.com/4955dc7c44544a9736ba4d72b7d51253.png)

設定できるとこのようなフローの見た目になっているはずです。

![image](https://i.gyazo.com/943b4630e0163a28b3c7973b4d060418.png)

設定ができたらデプロイします。

![image](https://i.gyazo.com/660074c0d2082b98c9dcb104ea445a5f.png)

0 と 1 の inject ノードを交互にクリックして通知で届くメッセージの内容が変わるか体験してみましょう。

## 12-8 MQTT 連携

![image](https://i.gyazo.com/ef055a37f15a994de1702b7f3c80c06e.png)

自分の MQTT ブローカーと接続し自前で 0 と 1 のメッセージを送るようにしましょう。

![image](https://i.gyazo.com/c022fb7bfb5259b1996709b93161f35d.png)

このように、今回のフローと自分の MQTT ブローカーと接続し 0 と 1 のメッセージを送るようにしましょう。

![image](https://i.gyazo.com/274d6378212035572852ee8da221b02b.png)

mqtt out ノードをワークスペースに配置します。

![image](https://i.gyazo.com/c389fea410699800f1092bb389fcb385.png)

mqtt out ノードのプロパティを自分の MQTT ブローカーのトピック ttc2022/res に送信されるように設定します。

- サーバ
  - My MQTT Broker
- トピック
  - ttc2022/res

![image](https://i.gyazo.com/90058948834679c4e99396a562065876.png)

mqtt out ノードに inject ノードを 2 つつなげて、さきほどの switch ノードに 0 や 1 の通史を送ったように、ひとつは 1 の数値を送るように、もうひとつは 0 の数値を送るように設定しつなぎます。

![image](https://i.gyazo.com/943b4630e0163a28b3c7973b4d060418.png)

設定ができたらデプロイします。

![image](https://i.gyazo.com/1de4b33663a56d865da80d048bb0c24e.png)

設定できるとこのようなフローの見た目になっているはずです。

## 12-9 MQTTとフロー連絡

MQTT からメッセージを送り Node-RED 経由で LINE Notify にメッセージします。

mqtt out ノードから来たデータを mqtt in ノードで自前で受け取って、「部屋が明るくなりました」「部屋が暗くなりました」のフローにつなぎます。

![image](https://i.gyazo.com/2db8e4f562c55008ddabf347a6c2e888.png)

switch ノードの左上あたりに mqtt in ノードを配置します。

![image](https://i.gyazo.com/591f390c9a1554e7f63b93ecb2ffecf4.png)

mqtt in ノードのプロパティはこのように変更します。

- サーバ
  - My MQTT Broker
- トピック
  - ttc2022/res

![image](https://i.gyazo.com/2b6190174aed5f653f8c2ec29412ee42.png)

mqtt in ノードと switch ノードをつなぎます。

![image](https://i.gyazo.com/83732b57a20750e7690186f758654358.png)

mqtt in ノードに来たデータを確かめるために debug ノードもつないでおきます。

![image](https://i.gyazo.com/943b4630e0163a28b3c7973b4d060418.png)

設定ができたらデプロイします。

![image](https://i.gyazo.com/61937e5525231030d3836f7aa286fb06.png)

設定できるとこのようなフローの見た目になっているはずです。

![image](https://i.gyazo.com/96e55b896c5ed27c74f678a4c371aa01.png)

mqtt out ノードにつながっている 0 と 1 の inject ノードを交互にクリックします。

![image](https://i.gyazo.com/90a001e4dba7684e24cf01388eccb2a7.png)

通知で届くメッセージの内容が変わるか体験してみましょう。

## 12-9 次の授業の準備

![image](https://i.gyazo.com/265cbce628625903232b6ac0ea992175.png)

次の授業のために、明るさセンサーの仕組み（回路）を準備します。

![image](https://i.gyazo.com/fa7747862927454bf64c9866d5cc1fa7.jpg)

以前行なった明るさセンサー値を取得するプログラムをデバイスに書き込み準備します。

→ [第9回の仕組み](../lecture09/00-introduction.md)