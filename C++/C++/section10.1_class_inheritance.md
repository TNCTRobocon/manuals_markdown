# 継承

## 継承とは

クラスの機能を受けついで新しいクラスを作り出す機能

ポリモーフィズムと大いに関わる機能  
うまく使えば便利だが、うまく使えないとコードが複雑になるだけでメリットを感じられないことも多い機能

```C++
#include<iostream>

class base_class{
public:
    void print(){
        std::cout << "base class\n";
    }
};

class derived_class : public base_class{
public:
    void print_new{
        std::cout << "derived class\n";
    }
};

int main(){
    derived_class dc;

    dc.print();//base class
    dc.print_new();//derived class
}
```

継承元となるクラスを基底クラス(スーパークラス、親クラス)という  
今回はbase_classが親クラスに当たる

継承をしたクラスを派生クラス(サブクラス、子クラス)という  
今回はderived_classが子クラスに当たる

派生クラスでは基底クラスのメンバを呼び出すことが可能

## 継承の方法

```C++
class base_class{

};

class derived_class : public base_class{

};
```

継承は`子クラス名 : public 親クラス`で表す

`public`のところに関してはあと`private` と `protected`の二種類がある

|private|protected|puvlic|
|-|-|-|
|派生クラスを通じて基底クラスにアクセスできなくなる|派生クラスを通じて継承したクラスからのみアクセスできる|派生クラスを通じて基底クラスにアクセスない|

このような違いがある

## 合成

包含ともいう

あるクラスに別のクラスのインスタンスが含まれること

継承より依存度が低いので含むクラスの設計が変更されても継承よりは影響が低いという関係性がある

## is-a関係とhas-a関係

### is-a関係

AはBであるという関係  
また、AはBの一種という言い方もする  
継承で表現するとだいたい都合が良い

人は哺乳類の一種や剣道部は部活の一種などのような関係

### has-a関係

BはAを持っているという関係  
または含んでいるともいう  
合成で表現するとだいたい都合が良い

車はタイヤを持っている、剣道部は部員を含んでいるなどのような関係

保守性の観点からいうとhas-a関係の方が望ましい

## 継承とコンストラクタ

コンストラクタの呼ばれる順番  
基底クラスのコンストラクタ  
↓  
派生クラスのコンストラクタ  

デストラクタは、  
派生クラスのデンストラクタ
↓  
基底クラスのデストラクタ

## 移譲コンストラクタ

派生クラスのインスタンスを生成するときに基底クラスの引数付きコンストラクタをよびだしたいときに使う

```C++
#include<iostream>
#include<string>

class base_class{
    int num;
    std::string name;

public:
    base_class(int n = 0, const char*s) : num(n), name(s){}
};

class derived_class : public base_class{
public:
    derived_class(int n = 0, const char*s) : base_class(n, s){}
}
```

派生クラスのコンストラクタの引数定義の後ろに`:基底クラス名(引数)`とすることによって基底クラスのコンストラクタに引数を渡せる

メンバイニシャライザと書き方は一緒

2021/01/09
