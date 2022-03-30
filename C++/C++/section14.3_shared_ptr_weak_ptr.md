# shared_ptrとweaK_ptr

## shared_ptr

他のインスタンスと所有権を共有できるスマートポインタ  
内部的に所有権を持つオブジェクトの数をカウントしてどのオブジェクトからも参照されなくなり、カウンタが0になると自動的にデリータが呼ばれてメモリが解放されるもの

生ポインタの取得や所有権の取得は他のスマートポインタと一緒

### 所有権の移動

`unique_ptr`でも用いた`std::move`を使う

### 所有権のコピー

普通のコピー動作で所有権を複数に分散できる

```c++
#include<iostream>
#include<memory>

struct my_struct{
    my_struct(){std::cout<<"constructor"<<std::endl;}
    ~my_struct(){std::cout<<"destructor"<<std::endl;}
};

int main(){
    std::shared_ptr<my_struct> ms1 = std::make_shared<my_struct>();

    std::shared_ptr<my_struct> ms2 = ms1;//コピー
    std::shared_ptr<my_struct> ms3(std::move(ms1));//ms1の所有権の移動
    {
        std::shared_ptr<my_struct> mc4 = ms2;
        //ここでmc4が破棄される
    }
    std::cout<<"===end main==="<<std::endl;
    return 0;
}
```

結果としては

```markdown
constructor
===end main===
destructor
```

となる

ちゃんとカウントされて所有権をもってるインスタンスの数がカウントされてるんですね  
ならば今いくつの数のインスタンスが所有権を持ってるか確かめる方法があるんじゃないかということで

### use_count

メモリの所有権を持つインスタンスの数を表すメンバ関数が`use_count`メンバである

また所有権を持つのが自分だけか確かめる関数もあり、`unique`関数という

それぞれ`shared_ptr`のメンバ関数である

### 配列

本来`shared_ptr`は配列を扱えないが少し工夫すれば扱える  

```c++
std::shared_ptr<int> ptr(new int[5], std::default_delete<int[]>());
```

コンストラクタの第一引数に`new`でメモリを確保し、第二引数に`std::default_delete<データ型[]>()`を渡す  
これは`deleter`の指定と一緒のこと

`shared_ptr`のデフォルトの`deleter`は`std::default_delete`で用意されてるテンプレート引数を指定することで行けるようになる

>各要素へのアクセスは`get`関数で生ポインタを取得してそれのあとに添字演算子(`[]`)でアクセスすることになるので本当にあまり向いていない

## weak_ptr

~~よわよわptr~~  
`shared_ptr`とセットで利用されるスマートポインタ

`shared_ptr`と違って所有権を持たない(弱参照とも言う)

### そもそもなんで必要なのか

`shared_ptr`は性質上循環参照を起こす可能性がある

```c++
#include<iostream>
#include<memory>

struct my_struct{
    my_struct(){std::cout<<"constructor"<<std::endl;}
    ~my_struct(){std::cout<<"destructor"<<std::endl;}

    std::shared_ptr<my_struct> ms;
};

int main(){
    std::shared_ptr<my_struct> ms1 = std::make_shared<my_struct>();
    std::shared_ptr<my_struct> ms2 = std::make_shared<my_struct>();

     ms1->ms = ms2;
     ms2->ms = ms1;

    std::cout<<"===end main==="<<std::endl;
    return 0;
}
```

結果は

```markdown
constructor
constructor
```

となり、デストラクタが呼ばれていないのがわかるだろうか

理屈は`ms1`を破棄するとき`ms2`に参照されてるからデストラクタを呼ばない、  
次に`ms2`を破棄するときに`ms1`から参照されていて、なおかつさっき`ms1`が削除されていないのでデストラクタが呼ばれないという問題がある

これは`weak_ptr`で解決できる

```c++
struct my_struct{
    my_struct(){std::cout<<"constructor"<<std::endl;}
    ~my_struct(){std::cout<<"destructor"<<std::endl;}

    std::weak_ptr<my_struct> ms;
};
```

これでいける

`weak_ptr`での所有権の確保が行われていないので循環参照が起こることはない

また、`weak_ptr`はコピー操作やコンストラクタへの指定が許可されている

加えて他のスマートポインタと同様にムーブでの移動も可能  
所有権の移動は起きないが、ムーブ元の`weak_ptr`の参照が失われるのでアクセスできなくなる

### 参照先へのアクセス

`lock`関数を使う

そのまま生ポインタにアクセスしてしまうとメモリを解放されてしまう可能性がある  　
それを極力排除するためにこの関数を使う

これは参照元の`shared_ptr`をかえすのでそれを介して値にアクセスするという~~めんどくさい~~ことをする必要がある

### 参照の解放

`reset`関数で参照元の解放ができる

あくまで参照されなくなるだけなのでメモリの解放もないし他の`weak_ptr`の参照を得ることなどはできない

### 参照先の状態確認

参照先の`shared_ptr`が解放されているか否かは`expired`関数で確認できる  

```c++
std::shared_ptr<int> ptr1 = std::make_shared<int>(0);
std::weak_ptr<int> w_ptr(ptr1);

if(w_ptr.expired()){
    std::cout <<"参照もとがあ〜る"<< std::endl;
}else{
    std::cout <<"なーい"<< std::endl;
}
```

こんな感じで書ける

危険なアクセスをする気がしたら`weak_ptr`を使おう

2022/03/31  
written by 西永
