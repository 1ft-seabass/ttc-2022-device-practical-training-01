# 第5回 HTTP フロー作成の演習

## HTTP について

HTTP プロトコルについて概要を把握します。

- 教材
  - サブテキスト

HTTP は Hypertext Transfer Protocol という正式名称です。 Web ブラウザが Web サーバと通信する際に主として使用する通信プロトコルです。

よくある例としては、みなさんが Web ブラウザからアドレスバーで URL を入力して HTML などのテキストによって記述された Web ページなどのコンテンツを表示するときのデータの送受信に用いられます。

参考文献
- Hypertext Transfer Protocol - Wikipedia
  - https://ja.wikipedia.org/wiki/Hypertext_Transfer_Protocol
- HTTP の基本 - HTTP | MDN
  - https://developer.mozilla.org/ja/docs/Web/HTTP/Basics_of_HTTP

実際には、このような仕組みになっています。

> HTTPはリクエスト-レスポンス型のプロトコルであり、クライアントがサーバにリクエストメッセージを送信する。 基本的な考え方は非常に単純で、「何を」「どうして」欲しいのかを伝える。URLが「何を」、メソッドが「どうして」に当たる。 サーバはこれにレスポンスメッセージを返し、基本的にこの時点で初期状態に戻る。つまり、サーバはクライアントの状態を保存しない。
>
> Hypertext Transfer Protocol - Wikipedia - https://ja.wikipedia.org/wiki/Hypertext_Transfer_Protocol

この説明は、仕様をちゃんと説明してはいるのですが、ちょっととっつきにくいかもしれません。もう少し、噛み砕いていきましょう。

