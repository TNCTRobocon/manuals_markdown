# Gitの準備
## Gitのインストール
Gitは、多くの場合は標準で搭載されていないので、適切な方法を用いてインストールします  
- windowsの場合  
[Gitの公式サイト](https://gitforwindows.org/)から、インストーラをダウンロードし、セットアップを実行します。  
インストールの詳細設定は以下のとおりにしてください。  
    - インストール先:お好みでどうぞ
    - オプションの選択:そのままでよい
    - スタートメニュー登録先:そのままでよい
    - (コミットメッセージを入力する)テキストエディタの選択:まあ...Vimでいんじゃね?
    - 新規リポジトリ作成時のブランチ名:**Override the default branchname for new repositories**を選択し、**main**と入力してください(後ほど説明します)
    - パスの設定:Git from the commandline and also from 3rd-party software
    - OpenSSHのインストール:そのままで良い
    - HTTPS接続の設定:Use the openssl library
    - 改行コードの設定:Checkout as-is, commit as-isがおすすめらしい
    - ターミナルの設定:Use Windows' default console window
    - git pullの設定:デフォルトで良い
    - 資格情報マネージャの設定:Git Credential Manager
    - 追加オプション・試験運用オプション:そのままでよい
- ubuntuの場合  
次のコマンドでインストールします  
```sudo apt install git```

## 動作確認
ターミナル(コマンドプロンプト)を開き、次のコマンドを入力します。  
```git -v```

## GitHubのアカウント作成
有効なメールアドレスが必要です。持ってない場合はGoogleとかで適当に作ると良き。  
ちなみに、I科は授業内で指定された通りのアカウントを作らなきゃいけないので、学校のメールアドレスは使わないほうがいいでしょう。  

[いいサイト](https://qiita.com/ayatokura/items/9eabb7ae20752e6dc79d)があったのでこれを見ながらセットアップしてください。  


2023/06/24 Written by Kohki S.  
ひとこと: やる気が出ません