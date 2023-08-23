# unique_ptr

※C++11以降で使うことができる

前回所有権についてやったのを覚えているだろうか  
この`unique_ptr`は所有権を唯一(`unique`)にするように振る舞うスマートポインタである

よってコピー操作が禁止されていたりする  
生ポインタの取得や所有権の取得や放棄は`auto_ptr`と同様にできる(`get`関数、`reset`関数、`release`関数)

## 所有権の移動

`unique_ptr`で所有権を移動させるにはムーブを使う必要がある

```c++
std::unique_ptr<my_class> smart_ptr1(new my_class(1));
std::unique_ptr<my_class> smart_ptr2;

smart_ptr2 = smart_ptr1;//error

smart_ptr2 = std::move(smart_ptr1);//ok

std::unique_ptr<my_class>smart_ptr3(std::move(smart_ptr2));//ok
```

コピー動作はコンパイルエラーになるので禁止されている

ただし、`section13`でやったようにムーブを行うことによってならポインタの所有権を移動させることができる

注意点として所有権を移動させた後は元のインスタンスを利用しないようにする必要がある

また、別で再度メモリ領域を割り当てることも可能である

## 所有権の確認

インスタンスを直接条件式に入れることで所有権の有無を確認できる

```c++
std::unique_ptr<my_class> smart_ptr1(new my_class(1));
std::unique_ptr<my_class> smart_ptr2 = std::move(smart_ptr1);

if(ptr1){
    std::cout<<所有権あり<<std::endl;
}else{
    std::cout<<所有権なし<<std::endl;
}

if(ptr2){
    std::cout<<所有権あり<<std::endl;
}else{
    std::cout<<所有権なし<<std::endl;
}
```

```markdown
所有権なし
所有権あり
```

## 配列

`unique_ptr`では配列を扱える

```c++
std::unique_ptr<int[]> smart_ptr(new int[5]);

for(int i = 0; i <= 5; i++){
    smart_ptr[i];
}
```

## deleter

そもそも`deleter`とはスマートポインタのインスタンスが破棄されるときに呼ばれる関数

前回`malloc`関数で確保したメモリも解放できると言ったがそれは別に終了処理を書き換えてやる必要がある

指定方法は複数ある

### 関数オブジェクト

一般的な指定方法

```c++
#include<iostream>
#include<memory>
#include<cstdlib>

struct deleter_malloc{
     void operator()(int*i) const {
          free(i);
     }
};

int main(){
     int* p = (int*)std::malloc(sizeof(int));

     std::unique_ptr<int, deleter_malloc> s_ptr(p);
}
```

簡単ですね  
関数オブジェクトを`unique_ptr`に渡してるだけだから


### 関数を直接渡す

```c++
#include<iostream>
#include<memory>
#include<cstdlib>

void deleter_malloc(int*i){
     free(i);
}

int main(){
     int* p = (int*)std::malloc(sizeof(int));

     std::unique_ptr<int, decltype(&deleter_malloc)> sptr(p, deleter_malloc);
}
```

これは上に比べて少しわかりにくい

`unique_ptr`のテンプレート引数の第二引数に関数の型、コンストラクタの第二引数にテンプレート関数のポインタを渡せばおk

>`decltype`とは型情報を返してくれる偉いやつ
またいずれ書くだろう

## make_unique

インスタンス生成に使えるやつ

```c++
std::unique_ptr<int> s_ptr1 = std::make_unique<int>(1);

std::unique_ptr<int[]> s_ptr2 = std::make_unique<int[]>(5);
for (int i = 0; i < 5; i++) s_ptr2[i] = i;
```

C++14以降で使える機能

2022/03/30  
written by 西永
