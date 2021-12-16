# 型推論

C++の便利な機能だ
本当によく使う機能

## auto型

型名を自動で判別してくれるすごい子  
int や double ではあまり効果は実感できないが前セクションであったイテレータや、いずれ説明するラムダ式など長い型名の記述になるときはかなり便利

```c++
std::vector<int> vec = {0, 1, 2, 3, 4};

for (std::vector<int>::iterator itr = vec.begin(); itr != vec.end(); ++itr){
    std::cout << *itr << std::endl;
}

//↓auto使用
for (auto itr = vec.begin(); itr != vec.end(); ++itr){
    std::cout << *itr << std::endl;
}
```

また、

```C++
int function(auto&ref, const auto arg, const auto& cref){
    //コード
}
```

のように`auto`型で参照、定数、const参照もできる  
何ならよく使う

しかし、`auto`も万能ではない  
以下のような場合は使えない

| 対象 | 対応 |
|-|-|
|ローカル変数|〇|
|グローバル変数|×|
|メンバ変数|×|
|静的メンバ変数|constのみ可|
|関数の戻り値|仮想関数以外なら可(C++14)|
|関数の引数|ラムダ式のみ可(C++14)|

## template

型を自動で判別してくれる子2  
正しくはコンパイル時に型や値を引数として渡す機能  
~~諸悪の根源とかいろいろ言われてる~~特殊化とかはここでは触れないのでここでは大丈夫

### 関数テンプレート

section2で触れた関数について、オーバーロードという機能があった  
だが、関数名が同じでも同じ処理を行って、変数を変えてとなると大変だしバグの元になるのでテンプレートを使おう

```C++
template <typename T>
T max( T a, T b )
{
    return a < b ? b : a ;
}

int main(){
    int num1 = 0, num2 = 10;

    cout << max<int>(num1, num2);
}
```

`template<typename 〇>`でテンプレートの宣言  
`typename T`のTは慣習的につけられてる名前なので適当につけても構わない

また、`template<class 〇>`としてもおk  
特に違いはない

呼び出した時に  
`max<int>(num1, num2)`  
とかく`<int>`とするのはコンパイル時に確定する型名のことである  
これでコンパイルすると関数内で`T`はint型として扱われる  
int型として扱われるので当然引数や戻り値、変数の宣言にも使える素晴らしい子だ

ちなみに、  
`T`をテンプレートパラメータ  
呼び出す側で指定するデータ型(`<int>`みたいなやつ)をテンプレート引数という

また、テンプレート引数は実引数からデータ型が推測できる場合は省略ができる

使用したデータ型が複数ある時はテンプレートパラメータをコンマで区切って別で定義できる

```C++
//関数テンプレート
template<typename T1, typename T2>
void func(T1 x, T2 y){
    //何か処理
}

int main(){
    //関数呼び出し側
    func<int, double>(1, 2.0);
}
```

### クラステンプレート

まだクラスについて説明していないので詳しいことは説明できないのでこういうもあるという説明にとどめる

```C++
template <typename T>
class pos_2d{
    T x = T{} ;
    T y = T{} ;
} ;
```

これは関数テンプレートと同じように型を変数のように扱って使うときに指定するものだと思ってくれればいい

### 変数テンプレート

~~正直私には何に使うのかよくわからないが~~説明だけする

```C++
template < typename T >
constexpr T PI = static_cast<T>(3.14159265358979323846L) ;

int main(){
    std::cout << PI<int> << std::endl;; // 3
    std::cout << PI<double> << std::endl; // 3.14159
}
```

こうすれば要求した型の大きさに合わせて自分で動かしてくれるらしい

### concept

C++20以降で使えるテンプレートを制限できる機能  
こうすることでエラーメッセージなどが読みやすくなる

```c++
template<typename T>
concept number = std::is_integral_v<T>//整数型であることを表すコンセプト
```

こうすることによって整数型のみにテンプレートを制限してしまい、エラーコードを読みやすくするなどの効果がある

整数型以外にも

- `regular`
  基本型とかそのあたり
  詳しく言うと
  + ムーブ構築・代入可能  
  + コピー構築・代入可能  
  + デフォルト構築可能  
  + swap可能  
  + == !=による等値比較可能  
であることを言う
- `floating_point`
  浮動小数点型であることを示す

次はclassについての記述を含むのでわからなければ読み飛ばしてもらっても構わない

```C++
template<class T>
concept Drowable = requires(T&x){
    x.drow();//drow関数を持つことを必要とする
    //他にも条件が必要なときはセミコロン区切りで列挙
}

template<Drowable T>
void func(T&x){
    x.drow();
}

struct Circle{
    void drow(){}
}

struct Box{
    void drow(){}
}

int main(){
    Circle c;
    func(c);

    Box b;
    func(b);

    int i;
    func(i);//error
    //conceptでdrowメンバ関数を持っていないためDrowableコンセプトの要件を満たしていないためエラー
}
```

このようにクラスに対してもコンセプトを使うことができる

### typenameとusing

`typename`の使い方について学んでいこう

テンプレートパラメータでの使用は学んだと思うが、それ以外での使い方についても見ていく

#### そもそもusingについて

`using`には`typedef`のようなエイリアスを作る機能がある

>エイリアス宣言という

```C++
using Integer = int;//Integerはint型としても扱える
```

他にも関数ポインタなどとも相性が良い  
詳しくは自分で調べてほしい

ここでテンプレートによる型の別名付けについて

```c++
template<typename T>
using Vec = std::vector<T>;

Vec<int> v;
v.push_back(3);
```

このようにするとテンプレートを使った型にもエイリアスを作ることができる  
これは`typedef`にはない機能で、usingのみの機能となる

```c++
template<typename T>
void func(){
    std::vector<>
}

## decltype

`decltype`は、オペランドで指定した式の型を取得する機能
型を指定する必要のある個所で`decltype`を使用することによって、具体的な型名を指定する代わりに式から取得した型を指定できる

```C++
int i = 0;
decltype(i) j = 0;//int
decltype(i)* k = &i;//int*
decltype((i)) l = i;//int&

decltype(function()) r;//関数の返り値の型
```

`auto`の使えないところに使えるので便利

よく使うものとしては

```C++
template <typename
T1, typename T2>
auto add(const T1& x,const T2& y)->decltype(x+y){
    return x+y;
}
```

のように関数の戻り値の指定に使えたりする

## その他

まだまだテンプレートにはいろいろと奥深い機能があるので調べてみるといい  
あまりの複雑さにﾁｮｯﾄﾅﾆｲｯﾃﾙｶﾜｶﾗﾅｲみたいな状況になることが多々あるから頑張ってね……

writen by 西永
2021/12/13
