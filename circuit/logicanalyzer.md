# ロジックアナライザについて

パソコンに繋ぐと信号波形が見れるもの。デジタル信号特化型オシロスコープ。

# 必要なもの
- ロジックアナライザ

Amazonの安いやつを購入。取説その他は無いので注意。



[https://www.amazon.co.jp(販売ページ)](https://www.amazon.co.jp/KKHMF-8%E3%83%81%E3%83%A3%E3%83%B3%E3%83%8D%E3%83%AB-USB%E3%83%AD%E3%82%B8%E3%83%83%E3%82%AF%E3%82%A2%E3%83%8A%E3%83%A9%E3%82%A4%E3%82%B6-8CH%E3%83%AD%E3%82%B8%E3%83%83%E3%82%AF%E3%82%A2%E3%83%8A%E3%83%A9%E3%82%A4%E3%82%B6-ARM%E3%81%AB%E5%AF%BE%E5%BF%9C/dp/B078P8GQSQ/ref=cm_cr_arp_d_product_top?ie=UTF8)

![](.\images\logicanalyzer\image1.png)

- オスーメスジャンパケーブル

意外と忘れがち。ロジックアナライザのコネクタはMIL10なのでこれがないと面倒な事になる。
適当に部品店で揃えましょう。

[共立(販売ページ)](https://eleshop.jp/shop/g/gF18121/)

![](.\images\logicanalyzer\image2.png)


- USB-miniBケーブル

部室に生えてます。買うならAmazonベーシックブランドが良いとかbyT先輩

- 読み込みソフト

[配布サイト](https://sigrok.org/wiki/Downloads)から環境にあった`PulseView`というファイルをダウンロードしてインストールしておきましょう。インストールは適当にnextをぽちぽちすれば良いかと。

![](.\images\logicanalyzer\image3.png)


# ドライバのインストール

**注意：トラブル防止のためPCに繋がっているUSB機器をすべて外すこと**

1. アナライザをPCに接続
2. PCのスタートメニュー＞sigrok＞Zadig (PulseView)を開く
3. `Install Driver`をポチってドライバをインストール(ちょっと待つ)

![](.\images\logicanalyzer\image4.png)
