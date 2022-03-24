# move

ムーブとはあるオブジェクトから他のオブジェクトにリソースを引き渡すことである。  
値のコピーではコストが高くつく場合は、より高速に値を別の変数へ移すことができる。
リソース明け渡し後のオブジェクトには何が入っているのか不明となり、値を参照した時の動作は対象オブジェクトの型に依存する。 後述する所有権の移動を除けば、一般にはムーブ後オブジェクトの状態は明確に規定されない事が多い。
>引用元 https://cpprefjp.github.io/lang/cpp11/rvalue_ref_and_move_semantics.html

これがmoveの説明だがわかっただろうか  

要するに**高速で代入を行える**が**代入した変数の値が何になってるかが保証されてない**から気をつけてねというもの

書き方としては

```c++
type_t hoge;
type_t huga = std::move(hoge);//これ以降hogeは不定になる
```

前回説明したが、`move`が右辺値として扱われていた事を覚えているだろうか  

なんと、`move`を使うと左辺値を右辺値として扱うようにできるようになるのだ

## なぜmoveが必要なのか

高速で移動させたくてもう使わないというときなどに有効

### 例

右辺値1回代入されたら破棄されるものなので使われることはないという暗黙の合意がある  
つまり、右辺値として渡された時点でもうどこかで使うつもりはないということを意識する必要がある  
こういうことならば最後に支障がでなければどのように値を壊しても問題ないということになる

この約束があってできるようになることはオブジェクトの移譲、メモリ管理権の移譲である

ここで2つの値を交換するプログラムを考える

```c++
void swap(my_class&a, my_class&b){
    my_class temp = a;
    a = b;
    b = temp;
}
```

ここで`my_class`のサイズが大きかったらどうなるだろうか  
当然コピーに時間がかかってしょうがないだろう

ムーブを用いると

```c++
void swap(my_class&a, my_class&b){
    my_class temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
}
```

このように記述できる

`move`はコピーよりも高速なので`my_class`のサイズが大きくても高速で値の操作ができる

こんな感じ

## ムーブコンストラクタ

`section9.2_class_constructor.md`でやった内容を覚えてくれているだろうか

今回はそれの新しい種類を教える

ムーブコンストラクタだ

書き方を見せたほうが早いだろう

```c++
class move_class{
    int i;
public:
    move_class(){
        //色々な処理
    }

    move_class(const move_class& mc1){//コピーコンストラクタ
        //色々な処理
    }

    move_class(move_class&& mc2){//ムーブコンストラクタ
        //色々な処理
    }
};
```

これで書き方はなんとなくわかっただろうか  
では、ムーブを使うのはどういうときか、それは保持してるポインタを渡したいときだ  
また、ポインタを渡して渡した元がポインタを放棄しないと関係が複雑になるので、ポインタを渡したら渡した元を`null`にするようにしよう

基本的に使うことはそう多くないが覚えていて損はないだろう

また、そうそうないだろうが`move`を使ってもムーブコンストラクタが呼ばれないことがある

例としては

```c++
#include<iostream>

class my_class{
public:
     my_class(){
          std::cout<<"constructor"<<std::endl;
     }
    my_class(const my_class& lc){
         std::cout<<"copy constructor"<<std::endl;
    }
    my_class(my_class&&lc){
         std::cout<<"move constructor"<<std::endl;
    }
    ~my_class(){
         std::cout<<"destructor"<<std::endl;
    }
};

int main(){
     my_class mc1;
     const my_class mc2;
     my_class mc3 = std::move(mc1);
     my_class mc4 = std::move(mc2);
     return 0;
}
```

実行してみると

```markdown
constructor
constructor
move constructor
copy constructor
destructor
destructor
destructor
destructor
```

`main`関数4行目のムーブコンストラクタが呼ばれてないのがわかるだろうか

`const`をつけた変数のムーブだとコピーコンストラクタが呼ばれてしまう  
気づけないと本当にずっと沼るので気をつけましょう

### noexcept

例外やってから教えるので名前を頭の片隅に入れるだけで今は大丈夫

2022/03/25  
written by 西永
