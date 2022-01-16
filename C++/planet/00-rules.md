# 概要

C,C++の標準ライブラリを一切使えない環境で最終的にインベーダーゲームを
作る実戦形式の骨太演習テキストです。

C及びC++の基本的な構文、分割ビルドを理解していることを前提とします。

# 環境

この演習では、次のいずれかの環境を推奨します

1. マイコンとその開発環境

  UART機能とタイマーが搭載されており、C及びC++のコンパイラを
  利用できること。

  例: STM32マイコン、LPCマイコン、PIC18F,PIC24F,PIC32マイコンなど
      (個人的には、STM32F4シリーズあたりがおすすめです)

  例外: PIC12F,PIC14F,PIC16Fシリーズは、スタックが有効利用できないため、
  本演習において動作しません。

2. Linux開発環境

  コンソールへの出力として、標準入出力関数であるgetchar,putcharと
  タイマーに関する関数以外の使用は控えてください。

  makeもしくはcmakeを用いたビルド方法を事前に習得するといいでしょう。

  Windowsを利用しているユーザーは、wslをインストールしてください。

3. Visual Studio環境
  
  おそらく動作するでしょうが、私はサポートしません。

# ルール

コンパイラが標準でサポートしているライブラリを使用してはいけない。

禁止されているヘッダーファイルと関数の一例

(C)
* <stdio.h> `fopen`,`fclose`,`fseek`,`fprintf`,`fscanf`,...(ファイル操作)
* <stdio.h> `printf`,`scanf`,`puts`,`gets`...(標準入出力)
* <stdlib.h> `malloc`,`free`,...(メモリー管理)
* <string.h> `strlen`,`strcmp`,`strcat`,`strcpy`,...(文字列操作)
* <string.h> `memcmp`,`memset`,`memcpy`,...(バイナリ操作)
* <ctype.h> `isdigit`,...(文字の種類)
* <math.h> `sin`,`cos`,`tan`,`log`,`exp`,... (各種数学関数)

(C++)
* `<vector>`,`<deque>`,`<string>`,`<map>`,`<set>`,`<memory>`
* `<algorithm>`
* `<iostream>`,`<fstream>`

例外として次のヘッダーファイルと関数の利用は認める。

(共通)
* `stddef.h`,`stdint.h`,`stdbool.h` 
* `<array>`,`<optional>`(c++17)

(Linux環境)
* `getchar`,`putchar`(入出力のため)
  + 難易度を上がる場合は、これらの関数も禁止する。システムコールを
    活用すべし。
* `mmap`(メモリー確保のため)
  + 難易度を上がる場合は、これらの関数も禁止する。システムコールを
    活用すべし。 
* `unistd.h`(システムコールのため)
* TODO: タイマーに関する関数の具体名を書く

C及びC++の構文は原則として認められる

次の構文を認めない。

(C++)
* `new`,`new []`
* `delete`,`delete []`
* `try ... catch`構文
(C99)
* スタックにおける可変長配列

