# センサー通知実習

## 13-1 演習概要

今回の Node-RED 動作の大まかな流れを把握します。

![image](https://i.gyazo.com/d69f0a82e9d9ecb77b6c5ddeea4cd435.png)

[第9回の仕組み](../lecture09/00-introduction.md) で取得した部屋の明るさをセンサーが捉えて、Node-RED に送りその明るさに応じて LINE Notify ノードによって LINE アプリに通知を送ります。

## 13-2 デバイス準備 → 書き込み → デバイス動作確認

![image](https://i.gyazo.com/fa7747862927454bf64c9866d5cc1fa7.jpg)

以前行なったセンサー値を取得するプログラムをデバイスに書き込み準備します。

→ [第9回の仕組み](../lecture09/00-introduction.md)

## 13-3 データ受信確認

Node-RED がデバイスからデータ受信できてるか部分確認します。

![image](https://i.gyazo.com/dc535bb8fc74717cf0441b7c11348028.png)

前回使ったフローで mqtt in ノード につながった debug ノードに注目します。

![image](https://i.gyazo.com/96991ded5dabcf495debac5c0e262207.png)

デバイスに電源を入れてみてデータが受信されていることを確認します。

## 13-4 LINE Notify フロー追加

Node-RED LINE Notify 連携部分のフローを追加します。

![image](https://i.gyazo.com/f9ff2247fb72dedf9ccfe98e4edf291b.png)

現在の状態だと、switch ノードがセンサー値の値ではなく 1 と 0 で判定したままです。`{"light":361}` という値で判定できるよう設定を追加します。

![image](https://i.gyazo.com/a23fbe5bd2da227fb843dd17c15827da.png)

JSON データで mqtt in ノードが受け取れるよう、プロパティの出力の項目を `JSONオブジェクト` に変更します。

![image](https://i.gyazo.com/8446b03326f477ba0453aa2923613c55.png)

switch ノードをこのように変更します。450 の部分は、センサー値で「明るい」「暗い」が馬上手く判定できる値を設定しましょう。

- プロパティ
  - msg.payload.light
- 振り分けルール
  - 1 番目
    - データタイプ
      - 数値
    - 評価
      - `<`
    - 値
      - 450
  - 2 番目
    - データタイプ
      - 数値
    - 評価
      - その他

![image](https://i.gyazo.com/943b4630e0163a28b3c7973b4d060418.png)

設定ができたらデプロイします。

## 13-5 LINE Notify 確認

Node-RED から LINE Notify へのメッセージ送信含め、フロー全体の動作を確認します。

![image](https://i.gyazo.com/219c1d17523fa694dbbe75e98d0fe429.jpg)

手をかぶせて暗くして変化をみてみましょう。

![image](https://i.gyazo.com/aa8117d634b36267f670da6d3e4c98c9.png)

実際にメッセージが変化するか確かめてみましょう。

## 13-6 フロー実践

Node-RED で様々なユーザーインターフェースやグラフ表示ができるノード群、ダッシュボードノードの体験していきましょう。

![image](https://i.gyazo.com/0245d94fb6c895872799bc0da4e89237.png)

https://flows.nodered.org/node/node-red-dashboard

詳しくは、メインテキストの 5.2 Node-RED ダッシュボードノードにも書かれています。

Node-RED ダッシュボード機能は標準では使えないので、node-red-contrib-line-messaging-api ノードと同じようにノードをインストールします。

右上のメニューからパレットの管理を選択し、ノードを追加タブをクリックします。

![image](https://i.gyazo.com/d9cd7057710d5ad758e5ae171852b8c6.png)

検索エリアで node-red-dashboard と検索します。同名の node-red-dashboard をインストールします。

![image](https://i.gyazo.com/6bb975afc7cc08c3cbdd58fb213fe9d4.png)

パレットにダッシュボードノード群がインストールされます。

### 13-6-1 ダッシュボードノードの設定

ダッシュボードノードをインストール後にダッシュボードそのものの設定は、ノード情報ウィンドウのダッシュボード設定から行えます。

![image](https://i.gyazo.com/ea05c3b8aeabf484b9623429796e3aac.png)

ノード情報ウィンドウの右上のボタンからこのように Dashboard をクリックします。（インストール後に登場します）

![image](https://i.gyazo.com/4e268a41b6ff191e9bb0dde897b306f3.png)

今回は表示上の最低限の配置を決めるので、まずタブを一つ設定するためタブボタンを1度クリックします。

![image](https://i.gyazo.com/5fbf8f675d84c7c978ee7cd276f20f2c.png)

クリックするとこのように Tab1 が追加されます。

![image](https://i.gyazo.com/4de8ee071822619a3de4d69ca3336144.png)

Tab1 にマウスを乗せると、グループなどボタンが出てくるのでグループをクリックします。

![image](https://i.gyazo.com/ca64703ce05d03cc7a5bac3f4d5c877b.png)

これで最低限の設定は完了です。

### 13-6-2 グラフを配置してみる

![image](https://i.gyazo.com/1c7152a1c4122202c84f09e62536001a.png)

折れ線グラフが作れる chart ノードを試してみます。IoT ではセンサー値をまずは見てみて、ブラッシュアップしていくことは多いので、こういった可視化の手法は役に立ちます。

![image](https://i.gyazo.com/67eaa2346c78473d9e2477db9af7d55e.png)

chart ノードはこちらです。

![image](https://i.gyazo.com/aa5a3edaefd7f7ab88760dfc43167ffc.png)

このあたりに change ノードと chart ノードを配置してつなぎます。

![image](https://i.gyazo.com/f5f64323531c63333286e56c768dca81.png)

change ノードは chart ノードに msg.payload で値を届けるために光センサーの値が入っている msg.payload.light からデータを移動します。

![image](https://i.gyazo.com/e06c7a33c0ec110e5e727c9b0c874c96.png)

chart ノードのプロパティは、今回はグループが `[Tab1] Group1` になっているかを確認します。

![image](https://i.gyazo.com/943b4630e0163a28b3c7973b4d060418.png)

設定ができたらデプロイします。

![image](https://i.gyazo.com/b83c3f661924d04ab784911ea698412c.png)

設定できるとこのようなフローの見た目になっているはずです。

### 13-6-3 ダッシュボードの確認

ダッシュボードは、インストールした瞬間から Node-RED の URL に `/ui` をつけた形で確認できます。Node-RED が `http://localhost:1880/` で起動されている場合は `http://localhost:1880/ui` です。

![image](https://i.gyazo.com/3bd11ea311de237d06ed7e1e9468b552.png)

そのかに、さきほど設定したノード情報ウィンドウの右上のボタンから Dashboard を表示した、このアイコンからも `http://localhost:1880/ui` にアクセスできるので、今回はこれでやってみましょう。

![image](https://i.gyazo.com/447840e5bb78e56b317d17076df4d198.png)

このように、センサー値がリアルタイムに折れ線グラフで表示されます。

### 13-6-4 ボタンを配置してみる

グラフのようなデータの可視化だけでなく、ユーザーインターフェースもつくれます。IoT のプロトタイピングでは、このようにユーザ操作をうまく受け入れる仕組みは重宝します。

![image](https://i.gyazo.com/77fb193859b14169a50d67120abae655.png)

button ノードはこちらです。今回は、ボタンを押すと「ボタンが押されました！」と LINE Notify にメッセージ送る仕組みを加えます。

![image](https://i.gyazo.com/4c5f492ecc4ec8b5c705662bb659c9d7.png)

このあたりに button ノードを配置して、Notify ノードにつなぎます。

![image](https://i.gyazo.com/b1f59f59d20362de64b6143ba12f23dd.png)

button ノードのプロパティは、まずグループが `[Tab1] Group1` になっているかを確認します。

![image](https://i.gyazo.com/f28b78b80853415bc10f7dad43aad535.png)

つづいて、ボタンを押したときの送るメッセージを決める `When clicked, send:` 項目の Payload を「ボタンが押されました！」の文字列にします。

![image](https://i.gyazo.com/943b4630e0163a28b3c7973b4d060418.png)

設定ができたらデプロイします。

![image](https://i.gyazo.com/9b45f4d681483d6c116433a6b3fa707e.png)

`http://localhost:1880/ui` にアクセスするとボタンができているので、何度かクリックしてみましょう。

![image](https://i.gyazo.com/a304b5dd9aadc3b8a1de0251fc1111cc.png)

このように、センサー値のメッセージの間に「ボタンが押されました！」の通知が来ます。