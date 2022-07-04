# LINE Notify API 演習

## 演習概要

今回の Node-RED 動作の大まかな流れを把握します。

![image](https://i.gyazo.com/5e069bdbcfa1b742ebc6e60aebcf6fab.png)


## フロー準備

今回の Node-RED フローを作成します。

### ひとまずフローを全部選択して削除します

![image](https://i.gyazo.com/a4540fb1b4ae851b96978b5916dcd434.png)

まず、今回の 2 回の授業でつくるフローに集中するため、マウスでドラッグして選択して DELETE キーを押して以前のフローを削除します。

MQTT の設定については、ちゃんと保持されているので大丈夫です。

![image](https://i.gyazo.com/8325d656243200bdb6a3038fe4185eb8.png)

右下の + や - 、ナビデータで全体を確認してちゃんと削除できているか、確認しましょう。

## インストール

Node-RED で node-red-contrib-line-messaging-api ノードをインストールします。

![image](https://i.gyazo.com/cefbac6bf2f4ed2a7bcd43668754d2a8.png)

インストール方法については、メインテキスト 4.1 「ノードの追加」を確認します。

### node-red-contrib-line-messaging-api のインストール

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

## フロー作成

![image](https://i.gyazo.com/bd32b73de73d9cd164aefba556330a1a.png)

inject ノードと Notify ノードでこのようなフローを作成します。

### inject ノード設定

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

### Notify ノード設定

事前に前回設定した LINE Notify トークンを用意しましょう。

今回の Node-RED フローの LINE Notify 設定を行います。

![image](https://i.gyazo.com/bd32b73de73d9cd164aefba556330a1a.png)

Notify ノードをダブルクリックしてプロパティを設定します。

![image](https://i.gyazo.com/2e3da8b38259ba510ef150eab2cc6ec5.png)

LINE Notify ノードのプロパティで LINE Notify AccessToken 項目に入力して設定します。

## フロー確認

LINE Notify API の設定ができたか確認します。

## フロー実行

フローを動作させて LINE でメッセージを確認します。

## フロー変更1

今回の フローを変更し送信するメッセージを変えます。

TODO : inject ノードと change ノード
TODO : メインテキストにもあるよと伝える

## フロー変更2

今回のフローを変更し0/1値に応じたメッセージをします。

TODO : inject ノードと switch ノード

## MQTT 連携

今回のフローと自分の MQTT ブローカーと接続します。

## MQTTとフロー連絡

MQTT からメッセージを送り Node-RED 経由で LINE Notify にメッセージします。

TODO : 自前で送る形
TODO : 回路準備もしちゃおう

## 次の授業の準備

![image](https://i.gyazo.com/265cbce628625903232b6ac0ea992175.png)

次の授業のために明るさセンサーの仕組み（回路）を準備します。

![image](https://i.gyazo.com/fa7747862927454bf64c9866d5cc1fa7.jpg)

以前行なった明るさセンサー値を取得するプログラムをデバイスに書き込み準備します。

→ [第9回の仕組み](../lecture09/00-introduction.md)