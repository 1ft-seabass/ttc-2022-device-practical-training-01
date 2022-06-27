# 第11回 LINE Notify API 基礎

![image](https://i.gyazo.com/078142258b3c0026c184d54eda2ccba9.jpg)

まず、今日は LINE アプリを使っていくので、手元のスマホで LINE アプリがあるか確認しましょう。

## 11-1 LINE Notify とは

LINE Notify の大まかな仕組みを把握します。

![image](https://i.gyazo.com/5ee7b4482f1b28caaf860e72744cd2f5.png)

LINE Notify https://notify-bot.line.me/ja/

> Webサービスと連携すると、LINEが提供する公式アカウント"LINE Notify"から通知が届きます。
> 複数のサービスと連携でき、グループでも通知を受信することが可能です。

![image](https://i.gyazo.com/8dddc3621b4a77af65be36d7907cd02a.png)

つまり「LINE Notifyと連携を行うことで、LINEユーザーが簡単にサービスの通知を受信できるようになります」

## 11-2 IoT における通知

LINE Notify のような IoT における通知の重要性を把握します。

![image](https://i.gyazo.com/9e70b598a6e055b9b1a7ddab800f6f8a.png)

自分の LINE に通知としてメッセージを受け取ることができる仕組みです。

- 自分から見に行かなくてもメッセージで知らせてくれる仕組み
- 複数人に一斉にメッセージを受け取る仕組み
- 何かしらの情報をまとめて知らせてくれる仕組み

といったものを作ることができます。

自分たちが設定した情報だけを手軽に LINE ユーザーに配信できるので、WEB アプリの仕組みと相性がよく「こういう通知内容は実際役に立つだろうか？」といった形で、自分たちの考えた発想を試しやすいです。

また、そういったメッセージを受け付ける部分を LINE に任せることで、LINE アプリの使い慣れた洗練されたレイアウトで、すぐにメッセージを表示できることも良い点です。

もし、このレベルに使いやすい仕組みを自分でイチからつくるとなると、WEB サーバーの知識・HTML/CSS/JavaScript といった WEB 表示の知識・セキュリティへの配慮・多くのユーザーがいる状況などなど整えるべきことが数多くあります。「こういう通知内容は実際役に立つだろうか？」というシンプルな試行錯誤をするまでに、たくさんの時間がかかります。

このあたりを、LINE Nofity および LINE アプリで、すぐに試せるというのは、自分たちの構想を試して良くしていくときには強い味方になります。

## 11-3 LINE Notify 事例

LINE Notify に関する使いどころ（ユースケース）を個人面・IoT事例面で把握します

- 個人面
  - 自分の興味のありそうなカテゴリのニュースを定期的に通知
  - 家族共有の Google カレンダーが更新されると通知して共有
- IoT事例面
  - 温度・湿度センサーを設置しておき熱中症アラートを出す（冷房を促すこともセットで）
  - CO2 センサーを設置しておき一定量の濃度に到達したら換気を促す
  - 新生児の健康指標事例
    - https://www.1ft-seabass.jp/memo/2019/11/06/unko-button-getting-start/
    - https://www.1ft-seabass.jp/memo/2020/07/13/summary-of-oyako-tech-lt/
  - 事例
    - https://speakerdeck.com/1ftseabass/developers-summit-2021

## 11-4 LINE アカウント確認

<img src="https://guide.line.me/ja/install_5.png" width="200" />

LINE アカウントとスマホアプリインストールを確認します。

## LINE Notify サイトログイン

LINE Notify サイトにログインしアカウント確認をします。

![image](https://i.gyazo.com/c45ee309aa6793bc12f67c24f3a905ce.png)

https://notify-bot.line.me/ja/ に、まずアクセスします。

![image](https://i.gyazo.com/043d433bfa913e2edaee4bb917e92bb2.png)

右上のログインをクリック。

![image](https://i.gyazo.com/d2a7444465cb56a81eedb3e957403806.png)

下部の QR コードログインをクリックします。（メールアドレス・パスワードは、おそらくみなさん設定していないのと、いまから設定をやるとなると、PCとアプリを行き来して、まあまあ大変になるので今回は避けます。）

![image](https://i.gyazo.com/a6834bc86db3d0f024a0cb5886664883.png)

QR コードが表示されます。 LINE アプリでスキャンするとログインできます。QR コードのスキャン方法は下部のリンクをクリックすると表示されます。

![image](https://i.gyazo.com/e3856b10d3a1b933f284f7f81f3fac64.png)

## 11-5 LINE Notify 設定の取得

LINE Notify 設定しトークンの取得を行います。

![image](https://i.gyazo.com/bf26cdcf093a783aee4ff510ec9ddb68.png)

ログインすると、右上にアカウント名が出るのでクリックします。

![image](https://i.gyazo.com/7cdb07c7e588bac278a5fb0b2dbc9d83.png)

マイページをクリック。

![image](https://i.gyazo.com/0c48f49af1be4e5e7c789366c0b838cf.png)

マイページの下の方に「アクセストークンの発行(開発者向け)」というエリアがあるのでスクロールします。

![image](https://i.gyazo.com/bbba9909e0437e487718479953b198ff.png)

トークンを発行するボタンをクリックします。

![image](https://i.gyazo.com/05b98371bcae556f578cdb96505ecb7c.jpg)

トークンを発行するウィンドウが表示されるので、以下のように対応します。

- トークン名を記入してください (通知の際に表示されます)
  - `M5Stack Notify` と入力
- 通知を送信するトークルームを選択してください
  - `1:1でLINE Notifyから通知を受け取る` を選択

こちらを対応すると、発行するボタンが押せるようになるのでクリックします。

![image](https://i.gyazo.com/abee7f38d2db6897c61cdb42fc29a83c.png)

このようにトークンが表示されるのでメモしましょう。

**このページから移動すると、新しく発行されたトークンは二度と表示されないので気をつけましょう**

メモしたらウィンドウを閉じるボタンをクリックして閉じます。

## 11-6 LINE Notify 設定の確認

LINE で LINE Notify 設定されたかメッセージ確認を行います。

![image](https://i.gyazo.com/2fcf2f7f0d039737510759301a619485.png)

リストに追加されたことを確認しておきます。

![image](https://i.gyazo.com/07a33eec5562fc6fd67e52aeaa5c2bc9.png)

今回選択した LINE Notify 先のアカウントにこのようなメッセージが来ていることも確認します。このように、LINE Notify API のアクセストークンの発行されると LINE アプリに Personal Access Token 発行の通知が来ます。

## 11-7 LINE Notify の技術仕様

LINE Notify の技術的な仕様やメッセージデータを確認します。

### 11-7-1 技術的な仕様やドキュメント

LINE Notify API のデータのやり取りは HTTP プロトコルで行います。 

![image](https://i.gyazo.com/279081acd57f3204852561b29cab2aef.png)

ドキュメントは LINE Notify サイトから確認できます。

- https://notify-bot.line.me/ja/

![image](https://i.gyazo.com/6865fb59897f753ac0e2f0eec54e6739.png)

こんな感じです。

### 11-7-2 通知系を把握していこう

![image](https://i.gyazo.com/8d51aa1bceb0f9b8531a879bc8d11ef8.png)

ドキュメントのつくりとして、はじめに「API 全体の流れと、実装の必要な箇所について」や「認証系」がありますが、今回はメッセージのやり取りを行う「通知系」をみていきます。

いままで勉強した HTTP の知識で一緒に読み解いていきましょう。

![image](https://i.gyazo.com/2717cf9a01715977b1a52f20243d0280.png)

リクエスト方法、必要なヘッダーを把握します。

- LINE への通知のためのAPI
  - メソッド
    - POST
  - URL
    - https://notify-api.line.me/api/notify

![image](https://i.gyazo.com/26199a652d191b61f11b0a747fe3285d.png)

送信できるデータはリクエストパラメータで確認できます。テキスト・画像・スタンプを送ることができます。

![image](https://i.gyazo.com/433127ff3540c8c9aab3ed4e37e934be.png)

各サービスごとに1時間にAPIをcallできる回数の上限 API Rate Limit も注意しましょう。

## 11-8 LINE Notify のツール

PC版アプリのツールを把握します。

![image](https://i.gyazo.com/895157df89c2ef3c8127e202c065eb76.png)

- パソコンでLINEを利用する｜LINEみんなの使い方ガイド
  - https://guide.line.me/ja/services/pc-line.html

こちらをみつつ、インストールしていきましょう。

![image](https://i.gyazo.com/a9812231b44c092ae5c3b7a072207e7a.png)

QR コードログインがおススメです。