![image](https://i.gyazo.com/8d8b5bcd165aa9851160c0aeac32169d.png)

こちらの図を見つつ、[典型的な HTTP セッション](https://developer.mozilla.org/ja/docs/Web/HTTP/Session) を追っていきます。

まず、クライアントからサーバーへ URL で「何か」決めて問い合わせます。また、HTTP ヘッダーでクライアントからサーバーが追加情報を渡すことができます。

- HTTP メソッド
  - リソースに対して実行したいアクションを宣言します。いろいろありますが GET と POST を使うことが多いです。
  - https://developer.mozilla.org/ja/docs/Web/HTTP/Headers
- HTTP ヘッダー
  - HTTP リクエストやレスポンスでクライアントやサーバーが追加情報を渡すことができます
  - https://developer.mozilla.org/ja/docs/Web/HTTP/Headers

![image](https://i.gyazo.com/03d1c316f872a525a4bb30e7fffa412a.png)


そして、サーバーが HTTP リクエストから受け取った内容で、今度は HTTP レスポンスという形で応答します。こちらの図を見つつ、[典型的な HTTP セッション](https://developer.mozilla.org/ja/docs/Web/HTTP/Session) を追っていきます。

まず、HTTP ヘッダーでサーバーからクライアントへ追加情報を渡すことができます。そして、HTTP 応答ステータスコードで正常に完了したどうかを伝えます。こちらを、みなさんのブラウザが受信すると Web ページが表示されます。

- HTTP 応答ステータスコード（HTTP レスポンスステータスコード）
  - 特定の HTTP リクエストが正常に完了したどうかを示します。200 が Success で応答成功です。その他に、有名なものとして 404 , 500 , 503 などがあります。
  - 404 Not Found
    - サーバーがリクエストされたリソースを発見できないこと
  - 500 Internal Server Error
    - サーバー側で処理方法がわからない事態が発生したことを示します。
  - 503 Service Unavailable
    - サーバーはリクエストを処理する準備ができていないことを示します。
  - 参考文献（一覧はこちら）
    - https://developer.mozilla.org/ja/docs/Web/HTTP/Status

全体の図としては以下の通りです。

![image](https://i.gyazo.com/6052386b6f5bdf2b17b7692149fd2d92.png)

本来、みなさんのブラウザで URL にアクセスして何かしらが表示されるまでには、このような流れで行われています。いろいろありますね。

ですが、今回はすべて覚える必要はないです。 Node-RED で HTTP プロトコルを扱うために、ざっくりこのような流れになっているんだなと理解できていれば OK です。

Node-RED はこのあたりをすべてノードとして用意されています。今回の話を思い出しながら、実際に手を動かしつつ、理解を深めていきましょう。

## HTTP 関連ノード

Node-RED の HTTP 関連ノードを把握します。

- 教材
  - サブテキスト

![image](https://i.gyazo.com/ca582e17aeb4de45625760c773071930.png)

まず、パレットのネットワークというカテゴリを見てみましょう。こちらには、HTTP だけでなく他のプロトコルのノードも揃っています。

![image](https://i.gyazo.com/0564898e622f8e2a865a2d0b7c0af39a.png)

その中でも HTTP 関連ノードは 3 つあります。

- http in
  - HTTPエンドポイントを作成し、Webサービスを構成します。
- http response
  - HTTP Inノードで受け付けたリクエストに対するレスポンスを送り返します。
- http request
  - HTTPリクエストを送信し、レスポンスを返します。

こちらを使って HTTP のフローを体験していきましょう。


## HTTP レスポンスフロー概要

HTTP レスポンスフローの流れを把握します。

- 教材
  - テキスト 3.4 P.46

## HTTP レスポンスフロー作成

HTTP レスポンスフローを作成し動かします。

- 教材
  - テキスト 3.4 P.46-50

## template ノード追加

template ノードでHTTP レスポンスの見た目を変更します。

- 教材
  - テキスト 3.4 P.50-53

## HTTP API について

HTTP API の重要性や世界観を学びます。

- 教材
  - サブテキスト

さて、HTTP プロトコルは Web 上で重要な役割ですが、その中でも API という世界観を把握しておきましょう。

API とは、 Application Programming Interface の頭文字です。データを提供したり、何かしらの機能を提供するソフトウェアの一部を、私たちのような外部の人間が扱えるように公開されている窓口です。HTTP プロトコルでやり取りしていることが多いです。

たとえば、WEBアプリケーションなどインターネットの様々な仕組みを構築するとき、 API からデータを取得して加工して表示することが多いです。データや機能を借り受けるということですね。

## サンプル API 解説

今回のつなぐ サンプル API について把握します。

- 教材
  - サブテキスト

かわいい柴犬画像をランダムに返答してくれる shibe.online というAPIを使ってみましょう。

![image](https://i.gyazo.com/ffdaa58d8fb284e2d0095d4ba8f60d8b.png)

https://shibe.online/ こちらです。

HTTP リクエストの仕様として読み解くと以下のようになります。

* HTTP リクエスト方法
  * GET メソッド
* アクセスする API の URL
  * http://shibe.online/api/shibes

これのみです。追加で設定すべきパラメータもなく、これは、GET リクエストのためブラウザからアクセスでき、とても扱いやすいAPIです。

## HTTP リクエストフロー概要

今回の API に接続しデータを取得する流れを学びます。

- 教材
  - サブテキスト

![image](https://i.gyazo.com/baedc63f4a27f63eb33277aeb49481eb.png)

まず、パレットから http request ノードをワークスペースにドラッグアンドドロップしましょう。

![image](https://i.gyazo.com/c408d12ed4e8cac8f21f908895ec1ba6.png)

http request ノードをワークスペースに配置しました。

![image](https://i.gyazo.com/247a57dbff5c98d92558dc25d8c8a7bb.png)

inject ノードをワークスペースに配置して、動かすきっかけを指示できるようにします。

![image](https://i.gyazo.com/c7fa03567191282fe7dda707b2755b90.png)

debug ノードをワークスペースに配置して http request ノードが、どこかのURLにアクセスして取得したデータをデバッグタブに表示できるようにします。

![image](https://i.gyazo.com/79d9e7553396c09fb9d2daf96a726d20.png)

inject ノード → http request ノード → debug ノード とつなぎます。

これで「何かの API につなぐ」仕組みはひとまず出来上がりました。

## HTTP リクエストフロー作成

今回のAPI に接続する HTTP リクエストフローを作成します。

- 教材
  - サブテキスト

![image](https://i.gyazo.com/5eedcc78773990656fca5301fbc7acf4.png)

さきほどのワークスペースに戻って http request ノードをダブルクリックして詳細の設定をしましょう。

![image](https://i.gyazo.com/9c1791d6a5975656247eecd4992aa495.png)

このような設定項目があります。HTTP リクエストをするために様々な設定があります。

![image](https://i.gyazo.com/ace03d6fefff738b0df25119c855e122.png)

今回は

| 項目名 | 変更する内容 |
| --- | --- |
| メソッド | GET |
| URL   | http://shibe.online/api/shibes |


で設定します。

完了をクリックします。

![image](https://i.gyazo.com/2bdb7bcee8bd0219254ac90c8fe8e91f.png)

デプロイをクリックして Node-RED に設定を反映させます。

### 動かしてみる

![image](https://i.gyazo.com/d02727178bb7fb092a36642e2eb0d9ee.png)

それでは inject ノードの ![image](https://i.gyazo.com/917722feaa1444c55f1a19ece002757d.png) のボタンをクリックしましょう。

![image](https://i.gyazo.com/e14573b0bc320cc1788a7da6e49cb27d.png)

サイドバーのデバッグタブには、柴犬画像APIからリクエストが表示されます。

### 返答データを文字列からJSONに変更する

![image](https://i.gyazo.com/c62e6add7dce215f1ba6a586783c66ad.png)

現状では取得したデータは文字列です。今後扱いやすいようにJSONに変更しましょう。

文字列のままだと頑張って読んで探して取り出す必要がありますが、JSONデータで受け取れると入れ子構造で目的のデータが取り出しやすくなります。

それでは、http request ノードをダブルクリックをしてプロパティ編集画面を表示します。

![image](https://i.gyazo.com/1ecc81ac7419329c1b33ca3d5915e6d5.png)

http request ノードの設定の `出力形式` をUTF文字列から `JSONオブジェクト` 変更します。

![image](https://i.gyazo.com/d51b5faaace99acf648a267bb27b91c9.png)

すると、文字列ができるかぎり JSON に変換されます。

![image](https://i.gyazo.com/534bb947897bd27e2a15a946df46e3fe.png)

ためしに、fileにある柴犬画像URLをコピーして

![image](https://i.gyazo.com/4474f4c2d24782d82ac5674162877792.png)

ブラウザのアドレスバーにペーストしてアクセスしてみましょう。

![image](https://i.gyazo.com/0390ba400e7bc4ef1b68c19dbdbd3b55.jpg)

無事、柴犬画像が見れていますね！

### 時間があれば（エクストラ）

node-red-contrib-image-output ノードをインストールして画像表示をします。

[Node-RED で public-apis の柴犬画像 API につないで表示させるメモ – 1ft-seabass.jp.MEMO](https://www.1ft-seabass.jp/memo/2020/09/04/nodered-connect-shibainu/)

## HTTP API の多様さ

様々な HTTP API の種類や役割を把握します。

- 教材
  - サブテキスト

[![Image from Gyazo](https://i.gyazo.com/ca62ef1b64e4d0b133bfe8491b36d000.png)](https://gyazo.com/ca62ef1b64e4d0b133bfe8491b36d000)

さて、こちらの図は、私が使ったことのある API や知っている API をまとめてみたものです。

みなさんもイチから仕組みを構築してシステムをつくることももちろん大事ですが、このように API を知ることで、データを用意出来たり、ひとりでは難しい仕組みを導入出来たり、API を通じて新しい技術に触れることができます。

そして、フリーのAPIのリストコレクション [public\-apis](https://github.com/public-apis/public-apis) をご紹介します。

![image](https://i.gyazo.com/b3c1f4c2b1625cba88d3e862fcb7570e.png)

英語ですが、実に 100 以上の API があり見ているだけで楽しいです。私が図で示したような広がりが、実感できるでしょう。

このような、API をはじめとした、すぐに作れるツールやアプローチを知っていることで、よりプロトタイピングが磨かれるので、手を動かしつつ技術に触れつつ、鍛えていきましょう。