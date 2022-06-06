# 第6回 MQTT プロトコル

## MQTT プロトコル仕様

MQTT プロトコルの仕様を把握します

- 教材
  - サブテキスト

MQTTは、モノのインターネット（IoT）用に作られたメッセージングプロトコルです。非常に軽量にデータがやり取りできるよう仕様側で設計されており、稼働時に占有・消費するが小さく運用できます。IoT では送受信するデータが少ないことが多く、とても向いています。

また、ネットワーク帯域幅が最小（ネットワークが細く・遅い）状況でも、リモートでセンサーやデバイスを接続するのに最適です。

MQTT のくわしい使い方は、MQTT の仕様を伝える有名な Web サイト MQTT.org https://mqtt.org/ をみていきましょう。

パブリッシュ/サブスクライブ


http://devcenter.magellanic-clouds.com/learning/mqtt-spec.html

## MQTT 利用シーン

IoT における MQTT の利用シーンを把握します。

- 教材
  - サブテキスト

## MQTT ノード概要

Node-RED の MQTT ノードについて把握します。

- 教材
  - サブテキスト

![image](https://i.gyazo.com/89a0ad3dcc8b67042cc9c85352aae382.png)

パレットには MQTT 関連のノードとして MQTT の購読（Subscriber）として機能する mqtt in ノードと、MQTT の発行（Publisher）として機能する mqtt out ノードがあります。

## MQTT ブローカー

教材の MQTT ブローカーを把握します。

- 教材
  - サブテキスト

今回の教材では、講師が事前に用意した [beebotte](https://beebotte.com/) の MQTT ブローカーを生徒のみなさんで共有して使います。

設定情報については、このあと Slack で共有していきます。

## MQTT ノード設定

MQTT ノードの接続設定を把握します。

- 教材
  - サブテキスト

![image](https://i.gyazo.com/0d1c0dba7b9b6816eaa89cccfdc4da15.png)

MQTT ノードの接続設定は、mqtt in ノード・mqtt out ノードのプロパティで、サーバという項目があり、そこで新規に mqtt-broker を追加して行います。

![image](https://i.gyazo.com/8e6eb36270d3841a77da3a368f22c21a.png)

接続するためにこのような設定を行って行きます。いまは、手を動かさず、こういう設定があるんだなという把握でOKです。

このあと手を動かして、実際に接続していきましょう。

## MQTT 受信フロー作成

MQTT ノードを使った受信フローを作成します。

- 教材
  - サブテキスト

![image](https://i.gyazo.com/e22e638df81b888483fc03b89fc4fbf1.png)

パレットから mqtt in ノードを配置します。

![image](https://i.gyazo.com/57813ce841e819dde0408263fce0663f.png)

パレットから debug ノードを配置します。

![image](https://i.gyazo.com/959f9db988047a31f71bac567ddcb32e.png)

mqtt in ノードとdebug ノードをつなぎます。

![image](https://i.gyazo.com/cdbd10e9b9de19cd4788c94fc2b44e2c.png)

mqtt in ノードをダブルクリックしてプロパティを表示します。

![image](https://i.gyazo.com/0158881fc593d0e7dcc60086cdb26c6b.png)

サーバが「新規に mqtt-broker を追加」と選択されていることを確認し、鉛筆ボタンを押して編集します。

![image](https://i.gyazo.com/1d6631c72466a9b06266d963c8dd8360.png)

mqtt-broker 設定のプロパティです。

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

![image](https://i.gyazo.com/aee27081639de637775784d8253d235d.png)

最後にトピックを

- トピック
  - ttc2022/res

にします。

設定できたら、完了をクリックします。

- 参考文献
  - Beebotte の MQTT ブローカーと Node-RED の MQTT ノードでやり取りをするメモ – 1ft-seabass.jp.MEMO
    - https://www.1ft-seabass.jp/memo/2022/02/28/connecting-beebotte-using-nodered/

## MQTT 接続確認

接続状況をノードのインジケータで動作確認します。

- 教材
  - サブテキスト

![image](https://i.gyazo.com/eab4be1c4e188aee9581749553399a00.png)

設定ができたら、デプロイをクリックして反映させます。

![image](https://i.gyazo.com/4d2a3b9511d6fcf2c79cac35d42d8abd.png)

mqtt in ノードの下部に「接続済」と表示されていれば、接続成功です。

## MQTT 送信フロー更新

データを送信するフローに更新します。

- 教材
  - サブテキスト

## MQTT 送信フロー確認

データを送信するフローを確認します。

- 教材
  - サブテキスト

## MQTT ブローカー紹介

今回利用しているブローカの紹介とアカウント取得を行います。

- 教材
  - サブテキスト