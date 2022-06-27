# 第11回 LINE Notify API 基礎

## LINE Notify とは

LINE Notify の大まかな仕組みを把握します。

## IoT における通知

LINE Notify のような IoT における通知の重要性を把握します。

## LINE Notify 事例1

LINE Notify に関する使いどころ（ユースケース）を個人面で把握します

## LINE Notify 事例2

LINE Notify に関する使いどころ（ユースケース）をIoT事例面で把握します

## LINE アカウント確認

LINE アカウントとスマホアプリインストールを確認します。

## LINE Notify サイトログイン

LINE Notify サイトにログインしアカウント確認をします。

## LINE Notify 設定の取得

LINE Notify 設定しトークンの取得を行います。

![image](https://i.gyazo.com/c45ee309aa6793bc12f67c24f3a905ce.png)

https://notify-bot.line.me/ja/ からログインします。

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

![image](https://i.gyazo.com/2fcf2f7f0d039737510759301a619485.png)

リストに追加されたことを確認しておきます。

![image](https://i.gyazo.com/07a33eec5562fc6fd67e52aeaa5c2bc9.png)

今回選択した LINE Notify 先のアカウントにこのようなメッセージが来ていることも確認します。

## LINE Notify 設定の確認

LINE で LINE Notify 設定されたかメッセージ確認を行います。

## LINE Notify の技術仕様

LINE Notify の技術的な仕様やメッセージデータを確認します。

## LINE Notify のツール

PC版アプリのツールを把握します。