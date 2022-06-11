# 第6回 MQTT プロトコル

## MQTT プロトコル仕様

MQTT プロトコルの仕様を把握します

- 教材
  - サブテキスト

MQTTは、モノのインターネット（IoT）用に作られたメッセージングプロトコルです。非常に軽量にデータがやり取りできるよう仕様側で設計されており、稼働時に占有・消費するが小さく運用できます。IoT では送受信するデータが少ないことが多く、とても向いています。

また、ネットワーク帯域幅が最小（ネットワークが細く・遅い）状況でも、リモートでセンサーやデバイスを接続するのに最適です。

![image](https://i.gyazo.com/56b2b9e564db928ebe70566f85d8e817.png)

MQTT のくわしい使い方は、MQTT の仕様を伝える有名な Web サイト MQTT.org https://mqtt.org/ をみていきましょう。


## MQTT 利用シーン

IoT における MQTT の利用シーンを把握します。

- 教材
  - サブテキスト

> ![image](https://i.gyazo.com/f3124e146e9d45c7baf844d7054220e2.png)
> 
> MQTT.org https://mqtt.org/ のトップページの翻訳

- 双方向制御するもの
- 数百万の IoT デバイスがつながっても稼働するもの
- 通信環境が悪い場合でも確実に送りたいもの
- データを軽量に効率的に送りたいもの

このあたりがポイントです。

- 大量にデバイスをつなぎセンサーデータを集めたいとき
- ロボットアームのような遠隔で何かしらを動かしたいとき
- 

![image](https://i.gyazo.com/3f18f61e5c1b8b93e1c61d2901aca1e2.jpg)

時間があれば MQTT.org のユースケース https://mqtt.org/use-cases/ も見ていきましょう。 

## MQTT ノード概要

Node-RED の MQTT ノードについて把握します。

- 教材
  - サブテキスト

![image](https://i.gyazo.com/89a0ad3dcc8b67042cc9c85352aae382.png)

パレットには MQTT 関連のノードとして MQTT の購読（Subscriber）として機能する mqtt in ノードと、MQTT の発行（Publisher）として機能する mqtt out ノードがあります。

技術的なくわしい用語や仕組みは次回説明するので、今回はまず動かすことで体験していきましょう。

## MQTT ブローカー

教材の MQTT ブローカーを把握します。

- 教材
  - サブテキスト

![image](https://i.gyazo.com/807b4351a8300dd22c0c7f47293c5888.jpg)

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

![image](https://i.gyazo.com/04239974c6ae9381dd86bd7eda8eef5a.png)

mqtt in ノードをつかって、まず MQTT ブローカに接続してデータを受信する準備を行いましょう。

![image](https://i.gyazo.com/e4295e95d66bdeb4145f01dd41faa6be.png)

パレットの mqtt in ノードを確認します。

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

すると、サーバの設定が mqtt.beebotte.com:1883 となっています。

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

### 受信を待つ

![image](https://i.gyazo.com/6163626b6ca2c315c7a884217f913c4a.png)

デバッグタブを表示します。

いまから、講師の方からデータを送るので、受信を待ちましょう。

## MQTT 送信フロー更新

つづいて、データを送信するフローに更新します。

- 教材
  - サブテキスト

![image](https://i.gyazo.com/784c57ac8a0f993e149e11ee9b72bd4c.png)

このように、現在作った mqtt in ノードで受信したデータを debug ノードで受け取るフローはそのままです。

![image](https://i.gyazo.com/59389203ec29843a423a20d2f6bc2401.png)

パレットの mqtt out ノードを確認します。

![image](https://i.gyazo.com/e01b81c4bded2133a5c86cd79a648e70.png)

パレットから mqtt out ノードを配置します。

![image](https://i.gyazo.com/05d1bbdc77ddf4e2a2501c1ea6889a50.png)

パレットから inject ノードを配置します。

![image](https://i.gyazo.com/f3a0ce187d32284939a3d2bc31102d82.png)

inject ノードと mqtt out ノードをつなぎます。

![image](https://i.gyazo.com/a7c8eb9660cc05ec348360b70d3e6c64.png)

mqtt out ノードをダブルクリックして、プロパティの設定を以下のようにします。

- サーバ
  - さきほど設定した mqtt.beebotte.com:1883 を選択
- トピック
  - ttc2022/res

![image](https://i.gyazo.com/6210b658702cdd05b9f5cb8002e1a4db.png)

設定できたら、完了ボタンをクリックします。

![image](https://i.gyazo.com/eab4be1c4e188aee9581749553399a00.png)

デプロイをクリックして反映させます。

## MQTT 送信フロー確認

データを送信するフローを確認します。

- 教材
  - サブテキスト

![image](https://i.gyazo.com/6163626b6ca2c315c7a884217f913c4a.png)

デバッグタブを表示します。

![image](https://i.gyazo.com/43afebfce493c0d072139356d9dd9c0b.png)

inject ノードのボタンをクリックします。

![image](https://i.gyazo.com/dc9d410e40acac94d53fc8006361c42f.png)

いまデータが大量に来るのは、生徒みんなが同じ場所（MQTTブローカー）につないでいて、同じトピックを購読して、さらに、そのトピックにデータを送っているので、そう見えています。

![image](https://i.gyazo.com/f478961c49c306bf87dfb99b919c6db0.png)

さらに、みなさんで自分のフローの inject ノードの送るデータを、文字列にして、自分の名前を含んだ自由メッセージに変更すると、より実感できるでしょう。

![image](https://i.gyazo.com/11954132a185cf8c6bc7c430310f9c1c.png)

たぶんカオス。

ということで、次の章で、自分の MQTT ブローカーを取得し、自分だけのデータをやりとりできるよう設定していきましょう。

## MQTT ブローカー

今回利用している MQTT ブローカの紹介とアカウント取得を行います。

- 教材
  - サブテキスト

### Beebotte

![image](https://i.gyazo.com/807b4351a8300dd22c0c7f47293c5888.jpg)

今回利用している MQTT ブローカーは Beebotte https://beebotte.com です。

リアルタイム接続オブジェクト用のクラウドプラットフォームで、IoT にも相性がよく REST、WebSocket、MQTTをサポートする豊富なAPIがあります。

今回は、このサービスの MQTT ブローカーを使います。

![image](https://i.gyazo.com/4402402ead31ebeb569764acd3651cc1.png)

2022 年 6 月現在、Free プランでも、

> Unlimited Channels  
> 50,000 Messages/day  
> 5,000 Persistent Messages/day  
> 3 Months History  
> SSL Encryption  

日本語に訳してみると、

> 無制限のチャンネル  
> 50,000メッセージ/日  
> 5,000永続メッセージ/日  
> 3ヶ月の履歴  
> SSL暗号化  

なので、ホビーレベルであれば、制限内でも十分に使えます。

![image](https://i.gyazo.com/9289e9a31fee68ba7e5787b0515908e8.png)

クレジットカードも必要とせず登録できるので、みなさんもはじめやすいでしょう。

### Beebotte アカウント登録

- MQTT Broker「Beebotte」のユーザ登録、チャネル作成、ダッシュボード作成｜IoT Gym
  - https://poche.xsrv.jp/iot-gym/2018/08/25/beebotte-sign-up/

早速、こちらを参考にアカウント登録をしてみましょう。

![image](https://i.gyazo.com/cfb7ddeadbc1461bef6f5fa886cd2e3a.png)

右上の Sign Up をクリックします。

![image](https://i.gyazo.com/ee7ee93c708a2eace46826700bfe371d.png)

情報を入力して SIGN UP ボタンをクリックします。

今回入力したメールが届くのでリンクをクリックしましょう。

![image](https://i.gyazo.com/cfb7ddeadbc1461bef6f5fa886cd2e3a.png)

これで、アカウント登録は完了するので、Sign In からログインしましょう。

![image](https://i.gyazo.com/9f8c04c8c3c67c5320204c258281bce6.png)

ログインできたらアカウント登録は成功です。

### Beebotte で 自分の MQTT ブローカー設定を作成

講師が作成した MQTT ブローカーを同じような設定で自分の MQTT ブローカーを設定しましょう。

![image](https://i.gyazo.com/156e37d87fea312fddf358d3c061512f.png)

ログインしたら、左のメニューから Channels をクリックします。

![image](https://i.gyazo.com/ab4d4fd369e43434746f42489e77f04e.png)

Create New ボタンをクリックします。

![image](https://i.gyazo.com/f946908028e4606db690125356c3a2e8.png)

- チャンネル名
  - ttc2022
- Configured Resources
  - resource name
    - res

と図のように設定して Create channel をクリックします。

![image](https://i.gyazo.com/bee21ed9bf0ebdf9622a35cc533619f3.png)

設定できると、リストに ttc2022 が現れます。タイトルをクリックしてみましょう。

![image](https://i.gyazo.com/86d93174aad525eb647ed2301e3abfd6.png)

クリックするとチャンネルの詳細が表示されるので、

- Configured resources に res があること確認
- Channel Token の赤文字全部をメモ

をしておきましょう。

### 自分の MQTT ブローカー設定に Node-RED を変更する

さきほどメモした Channel Token を反映すれば、講師の MQTT ブローカーから、自分の取得した MQTT ブローカーに切り替わります。

![image](https://i.gyazo.com/59b936f0a076ffc538b6a2210cc2e826.png)

mqtt in ノードをダブルクリックしてプロパティを表示します。

![image](https://i.gyazo.com/7253afa06ab3a1ebd2744a640967205d.png)

サーバが mqtt.beebotte.com:1883 となっていることを確認して鉛筆ボタンをクリックします。

![image](https://i.gyazo.com/b0cfa4cc219b65306965532eecdf6209.png)

MQTTブローカーノードの設定 > セキュリティで、ユーザ名のところを、自分の取得した MQTT ブローカーの Channel Token に置き換えます。

更新ボタンをクリックして、mqtt in ノードのプロパティに戻り、完了ボタンをクリックします。

![image](https://i.gyazo.com/eab4be1c4e188aee9581749553399a00.png)

デプロイをクリックして反映させます。

### 動作確認

![image](https://i.gyazo.com/6163626b6ca2c315c7a884217f913c4a.png)

デバッグタブを表示します。

![image](https://i.gyazo.com/43afebfce493c0d072139356d9dd9c0b.png)

inject ノードのボタンをクリックします。

![image](https://i.gyazo.com/6f5d8545b5a2682811a8735d8d40a135.png)

今回は自分の送ったデータが来ることが確認できるはずです。