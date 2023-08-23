# 抽象クラス

## 純粋仮想関数

```C++
#include<iostream>

class human{
public:
    virtual void talk() const = 0;//純粋仮想関数
};

class american : public human{
public:
    void talk()const override{
        std::cout << "hello" << std::endl;
    }
};

class japanese : public human{
    void talk()const override{
        std::cout << "こんにちは" <<std::endl;
    }
};

void lets_talk(const human&Human){
    Human.talk();
}

int main(){
    american john;
    japanese taro;

    lets_talk(john);
    lets_talk(taro);
}
```

`virtual void talk() const = 0;`の部分を純粋仮想関数という

書き方としては仮想関数の最後の部分に`=0;`を付けるだけ

純粋仮想関数には処理の定義がなく、*必ず派生クラスでオーバーライドして関数を定義する必要*がある  
オーバーライドする側では通常の仮想関数をオーバーライドするのと同じようにすればok

また、純粋仮想関数を持つクラスはインスタンスを生成できないことも注意してほしい

純粋仮想関数を含むクラスを**抽象クラス**という

### 純粋仮想デストラクタ

抽象クラスはインスタンスが生成されては困る、しかしあったほうがクラス設計が簡単になる場合に有効  

だが、時にはクラスの設計の都合上抽象クラスにしたいけれどメンバ関数に純粋仮想関数が作れない場合が時々ある

そういう時に有効なものが純粋仮想デストラクタである

純粋仮想デストラクタは*何があっても定義を省略することができない*ので注意が必要  
クラス内にまとめて書くこともできないので注意

## インターフェース

抽象クラスの一つではないが触れておく

C++にそういう機能はないが抽象クラスを利用したクラスにインターフェースクラスというのがある

### インターフェースクラスとは

メンバ変数を持たず、すべてのメソッドが純粋仮想関数で構成されているクラス

派生クラス側では必ずインターフェースクラスのメソッドを持つことが保証されてる

```C++
#include<iostream>
#include<string>

class Icopy_string{
public:
    virtual Icopy_string* copy() = 0;
};

class test_class : public Icopy_string{
    std::string str;

public:
    test_class(const char *s = "") : str(s) {}

    test_class* copy() override{
        std::cout << "copy" << std::endl;
        test_class *t = new test_class();
        t->str = str;

        return t;
    }

    void print(){
        std::cout << str << std::endl;
    }
};

int main(){
    test_class tc1("ABC");

    testclass *tc2 = tc1.copy();
    tc2.print();

    delete tc2;
    tc2 = nullptr;

    return 0;
}
```

クラス`Icopy_string`は純粋仮想関数を一つ持つ抽象クラスである  
抽象クラスなのでそれ単体ではインスタンスを生成できない

copyメソッドをかならず別で定義しなければならない

インターフェースを作った時、クラス名の頭に`I`が付けられることが多い  
インターフェースであるということを強調するために付けられる

### 共変型

共変型サンプルコードでは基底クラスのメソッドcopyと派生クラスのメソッドcopyでは戻り値の型が異なる  
本来、オーバーライドは戻り値の型が一致しいてることが必要と述べた

ただし、例外があり、

基底クラスで仮想関数の戻り値の型が基底クラスのポインタ型、参照型である

かつ

派生クラスでオーバーライドする関数の戻り値が派生クラスのポインタ型、参照型であればオーバーライド可能である

### can-do関係

インターフェースクラスはそれを継承したクラスのできることを(最低限)保証しているとも言える

この関係をcan-do関係という(継承の一種なのでis-a関係ともいえる)

## 抽象クラスとインターフェースクラスの違い

### インターフェースクラスの特徴

クラスの型を指定するもの  
カプセル化とポリモーフィズムを要求する意味合いが強い

実装クラスは、全ての純粋仮想関数を実装する必要ある

### 抽象クラスの特徴

継承関係をもつ実装の再利用をできる  
継承と多態性を要求する意味あいが強い

共通して使える関数があるならばそれを使える

### 結論

クラス仕様としての型定義したいならインタフェース  
継承関係にあって処理の再利用したいなら抽象クラス
