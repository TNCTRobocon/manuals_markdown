# static

## 静的なメンバ

### 静的メンバ変数

すべてのインスタンスで共通の値を持つメンバ変数

```C++
#include<iostream>

class static_c{
    int num = 0;
    static int static_num;

public:
    void num_set(int i){num = i;}
    void static_set(int i){s_num = i;}

    void show_num(){std::cout<<num<<std::endl;}
    void show_static(){std::cout<<s_num<<std::endl;}
};

static_c::s_num = 1;

int main(){
    static_c s1, s2;

    s1.num_set(10);
    s1.static_set(20);

    s1.show_num();//10
    s1.show_static();//20

    s2.static_show();//20

    s2.num_set(30);
    s2.static_set(40);

    s2.nums_how();//30
    s2.static_show();//40

    s1.static_show();//40
}
```

このようにインスタンスs1を通してs2の、s2を通してs1の静的メンバ変数`static_num`が書き変わっているのがわかるだろうか

インスタンスに依存せずにクラスに依存する変数となる  
またいくらインスタンスを生成しても静的メンバ変数は一つしか作られないのでメモリの節約になる

static変数の定義はクラス外で行う  
ファイル分割をしたときはヘッダファイルに静的メンバ変数の実体を置くと多重定義になってエラーになる
static変数は初期値を与えなければデフォルトで0が入る  
ただし`const static`とした場合はクラス内で定義できる

クラスに依存しているので`クラス名::静的メンバ`という風にアクセスすることも可能である

### 静的メンバ関数

インスタンスを生成せずに使えるクラス内のメソッド

これも`クラス名::静的メソッド`と書ける

また、通常メンバ変数にアクセスすることができないことも注意が必要
>thisポインタを持たないため  
静的なメンバにアクセスすることは可能  
アクセサの設定次第でアクセスは可能

2022/01/06
written by 西永
