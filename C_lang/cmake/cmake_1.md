# cmakeを使おう

cmakeって知ってる？

C系の言語のビルドに利用されているビルドマネジメントツール  
makefileをより簡単に記述できるビルドマネージャ

CMake君は書かれたテキストからmakefileを生成して実行するものである  
簡単に複雑なmakefileを書けるよ、やったね！

## cmakeの用語を簡単に

### プロジェクト

ひとまとまりのソースコードにつけられる名前  
通常一つだけ設定される

### ターゲット

ビルドにもいろんなことを行う(実行ファイルの作成やライブラリの作成など)  
これらのタスクをそれぞれ指定したものがターゲット

大きく3種類があり、

1. 実行ファイルの生成(add_executable)
2. ライブラリファイルの作成(add_library)
3. カスタムターゲットの実行(add_custom_target)

があり、そのほかにもターゲット間に依存性を定義できたりする

### プロパティと変数

変数  
詳しくは後で解説する

プロパティとはターゲットやディレクトリの属性を表したもの  
これも後々解説する

## out-of-sourceという考え方

cmakeではビルドツリーとソースツリーを分けるout-of-souceビルドが利用できる

具体的に言うと、  
ビルドの成果物(\*.exeや\*.oなどのファイル)がbuildフォルダに入って便利  
これによってツリーが汚れずに済むし、gitの管理も楽になる  
加えてキャッシュや成果物を消したい時にBuildフォルダを消せばいいので便利  

## ビルドしてみる

```markdown
|-main.cpp
|-hello.hpp
|-hello.cpp
```

```c++
//main.cpp
#include"hello.hpp"

int main(){
    hello();
    return 0;
}
```

```C++
//hello.hpp
#pragma once

void hello();
```

```C++
//hello.cpp
#include<iostream>

void hello(){
    std::cout "hello" << std::endl;
}
```

### 通常のビルド

```sh
> g++ -c main.cpp hello.cpp
> g++ -o main.exe main.o hello.o
```

こうすると当然ディレクトリは

```markdown
 |-a.out
 |-main.cpp
 |-main.o
 |-hello.hpp
 |-hello.cpp
 |-hello.o
```

となる

これでgitを使おうとすると大変だろうなということが伝わるだろうか

そうじゃなくてもどれがソースファイルなのかがひとめでわかりにくくなってしまっている

### cmakeを使ったビルド

簡単なcmakeの例を見せる

CMakeLists.txtを作り、その中に

```CMake
cmake_minimum_required(VERSION 3.0.2)

project(test_cmake CXX)

add_executable(main.exe main.cpp hello.cpp)
```

こう記述してみる

そして、cmakeをビルドするときは必ずbuildディレクトリを作成しその中でビルドする

```sh
> mkdir build

> cd build

>cmake
```

---/  
 |-CMakeLists.txt  
 |-main.cpp  
 |-hello.hpp  
 |-hello.cpp  
 |-build  
    |-main.exe  
    |...（その他色々）

こうするとソースファイルがまとまってきれいになっているじゃないか

コマンドもcmakeって打つだけだしかなり楽になっただろう

これを元の状態に戻すならbuildディレクトリを消せばそれでokである

## 
