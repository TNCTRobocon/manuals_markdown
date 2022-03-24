# コンストラクタとデストラクタ

## コンストラクタ

インスタンスが生成されたときに実行されるメソッド

クラスで何らかの変数を初期化したい、やりたいことがあるとする  
そういう時にわざわざinitializeメソッドを作って実行をするのも非常に不便であり、めんどくさいのでコンストラクタを使おうという話

### コンストラクタの定義方法

```c++
#include<iostream>
class constructor{

public:
    constructor(){
        cout<<"コンストラクタ";
    }
};

int main(){
    constructor c_class;
}
```

結果

```markdown
コンストラクタ
```

このようにインスタンスを生成したときに自動でコンストラクタが実行されるのが分かったと思う  
また、通常のメソッドとは違い、あとから呼び出して使うことができない

書き方としては戻り値を持たない、クラスと同じ名前にするという必要があると言うところに注意

#### 引数付きコンストラクタ

コンストラクタにも当然引数をつけることができる

```C++
#include<iostream>
#include<string>

class arg_constructor{
    int num;
    std::string str;

public:
    arg_constructor(){
        std::cout<< "no argument"<< std::endl;

        num = 0;
        str = "";
    }

    arg_constructor(int _num, std::string _str){
        num = _num;
        str = _str;
    }

    void show_num(){
        std::cout << num << std::endl;
    }

    void show_str(){
        std::cout << str << std::endl;
    }
};

int main(){
    arg_constructor ac1;
    arg_constructor ac2(0, "hey constructor!");

    ac2.show_num();
    ac2.show_str();
}
```

結果

```markdown
no argument
0
hey constructor!
```

>string型については自分で調べてみてほしい  
cの文字列よりも圧倒的に使いやすくなっているのでぜひ

このようにしてコンストラクタに引数をつけることができる

#### コンストラクタを省略した場合

コンパイラが自動的に何もしないコンストラクタを生成する

#### メンバイニシャライザ

コンストラクタで呼び出すときに変数を初期化する  
その時にメンバ変数にそのまま値を代入しても良いのだが、この方法で行われることも多い

```C++
//以上は前のコード例と同じ
class arg_constructor{
    int num;
    std::string str;

public:
    arg_constructor(int _num, std::string _str):num(_num), str(_str){
    }
    //コード
}
//以下は前のコード例と同じ
```

このように初期化することができる  
こうすると効率的に初期化を行うことが可能である

注意点としてメンバイニシャライザはフィールドの順番と同じにしなければいけないというところがある  
→クラスで宣言した順番で初期化しなければいけない

>効率的に行える理由
>>オブジェクトがインスタンス化される際の流れは、次のような感じになっている  
１．オブジェクトをインスタンス化する  
２．クラスが持つメンバ変数のコンストラクタが起動し、中に書かれている処理が実行される  
３．コンストラクタの内容が実行される  
２の部分で、メンバ変数のコンストラクタが呼び出されていて、それぞれ初期化済みになっている。 メンバイニシャライザを使わずに代入で初期化しようとすると、それは３のタイミングになるので、 ２と３とで、処理が重複してしまう

### コピーコンストラクタ

#### デフォルトコピーコンストラクタ

```C++
#include<iostream>
#include<string>

class arg_constructor{
    int num;
    std::string str;

public:
    arg_constructor(){
        std::cout<< "no argument"<< std::endl;
    }

    arg_constructor(int _num, std::string _str){
        num = _num;
        str = _str;
    }

    void show_num(){
        std::cout << num << std::endl;
    }

    void show_str(){
        std::cout << str << std::endl;
    }
};

int main(){
    arg_constructor ac1(0, "copy");
    arg_constructor ac2(ac1);//コピーコンストラクタ
    //ac2 = ac1;でも可

    ac2.show_num();
    ac2.show_str();
}
```

結果

```markdown
0
copy
```

ac1とac2が一緒なことがわかるだろうか

正しくはコンストラクタの引数をコピーする  
この場合のコピーコンストラクタをデフォルトコピーコンストラクタという

#### デフォルトコピーコンストラクタの危険性

