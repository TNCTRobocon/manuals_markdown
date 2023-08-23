# ライブラリ

## 静的ライブラリと共有ライブラリ

二種類のライブラリが存在する

[ファイル分割](https://github.com/TNCTRobocon/manuals_markdown/blob/naga/c_plusplus/C_lang/C_lang/column1_filesplit.md)の項で紹介しているようにライブラリは別でコンパイルしておいて統合するときにリンクするだけにしておくべきだという風に説明した

しかし、そのままだとオブジェクトファイルがたくさんあって大変なことになってしまう

ここでそれらのオブジェクトファイルをまとめる役割を担うのがライブラリだ

ここで静的ライブラリと動的ライブラリの二つを紹介する

### 静的ライブラリ

開発時にコンパイルしておくもの

開発時に何らかの形で実行ファイルを作るときににリンカによってライブラリを実行ファイルの一部として埋め込むタイプのやつ

>リンカとは
>>機械語のプログラムを適切に連結して実行ファイルを生成するためのプログラム  
ファイル分割をしたときに結構お世話になるので調べたことがなかったら調べた方が仲良くなれるかもね

使い方は基本的にオブジェクトファイルと変わらないと思ってくれていい

コンパイル方法

`hello_en.hpp`
```cpp
#include <iostream>

void hello_en();
```

`hello_en.cpp`
```cpp
#include "hello_en.hpp"

void hello_en(){
    std::cout << "hello" << std::endl;
}
```

`hello_jp.hpp`
```cpp
#include <iostream>

void hello_jp();
```

`hello_jp.cpp`
```cpp
#include "hello_jp.hpp"

void hello_jp(){
    std::cout << "こんにちは" << std::endl;
}
```

ソースコードは以上

次に静的ライブラリの作り方

```sh
$ g++ -c hello_en.cpp hello_jp.cpp -O2 -std=c++2a -Wall
$ ar rvs libhello.a hello_en.o hello_jp.o
```

一応解説

一行目でコンパイルしてオブジェクトファイルを作っている  
各種引数がわからない時はいかのURLを参照

[ビルドオプション](https://github.com/TNCTRobocon/manuals_markdown/blob/naga/c_plusplus/C_lang/C_lang/column2_build_optioin.md)

二行目でオブジェクトファイルをまとめて静的ライブラリを作成している

arコマンドについてはこれが詳しい  
https://linuxcommand.net/ar/

一応見なくてもいいように説明しておくと  
`ar`はそういうコマンド。アーカイブファイルを作れるらしい

>アーカイブファイルとはデータを長期間保存するために専用のファイル形式にしたりとかしたもの。複数のファイルをまとめたりするものに対して言う

`rvs`はそれぞれ`r`はメンバの追加、`v`は操作内容を表示、`s`はシンボルテーブルを作成または更新である

>シンボルテーブルとは
>>データ構造の一種で変数の名前と中身の情報のテーブル(表)である

それと静的ライブラリを作るときは頭に`lib`と付けて、拡張子は`.a`にするのが一般的である
今回だと`libhello.a`となる

>windows, macだと異なるようであるので注意  
windowsとかmac使ってる人でわかる人だったら追記してください

### 静的ライブラリを用いたコンパイル

```sh
$ g++ main.cpp -L. -lhello -O2 -std=c++2a -Wall
```

```sh
$ g++ main.cpp libhello.a -O2 -std=c++2a -Wall
```

このどちらかでライブラリを用いてコンパイルできる

上はライブラリの位置を`-L`でライブラリを探すディレクトリを指定して`-l`でライブラリを指定している

この時に指定するライブラリの名前は対象のライブラリ名から頭の`lib`を外して拡張子も外したものにする

今回の場合だと対象のライブラリが`libhello.a`なのでコマンドは`-lhello`となる

また、下の方は普通にコンパイルするファイルとして指定するものである

上の方がコマンドとして一般的である

### 共有ライブラリ

実行時にリンクするもの
