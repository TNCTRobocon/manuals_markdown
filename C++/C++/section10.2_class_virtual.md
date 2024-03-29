# 仮想関数

ポリモーフィズムを実現する

## 仮想関数の作り方

```C++
#include<iostream>

class human{
public:
    virtual void talk() const {
        std::cout << "hello" <<std::endl;
    }
};

class japanese final : public human{
public:
    void talk() const override {
        std::cout << "こんにちは" << std::endl;
    }
};

void lets_talk(human&Human){
    Human.talk();
}

int main(){
    human John;
    japanese Taro;

    John.talk();//hello
    Taro.talk();//こんにちは

    lets_talk(John);//hello
    lets_talk(Taro);//こんにちは
}
```

>このコードはきちんとしたis-a関係になっていない  
きちんとしたやつはこの後の純粋仮想関数を参照

### virtual

基底クラスのメソッドにvirtualを付けると仮想関数になる

仮想関数は普通のメソッドと変わらないが、派生クラスで機能が上書きされる可能性のある関数という意味になる

必ず上書きされるわけではない

基底クラスのインスタンスを生成しても普通のメソッドとして使うことができる
>オブジェクトのポインタ経由で仮想関数を呼び出すと仮想関数テーブルを読みだす工程があるので通常メンバ関数と比べて若干遅くなる

### override

基底クラスの仮想関数を上書きする関数  
引数や戻り値、constの有無などシグネチャ(関数定義)がすべて一致する必要がある

基底クラスで仮想関数に指定されていないメソッドをオーバーライドするとエラーになる

>派生クラスではoverrideやvirtualを記述しなくてもオーバーライドは可能である  
しかし、これらのキーワードがないとシグネチャが異なるときにオーバーライドにならず新しいメソッドを定義したことになる  
これらのキーワードをつければ記述ミスがあった時などにエラーになってくれてバグを防ぐことができる

### final

継承できないものを作ることができるようになる

`class`に付ければ継承できないクラスが、メソッドの後につければ継承のできないメソッドの完成

finalを付けるとこれ以降で継承が行われないので保守性が上がるというメリットがある

>virtualの項で話した仮想関数テーブルがこれを付けることで読み込まれなくなるので若干の高速化が見込める場合がある

### ポリモーフィズム

lets_talk関数を見て何か思うところはないだろうか

仮引数を見てほしい  
`human&Human`となっている

>基底クラスは派生クラスのインスタンスを受けとれる
なぜなら、派生クラスは基底クラスを含むクラスである  
よって派生クラスには基底クラスのメソッドがあることが保証されているので呼び出すことができる

表示される文字列が変わっていることに違和感を感じる人もいるだろう

これがオーバーライドの力である

結果として上書きされて同じ関数でも違う結果が帰ってくるポリモーフィズムをよく表せている

ただし、上記のような呼び出し方ができるのはポインタか参照の時のみなので注意

>コピー代入はキャストされるのできちんとしたポリモーフィズムを実現できない

これはスライシングと言い、避けるべきとされる

```C++
void lets_talk(human Human){
    Human.talk();
}

int main(){
    human John;
    japanese Taro;

    lets_talk(John);//hello
    lets_talk(Taro);//hello
}
```

コピーすると派生クラスの情報がすべて失われてしまう  

ちなみに基底クラスのインスタンスを派生クラスとしてコピーするのはエラーになる

## 隠蔽

オーバーライドに似て非なるもの

派生クラスに基底クラスにあったメソッドと同じ名前のメソッドを定義すること

`override`を使わずに記述すると名前が見えなくなり、アクセスができなくなる  
ポインタなどを使ってアクセス使用としても多様性はないのでせっかくのオブジェクト指向なのにもったいない

```cpp
#include<iostream>

class human{
public:
    void talk() const {
        std::cout << "hello" <<std::endl;
    }
};

class japanese final : public human{
public:
    void talk() const {
        std::cout << "こんにちは" << std::endl;
    }
};

void lets_talk(human&Human){
    Human.talk();
}

int main(){
    human John;
    japanese Taro;

    John.talk();//hello
    Taro.talk();//こんにちは

    lets_talk(John);//hello
    lets_talk(Taro);//hello
}
```

## 仮想関数とnew演算子

```C++
class base{

};

class derived : public base{

};

int main(){
    base *b = new derived();
    delete b;
}
```

こうやってもインスタンスが生成できる

しかし、派生クラスのメンバにはアクセスできないので注意

virtualと付ければメソッドは派生クラスにアクセスできる

2021/01/10
written by 西永
