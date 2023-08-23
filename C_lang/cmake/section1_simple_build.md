# cmakeの使い方

前回は簡単な用語と使い方を説明した

今回は単純な場合の使い方についてマスターしよう

## ファイルが一つの場合のコンパイル

`main.cpp`
```cpp
#include <iostream>

int main(){
    std::cout << "hello world" << std::endl;
}
```

これをコンパイルしよう

普通にビルドするならば

```sh
> g++ main.cpp -o main 
```

こうだろうか

ファイル構成は以下のようになる

```markdown
|- main.cpp
|- main
```

ではcmakeを使おう

`CMakeLists.txt`に

```cmake
cmake_minimum_required(VERSION 3.16.2)

project(test_cmake CXX)

add_executable(main main.cpp)
```

と書き、

```sh
> cmake -S . -B build
> cd build
> make
```

と実行する

そうするとファイル構成は次のようになるだろう

```markdown
|- CMakeLists.txt
|- main.cpp
|- build
	|- main
	|- その他たくさん
```

これでコンパイルはできただろうか

### 解説

#### cmake

```cmake
cmake_minimum_required(VERSION 3.16.2)
```

これはcmake のバージョンを指定するもので必ず必要になるものだ  
cmakeはアップデートを繰り返して機能を増やしているのでどのバージョンの機能を使っているかを示すのに必要なのだ。常に最新のバージョンにしておこう

```cmake
project(test_cmake CXX)
```

これはプロジェクトの名前を付けている  
もともとcmakeはいくつものファイルをそれぞれコンパイルするという使い方というよりは大きなプロジェクトのコンパイルを統括するものなのでプロジェクトは一つしか名前を付けられない  
今回のプロジェクト名は`test|cmake`だ

では後ろの`CXX`とはなんだろうか  
これはC++を使うということをCmakeに教えているのである

書かなくても`C`と`CXX`が指定されるので問題ないが書いた方が実行速度が速いのでできるだけ書いた方が良い  
ちなみにCをコンパイルするときは`C`と指定する  
他にもjavaやkotlinもビルドの対象にできるらしい

```cmake
add_executable(main main.cpp)
```

実行ファイルの生成だ  
第一引数で出力するファイル名を指定し、第二引数以降でビルドに必要なファイルを指定する  
特に難しいことはないだろう

#### コマンドライン

一応コマンドラインでの対応について触れておこう

```sh
> cmake -S . -B build
```

これはcmakeの実行だ
`-S`はソースツリーの指定、`-B`はビルドツリーの指定なので特に指定のない人(この指定で問題ない)は正直下のコマンドでもよい

```sh
> cmake .
```

ビルドツリーの位置やソースツリーの位置を指定したいときは変更ここをすれば好きな位置を指定できるので覚えておくとよい

```sh
> cd build
> make
```

`cd build`については特に解説する必要はないだろう  
わからないならばもう少しコマンドラインと遊ぶことをおすすめする

`make`をする理由はcmakeはビルドをするためのmakefile生成器なのでcmakeを実行しても実行ファイルは生成されていないからだ  
`make`を実行することで初めて実行ファイルが生成されるのだ

正直このレベルならばcmakeで受けられる恩恵はないに等しい  
複雑になってからがこのcmakeの真価が発揮されるところなのでまだ耐えてほしい


## 複数ファイルのコンパイル

前回の説明でやったことだが、一応おさらいしよう

ファイル構成

```markdown
|- CMakeLists.txt
|- main.cpp
|- hello.cpp
|- hello.hpp
```

`hello.hpp`
```cpp
#include <iostream>
void hello();
```

`hello.cpp`
```cpp
#include "hello.hpp"
void hello(){
	std::cout << "hello world" << std::endl;
}
```

`main.cpp`
```cpp
#include "hello.hpp"
int main(){
	hello();
	return 0;
}
```

`CMakeLists.txt`
```cmake
cmake_minimum_required(VERSION 3.16.2)

project(test_cmake CXX)

add_executable(main main.cpp hello.cpp)
```

詳しい説明は前に書いた通りだ

変更点は三行目の`add_executable(main main.cpp hello.cpp)`くらいだろうか

正直`hello.cpp`というファイルを追加しただけなので解説することはないとは思う  
少なくとも同じファイル内であればこのように追加していけばいくらでもファイルのリンクはできる

## サブディレクトリのファイルをコンパイルする

```markdown
|- main.cpp
|- hello
    |- hello.cpp
    |- hello.hpp
```

このようにファイルが分割されたプログラムをコンパイルする

### 単一の`CMakeLists.txt`でコンパイルする

このようにファイルを配置する

```markdown
|- CMakeLists.txt
|- main.cpp
|- hello
    |- hello.cpp
    |- hello.hpp
```

`CMakeLists.txt`
```cmake
cmake_minimum_required(VERSION 3.16.2)

project(test_cmake CXX)

add_executable(main main.cpp hello/hello.cpp)
```

複数ファイルのコンパイルの項で書いた`CMakeLists.txt`にディレクトリをまたいだファイルの指定をするだけだ

### 複数の`CMakeLists.txt`でコンパイルする

```markdown
|- CMakeLists.txt
|- main.cpp
|- hello
    |- CMakeLists.txt
    |- hello.cpp
    |- hello.hpp
```

`CMakeLists.txt`
```cmake
cmake_minimum_required(VERSION 3.16.2)

project(test_cmake CXX)

add_subdirectory(hello)

add_executable(main main.cpp)

target_link_libraries(main Hello)
```

`CMakeLists.txt`
```cmake
cmake_minimum_required(VERSION 3.16.2)

add_library(Hello STATIC hello.cpp)
```

#### 解説

- `add_library`  
  これは`C_lang/C_lang/column3_library.md`で説明しているのが詳しいが、ライブラリを作成している  
  `STATIC`と指定しているが、これは静的ライブラリを作るように指示している  
  `SHARED`で共有ライブラリを作成することができる

- `target_link_libraries`  
  上で作ったライブラリのリンクを指示している
  共有ライブラリも同様にしてリンクできる

- `add_subdirectory`  
  そのサブディレクトリをcmakeの管理下に置く  
  そのディレクトリにCMakeLists.txtがなければエラーとなる


2022/10/26  
written by 西永
