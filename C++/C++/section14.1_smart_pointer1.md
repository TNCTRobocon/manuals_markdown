# スマートポインタ

```c++
class my_class{
    //　色々
};

void func(){
    my_class*mc = new my_class();
    return ;//mcの確保したメモリが開放されない
}
```

`section8`でやったように`new`で確保したメモリは開放されない  
`new`してメモリを確保したものを`delete`で開放するのはプログラマの責任である  
開放を忘れたメモリはメモリリークとしてプログラムの実行中は残り続けるのでメモリに残り続けるのでメモリの無駄遣いですね

開放し忘れによるメモリリークをできるだけ防ぐ新しい手段としてスマートポインタがある

ちなみにスマートポインタについても何種類かあって

- auto_ptr
- unique_ptr
- shared_ptr

の参種類がある

## auto_ptr

※C++11からは非推奨

```c++
#include<memory>
#include<iostream>

class my_class{
public:
    int num;
    my_class(int _num):num(_num){
        std::cout<<"constructor"<<num<<std::endl;
    }

    ~my_class(){
        std::cout<<"destructor"<<num<<std::endl;
    }
};

void func(){
    my_class*mc = new my_class(1);
    std::auto_ptr<my_class> mc2(new my_class(2));

    mc2->num;//普通のポインタと同じようにアクセスできる
}

int main(){
    func();
    return 0;
}
```

出力

```markdown
constructor1
constructor2
destructor2
```

`new`で作られたインスタンスは関数の終わりでもデストラクタが呼ばれないのに対して`auto_ptr`で作られたインスタンスは関数の終わりで開放されている

これは`auto_ptr`が実際にはクラスのインスタンスであり、関数が終わるときに自動的に`auto_ptr`のデストラクタを呼ぶため、デストラクタで管理しているメモリ領域に対して`delete`を実行している

注意点としてはこれはクラスの機能として実装されているので`auto_ptr`自体がポインタというわけではないし、配列のときのように`++`や`--`のようなポインタ演算はできなくなっている

だが、感覚的には同じように扱えて、`*`で値にアクセスしたり`->`でメンバにアクセスすることができる

>`auto_ptr`でアクセスできるのは`new`演算子で確保した分だけであり、`malloc`で確保されたメモリは管理できない  
ちなみに他のスマートポインタなら確保することができる

ちなみに

```c++
my_class*p = new p();
std::auto_ptr<my_class> ptr (p);
```

これでも動く

`auto_ptr`の引数になっているところはポインタを渡しているのでこうやって`new`でメモリを確保したところのポインタを渡しても動く

>そもそも`new`演算子はポインタを返すものだからね

### 生ポインタの確認

さっき`auto_ptr`自体がポインタではないと言った  
ではその変数の実際のポインタにはどうやってアクセスするのかという話になる

結論から言うと`get`関数だ

```c++
std::auto_ptr<int> ptr(new int(1));

int*p = ptr.get();
```

この方法で取得した変数に対して絶対に　`delete`しないようにしよう  
`auto_ptr`はデストラクタが呼ばれたときに`delete`を実行するので二重開放になってエラーになる

メモリを管理していない場合は`NULL`を返す

スマートポインタの生ポインタは極力使わないのが吉

## 所有権

新しい概念  
確保したメモリ領域にアクセスする権利と確保したメモリを開放する義務を誰が持っているか示すもの

```c++
std::auto_ptr<my_class> ptr(new my_class());
```

これは`new`でメモリを確保し、スマートポインタに所有権を渡しているところだ  

よくない例

```c++
my_class*p = new p();
std::auto_ptr<my_class> ptr (p);
delete p;
```

こうすると`ptr`の中身が不定になり、危険なアクセスになる可能性がある
>そりゃあ`ptr`に`p`を渡しててそれがポインタなら`p`への操作は当然`ptr`にも影響するよねっていう

どうしてもやりたいならば

```c++
my_class*p = new p();
std::auto_ptr<my_class> ptr (p);
p = nullptr;
```

としてアクセスできないようにしたほうが良い

### 所有権の取得

`auto_ptr`はコンストラクタにポインタをわたすことで所有権を取得できるが、`reset`関数を使うことによって所有権を再取得することができる

```c++
std::auto_ptr<my_class> mc(new my_class(1));
mc.reset(new my_class(2));
```

所有権の再取得をすると元の所有していたポインタには`delete`が行われ、メモリが開放される  
また、`reset`関数を実行するときに`nullptr`や引数として何も代入しないとメモリの開放を行うことができる

### 所有権の放棄

`release`関数で行える

```c++
std::auto_ptr<my_class> ptr(new my_class(1));

my_class*p = ptr.release();

delete p;
```

注意点としては`release`関数は所有権を放棄するだけでメモリの開放を行わないというところ

メモリの開放を行わないので自分で解放する必要があるところである

## auto_ptrが非推奨の理由

所有権の移動が意図しないところで発生してしまう可能性があるということ

```c++
std::auto_ptr<my_class> mc1(new my_class(1));
std::auto_ptr<my_class> mc2 = mc1;
```

これでコピーをしようとしたのに所有権の移動という動作になってしまう(まぁこうじゃないとメモリの二重解放になっちゃうんじゃないのって思うんだけどね)

他にもメモリの解放が`delete`限定というのもある  
何が悪いのかというと`malloc`で確保したメモリを解放できないという点と、**配列を扱えないという点にある**

配列は`delete[]`で解放する必要があるが`delete`のみしか書かれていないので配列を解放することができない

これらを解決したのが次回以降で説明する`unique_ptr`や`shared_ptr`だ

次回 `unique_ptr`

2022/03/27  
written by 西永
