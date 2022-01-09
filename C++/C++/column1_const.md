# constを使って安心安全なコードを書こう

## constとconstexpr

C++ではconstexprというものがある

constとは何が違うのか

### const

型修飾子  
初期化した後二度と変更されない変数に対して使う修飾子

### constexpr

コンパイル時に決まっている値にしか用いることができない  
定数として扱う

`const`では定数を使うときにメモリにアクセスするが、`constexpr`はコンパイル時にソースコードに埋め込まれる

```c++
const int const_i;
const_i = 0;//ok
constexpr int c_expr1;///error

constexpr int c_expr2 = 10;//ok
constexpr int c_expr3 = 3*5;//ok
constexpr unsigned int bufsize = sizeof("roboconA");//bufsizeの値は8
```

`constexpr`は必ず宣言時に初期化しなければいけない  
また、定数と定数、または`constexpr`と`constexpr`の計算結果などといったコンパイル時に値が決定できるものであれば`constexpr`は使うことができる(あまり複雑なものはNG)

`constexpr`で書くと右辺は必ずコンパイル時に計算できるものになるため、結果的に計算を実行時からコンパイル時に移して実行できるので結果的に高速化できることになる

`constexpr`大好き

## これを使うと何がいいの？

デバッグを楽にできる

変更しない値はconstをつけたほうが親切である(だって変数の中身を追わなくていいからね)  
デバッグ性が良いコードを書くことができるので積極的にconstやconstexprを使ってほしい

## defineはやめようね

`#define`でも定数を作れるじゃないかと思ったそこの君！

やめてください

まず`#define`はプリプロセッサである  
ここは大丈夫だろう  

`#define`には型がない
型の情報がないと何がエラーかわかりにくくなる、気を付けるものが増えるということがある  
少しでも安全性の高いコードを書きたいなら`constexpr`をお勧めする

次に、スコープの概念がないことが上げられる  
スコープの概念はどこまで作用しているのかを制限できるものだが、それも失われてしまう  
置換が行われる範囲が極端に広くなる、すると……  
怖いねー  
**絶対にやめてください**

### ちなみに

```C++
#define START int main(){
#define OUT(x) std::cout<<x<<std::endl;
#define END }

START
OUT("define!")
END
```

```markdown
define!
```

こんなえげつないこともできちゃうのでやめてください  

そもそもプリプロセッサはコンパイル条件を設定する以外のことにできる限り使わないようにするのがベスト

どうしても使いたいときは

```C++
#define OUT(x) std::cout <<x<<std::endl;
OUT("define!")

#undef OUT
```

という風に範囲を限定して書く

## constexpr関数

```C++
constexpr int twice(const int n){
    return n * 2;
}

void test_c(){
    constexpr int ten = 10;//ok
    constexpr int twenty2 = twice(ten);//ok

    int i = 10;
    constexpr int tenx = twice(i);//error
}
```

特徴として内部では変数の書き換えをできず、戻り値の型をvoidにすることができない点である  
~~そのためifの代わりに条件演算子を使う~~C++14からは緩和されてif文は使えるようになっている  
~~ループでは再帰を使う必要がある(再帰に関しては調べてみてください。関数型言語とかでよく見る)~~  
これもC++14から緩和されて使えるようになった

goto文は許されていない

その代わり、安全性が高く、速度が早いという特徴がある  
コンパイル時にも実行時にも数式評価が可能になった

>即時関数について
>>絶対にコンパイル前に関数を評価してほしいならば、C++20で追加された`consteval`指定子を付けた関数を用いることで実現できる  

## ポインタとconst

### ポインタではない場合

```C++
const int i = 1;
i = 123;  // エラー：再代入不可
```

特筆すべき点はない  
`const int`と書いても`int const`と書いても意味は同じということくらいは述べておく

### ポインタ

`const`の位置で何が上書き禁止になるか決まる

```C++
const char* s11 = "foo";
//*s11 = 'x';  // エラー：ポインタの指す先の書き換え不可
s11 = "bar";   // 成功：変数の再代入は可能

char const* s12 = "foo";  // 内容的には変数s11と内容は同じ
//*s12 = 'x';  // エラー：ポインタの指す先の書き換え不可
s12 = "bar";   // 成功：変数の再代入は可能

char* const s2 = "foo";
*s2 = 'x';     // 成功：ポインタの指す先の書き換え可能
//s2 = "bar";  // エラー：変数の再代入不可

const char* const s3 = "foo";
//*s3 = 'x';   // エラー：ポインタの指す先の書き換え不可
//s3 = "bar";  // エラー：変数の再代入不可
```

|型|中身の書き換え|ポインタの書き換え|
|-|-|-|
|`const char*`|可能|不可能|
|`char const*`|可能|不可能|
|`char* const`|不可能|可能|
|`const char* const`|不可能|不可能|

このような違いがある  
この辺りは覚えてしまっていいだろう

`const`を付ける位置の参考にしてほしい

## constメソッド

クラスのメンバ関数について、これもconstを付けることができる

```C++
class sample_class{
    int const_method()const{
        //処理
    }
};
```

こうすることでconstを付けた関数の内部でオブジェクトの変数の変更が不可能になる  
これもデバッグ性を向上させるものなので積極的に使ってほしい

注意点がいくつかある  

クラスのメソッドを呼ぶとエラーになる  
そのメソッドが同じように`const`メソッドなら呼び出せるのだが、普通のメソッドであれば呼び出すことは不可能である

ただし、`mutable`を使えば書き換え可能なのメンバ変数でも書き換えることが可能になっている  
便利だと思うかもしれないが、もともとのconstメソッドの意味を薄れさせることにつながるので乱用は控えよう

また、返り値に`const`定義のされていない参照変数をメンバとして返すとエラーになる  
まぁ`const`定義して返り値に指定するとエラーは出ない

2021/12/21  
written by 西永