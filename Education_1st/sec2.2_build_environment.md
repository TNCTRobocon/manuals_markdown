# 実際に環境構築をしてみよう
## Visual Studio Codeの導入
Visual Studio Codeは、拡張機能を導入することでほぼすべての言語を、多くのOS上で動作させることができる強力なコードエディタです。  
みなさんも使用しているTeamsやPowerPointなどの開発元であるMicrosoftの製品です。  
以下の通りに導入していきましょう。上手くいかない場合はそこら辺の人に聞いてみてください。  
1. [ここのページ](https://code.visualstudio.com/)からインストーラをダウンロードします。  
2. インストーラの指示にしたがってインストールを実行してください。  
導入は以上です。(簡単だね)  
## 日本語化
このままでは使いにくすぎるので、日本語化していきましょう。  
1. [ここのページ](https://marketplace.visualstudio.com/items?itemName=MS-CEINTL.vscode-language-pack-ja)から、Japanese Language Packをインストールし、再起動します。  

## 拡張機能を導入する  
VScodeは、インストールしたてほやほやの状態だとただのメモ帳と変わりありません。  
必要に応じて、使用する言語の拡張機能を導入しましょう。  
手順は以下の通りです。
1. VSCodeを開き、左のバーから「拡張機能」を選択
2. 上の「Marketplaceで拡張機能を検索」から言語名を入力し、  
   必要な拡張機能の「インストール」ボタンをクリックする

## GCCコンパイラの導入
C言語のコンパイラには、様々な種類がありますが、今回はGCCコンパイラというものを使用しましょう。  
GCCは、OSによってダウンロード方法が異なります。  
- Windowsの場合(若干ややこしいのでQiitaの解説を貼ります)
  1. ダウンロードサイトは[ここ](https://osdn.net/projects/mingw/downloads/68260/mingw-get-setup.exe/)
  2. Qiitaの解説ページは[ここ](https://qiita.com/ryo-sato/items/00c17469978e47d91a09)  
   手順が多すぎて書くのがめんどかったんです(ﾕﾙｼﾃ...)
-  Linuxの場合  
   ~~最初から入ってます。~~  
   普通は入ってないらしいので、aptコマンドを用いてインストールします。  

   まず、下のコマンドでaptをアップデートします。
   ```sh
   sudo apt update
   sudo apt upgrade
   ```

   次のコマンドでインストールします。  
   **build-essential**は、GCCに加えてC++の実行に必要なG++もろもろを導入してくれます。
   ```sh
   suso apt build-essential cmake
   ```

   依存関係のエラーが出た場合は、ダウングレードが有効らしいです。　　


最後に、GCCがきちんと使用できるかのテストを行います。コマンドプロンプトを開き、  
```sh
gcc -v
```
と入力します。
```sh
Thread model: win32
gcc version 6.3.0 (MinGW.org GCC-6.3.0-1)
```
など、バージョンが表示されたら大成功です。  
上手く動作しない場合は、先輩と一緒に確認しましょう。  
これでC言語の開発環境が整いました。

2023/04/17 written by Kohki S.  
ひとこと 長すぎワロタ

2023/05/15 : Windows,LinuxにおけるGCC導入について修正  
なんで俺のUbuntuに最初からGCCがいたんだろう...
