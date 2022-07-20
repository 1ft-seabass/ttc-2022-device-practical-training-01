# 第7回 MQTT データ連携演習

## MQTT の送受信基礎

- 教材
  - サブテキスト
    - https://zenn.dev/tseigo/books/node-red-with-arduino-device-simple-version/viewer/mqtt-topic
  - 内容
    - MQTT 送受信の概要
      - MQTT の送受信に関して大きく概念を理解する

## サブスクライブフロー作成

Node-RED でデータ受信フローを作成します。

- 教材
  - サブテキスト

![image](https://i.gyazo.com/1ffdb3ae405928f949d269038150fcf0.png)

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

![image](https://i.gyazo.com/2c867f0781aabab1cc600c80b44353d7.png)

講師の MQTT ブローカーを経由して、同じく MQTT ブローカーとつながったオンラインの表示の仕組みやデバイスに情報を送ってみましょう。

### フロー作成

![image](https://i.gyazo.com/e79c4ec88edd9e85db67728bd0798c8b.png)

今回は inject ノードと mqtt out ノードをワークスペースに配置します。

では MQTT ブローカに送るデータを設定します。

```js
{"name":"<name>","color":"<color>"}
```

- name
  - 半角英数字を使って自分の名前かハンドルネームを設定します。ひらがなや全角英数字はNG。
    - 例 : seigo , wombat10 など
- color
  - あらかじめ設定された半角英字の色の名前を設定します
    - blue
      - 青
    - red
      - 赤
    - green
      - 緑

たとえば、名前が seigo で、色の名前が赤の場合は

```js
{"name":"seigo","color":"red"}
```

となります。

inject ノードのプロパティで、このデータを送るよう設定します。

![image](https://i.gyazo.com/953ee274a6e595ac23c1b20bab9ed703.png)

- msg.payload の設定
  - `{}` マークの JSON オブジェクト指定します
  - 値を `{"name":"seigo","color":"red"}` のように設定します
    - この値は、皆さんの名前は独自のものにしましょう。（あとあとわかりやすくするため）

つづいて、mqtt out ノードのプロパティで、講師の MQTT ブローカを設定し、今回用のパブリッシュするトピックを設定します。

![image](https://i.gyazo.com/3910a35c1e22a99077654316bf8de939.png)

- サーバ
  - Teacher MQTT Broker
- トピック
  - ttc2022/control

設定ができたら、

![image](https://i.gyazo.com/eab4be1c4e188aee9581749553399a00.png)

デプロイをクリックして反映させます。


## パブリッシュ実践

Node-RED でデータ送信フローを動かして確認します。

- 教材
  - サブテキスト

![image](https://i.gyazo.com/50e3dcf24ff12bfda1e952df3d2b3649.jpg)

ここで、講師の方で、オンラインの表示の仕組みやデバイスを用意します。

![image](https://i.gyazo.com/2c867f0781aabab1cc600c80b44353d7.png)

このように動きます。

- 後ろのオンラインの表示の仕組み
  - 講師 MQTT ブローカーと連携
  - 一番左上が最新で順々に、送られてきた名前と色を背景色を表示されます
  - 右下に最新の送信されたログが表示されます
- 前にある M5Stack というデバイス
  - 講師 MQTT ブローカーと連携
  - こちらも最新の送られてきた名前と色を背景色を表示されます

![image](https://i.gyazo.com/9fca1d19efdb2aa5aa49bc605ed70786.png)

inject ノードをクリックして、データを送って、オンラインの表示の仕組みやデバイスを変化させてみましょう。

うまくいったら、以下を試してみましょう。

- ほかの色に変えてみる
  - `{"name":"seigo","color":"red"}` → `{"name":"seigo","color":"green"}`
- 名前を変えてみる
  - `{"name":"seigo","color":"red"}` → `{"name":"SEIGO :)","color":"red"}` 

![image](https://i.gyazo.com/3b79f12b375b7ec426f8c47ed509fa02.png)

実は今回の仕組みは、enebular という Node-RED が動くサービスを利用して Node-RED のサーバーを立てて、オンラインの表示の仕組みやデバイス制御しています。

すべて Node-RED で動いているので、ぜひポテンシャルを感じてください。

ちなみに、この enebular という仕組みは、次の 3 期で学べます！お楽しみに！

## 次回への伝達事項

### Arduino バージョン

![image](https://i.gyazo.com/249398704d5d737e76ed55b6c5d0950d.png)

お使いの Arduino バージョンを教えてください（次回使います）

### Raspberry Pi で使った電子工作部品を使います

![image](https://i.gyazo.com/5eac04cc76655085a67aeb8cb39096d8.jpg)

LED や光センサーを使います。次回使うので忘れないようにしましょう。

### みなさん LINE アカウントもご用意を

![image](https://i.gyazo.com/fa35ba7fb83a6f6ffe3a380126043feb.jpg)

これは次々回で使うので、使ってない人は、アカウントを作っておきましょう。