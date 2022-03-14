# 右辺値参照

右辺値や左辺値についての説明は`colomn3_rvalue.md`を参照

## 右辺値参照とはなんぞや

まずはsection3_referenceでやった参照を思い出してみよう  
あれは左辺値そのものにアクセスするんだった

今回はそれの右辺値バージョン

書き方としては

``` c++ 
T&& = rval;
```

`rval`は任意の右辺値である  
左辺値を代入しようとするとエラーになる

さて、通常の参照も含めて例を見ていこう

```c++
int i = 0;

int& lref_1 = 0;     //error
int& lref_2 = i;     //ok
int& lref_3 = lref_2;//ok
int j = lref_2       //ok

int&& rref_1 = 1;     //ok
int&& rref_2 = i;     //error
int&& rref_3 = lref_2;//error
int&& rref_4 = rref_1;//error
int k = rref_1;       //ok

int&& rref_move = std::move(lref);//次回解説
```

さて、ここまで見てきた人は大体の法則性がわかっただろう

### 結局なんなの？

問題はこれをどこに使うのだろうかというところだろう

もともとの右辺値の寿命について考えてみよう  
一時オブジェクトなので参照された後消えてなくなる

あくまでも右辺値参照はその値の延命措置であると考えよう  
式(expression) が評価された時点で寿命が尽きる値を関数の終わりまで延命するだけである  

それだけ聞くと使いみちないじゃんとなりがち

とりあえずこれを見てほしい

```c++
#include<iostream>

class rval{
    public:
    rval(){std::cout<<"constructor"<<std::endl;}
    ~rval(){std::cout<<"destructor"<<std::endl;}
};

rval func(){return {};}


int main(){
    rval();
    func();

    std::cout<<"===main end==="<<std::endl;
    return 0;
}
```

>`rval()`は右辺値としてのクラス  
インスタンスが生成されて代入されたら破棄される右辺値としての動きを持ったもの  
`rval`関数の返り値`return {}`は返り値の型を初期化したものを返す


```markdown
constructor
destructor
constructor
destructor
===main end===
```

`main` 関数の1行目2行目は`rval`クラスを呼んですぐに破棄するコードだ  

こうなるのはここまで読んできた人たちはすぐわかるだろう

では右辺値参照しよう

```c++
#include<iostream>

class rval{
    public:
    rval(){std::cout<<"constructor"<<std::endl;}
    ~rval(){std::cout<<"destructor"<<std::endl;}
};

rval func(){return {};}


int main(){
    rval&& rref_1 = rval();
    rval&& rref_2 = func();
    std::cout<<"===main end==="<<std::endl;
}
```

としてみると出力は

```markdown
constructor
constructor
===main end===
destructor
destructor
```

こうやって寿命を先延ばしにできる

ちなみに普通の参照を用いて右辺値を保持しようとすると

```c++
#include<iostream>

class ref{
    int a = 0;
public:
    ref() {std::cout<<"constructor"<<std::endl;}
    ~ref(){std::cout<<"destructor" <<std::endl;}
    int&get(){ return a;}
};

int&i = ref().get();
//この時点でrefクラスが破棄されているのでiは不定になる
std::cout<<i<<std::endl;//iは不定なので良くないコード
```

右辺値参照でなければ値は保持されない

## const参照

右辺値参照を使わずに右辺値を参照できる

文法的には
```c++
const T& a = b;
```

パッと見どうということはないただの参照だ

こいつはなんと右辺値も受け取れる

```c++
const int&cref1 = 0;//ok
const int&cref2 = x;//ok
const int&cref3 = i;//ok
```

右辺値参照と同じ機能として使わない方がいい

## ユニバーサル参照

左辺値も右辺値も束縛できる特別な参照  
`template`や`auto`を用いた右辺値参照と同じ書き方

```c++
template<class T>
int f(T&& uref_temp){}

auto&&uref1 = 0;
auto&&uref2 = x;
auto&&uref3 = lref;
auto&&uref4 = rref;
auto&&uref5 = cref;

f(1);
f(x);
f(lref);
```
### 完全転送(Perfect Forwarding)

右辺値や左辺値といった情報を含めたものも丸々型情報で区別ができるようになるようにユニバーサル参照に代入する  
`std::forward`を使う

```c++
#include<iostream>

void ref(int& a){std::cout<<"左辺値"<<std::endl;}
void ref(int&&b){std::cout<<"右辺値"<<std::endl;}

template<class T>
void h(T&&a){
    ref(a);
}

template<class T>
void forward(T&&a){
    ref(std::forward<T>(a));
}

int main(){
    int i = 0;
    int j = 0;
    auto&&uref = 1;
    auto&&uref1 = i;

    h(0);
    h(uref);
    h(uref1);
    h(std::move(i));

    std::cout<<"================"<<std::endl;

    forward(0);
    forward(uref);
    forward(uref1);
    forward(std::move(j));
}
```

結果は

```markdown
左辺値
左辺値
左辺値
左辺値
================
右辺値
左辺値
左辺値
右辺値
```

右辺値や左辺値といった情報が送られているのがわかるだろうか

これで右辺値や左辺値といった情報を保持したままプログラムが作れる

最後の`std::move(i);`については次回解説する

2022/03/15
written by 西永