```C++
class copy_c{
    int*p;

public:
    copy_c(int*_p) : p(_p) {}

    get(int i){
        *p = i;
    }
};

int main(){
    int num = 0;

    copy_c cc1(&num);
    cc1.get(1);
    copy_c cc2(cc1);
    cc2.get(10);//cc1のポインタの中身の値も10になる
}
```

このように、使うと関係のないインスタンスのcc1, cc2がポインタを通じてそれぞれ勝手に書き換えられてしまう  
これはエラーの原因になるので気を付ける

#### コピーコンストラクタの定義

コピーコンストラクタを定義することでエラーを避ける

```C++
class copy_c{
    int*p;

public:
    copy_c(const int*_p) : p(_p) {}

    copy_c(const copy_c&c){
        p = c.ptr;
        std::cout<<"copy constructor"<<std::endl;
    }

    get(int i){
        *p = i;
    }
};

int main(){
    int num = 0;

    copy_c cc1(&num);
    cc1.get(1);
    copy_c cc2(cc1);
    cc2.get(10);
}
```

今回はコピーしたクラスのメンバのポインタをコピーする処理を書いた  
ここは任意の処理を書くとよい  
>本番ではこんなコード書かないでください  
スパゲッティの元です

また、クラスのインスタンスを実引数として直接代入すると遅い操作になるので、**参照かポインタで代入する**ことを強くお勧めする

参照の場合もポインタの場合も仮引数にconstを付けて書き換えをできないようにした方が安全である

#### コピーコンストラクタの禁止

いっそコピーコンストラクタを禁止してしまおう

```C++
class copy_c{
    int*p;

    copy_c(const copy_c&c){//コピーコンストラクタの禁止
        p = nullptr;
    }

public:
    copy_c(const int&_p) : p(_p) {}

    get(int i){
        *p = i;
    }
};

int main(){
    int num = 0;

    copy_c cc1(&num);
    cc1.get(1);
    copy_c cc2(cc1);//エラー
}
```

privateでコピーコンストラクタを定義するとインスタンスを生成した時点でエラーになる  

自動生成されるコンストラクタは別の記法でも禁止することができる(C++11以降)

```C++
class copy_c{
    int*p;

public:
    copy_c(int*_p) : p(_p) {}

    copy_c(const copy_c c&) = delete;
}
```

お好みでどうぞ

ちなみにこれでも代入操作に対する対策ができていない  
それの対策については今まで教えた知識では少し足りないのでまた後で説明する

## デストラクタ

インスタンスを破棄したときに行われるメソッド  
メモリの解放などを行うことが多い

コンストラクタと同様に何も記述しなければ何もしないデストラクタが呼び出される

書き方はコンストラクタと同じようにクラス名と同じ名前で書き、頭にチルダ(~)をつける  
また、戻り値、引数を持たないという特徴を持つ

```C++
class destructor_c{
    int*p;

public:
    destructor_c(int i = 10){
        p  = new int[i];
    }

    ~destructor_c(){
        delete[] p;
    }
}
```

## new演算子とクラス

`new`を使うとクラスのコンストラクタを呼び出すことができる  
また、`delete`を使うとデストラクタを呼び出すことができる

```c++
#include<iostream>
#include<stdlib.h>

class hoge{
    hoge(){
        std::cout<<"コンストラクタ"<<std::endl;
    }

    ~hoge(){
        std::cout<<"デストラクタ"<<std::endl;
    }
};

int main(){
    hoge*new_hoge;
    hoge*malloc_hoge;

    std::cout<<"new"<<std::endl;
    new_hoge = new hoge();
    std::cout<< "malloc" <<std::endl;
    malloc_hoge = (hoge*)malloc(sizeof(hoge));

    std::cout<<"delete"<<std::endl;
    delete new_hoge;
    std::cout<<"free"<<std::endl;
    free(malloc_hoge);
}

```

```markdown
new
コンストラクタ
malloc
delete
デストラクタ
free
```

このように、mallocとfreeではコンストラクタとデストラクタは呼び出されず、newとdeleteではコンストラクタもデストラクタも呼び出されるという結果になった

2021/12/19  
written by 西永
