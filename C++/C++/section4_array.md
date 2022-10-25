# array

## arrayとは

C言語ではデータ型をまとめて扱うときに配列を使ったと思う  
C++でも配列は使えるがそれよりも便利に扱えるコンテナクラス(コンテナ型)を利用することが多い

>コンテナクラスとは
>>STL(Standard Template Library)と呼ばれるものの一部  
いずれ説明する

そして**arrayクラス**はコンテナ型の一つであり、配列よりも便利な機能が用意されている  
書き方さえ覚えてしまえばほとんど同じものとして扱える

使うときにはarrayをインクルードしなければならない

```C++
#include<array>
#include<iostream>

int main(){
    std::array<int, 3> arr{1,2,3};

    for(int i = 0; i < arr.size(); i++){
        std::cout << arr[i] << std::endl;
    }
}
```

## 宣言と初期化

使うときの宣言はこのようにします

```c++
std::array<int, 3> arr;
```

初期化をしない場合はそれぞれの要素の値は不定です

宣言と初期化を同時にやるには以下のようにする

```c++
std::array<int, 3> arr1{1, 2, 3};
std::array<int, 3> arr2 = {1, 2, 3};

std::array<int, 3> arr3 = {1, 2};//足りない分は0で埋められる

std::array<int, 3> arr4 = {1, 2, 3, 4};//初期化子が多すぎるためエラー

std::array<int> arr5 = {1, 2, 3};//要素数を省略してしまっているためエラー
```

## 代入操作

arrayの代入は配列より直感的で簡単でわかりやすい

```C++
std::array<int, 3>arr1 = {1, 2, 3};
std::array<int, 3> array2;

arr2 = arr1;//コピー完了
```

arrayクラスでは=によって代入が可能  
わざわざfor文を使っていた頃にはもう戻れません(誇張)

ポインタを使った移動でもないのでこの後書き換えても他の変数に影響を及ぼすなんてことはないので安心だ

ただし、全要素のコピーなのでポインタでの受け渡しよりも時間がかかる
計算量はO(n)[^1]

[^1]: 計算量の詳しい話については../../others/computational_complexity/computational_complexity.mdを参照

## 各要素へのアクセス

```C++
std::array<int, 3> arr = {1, 2, 3};

arr[0]  = 10;
//arr = {10, 2, 3} となっている

```

配列とまったく同じであるので詳しい説明などは省略する

## 二次元配列

```c++
std::array<std::array<int, 3>, 2> arr_2d{{
    {1, 2, 3},
    {4, 5, 6},
}};

//指定方法
arr_2d[2][1];
```

使い方は配列とほぼ同じ  
使い方の注意としては配列の時とは違い、要素数の並び順が逆転する  
そこが躓きやすい点なので注意

配列よりも劣る点として唯一上げられるところはstd::arrayを二つも書くので記述量が多くなる点である。(ﾒﾝﾄﾞｸｻｲ)

## 関数

arrayクラスには便利な関数がたくさんあるのでいくつか紹介

### size関数

要素数を返してくれる

```c++
std::array<int, 3> arr = {1, 2, 3};

arr.size();//3
```

戻り値の型はsize_t型

### front関数, back関数

```c++
std::array<int, 3> arr = {1, 2, 3};

arr.front();//1
arr.back();//3

arr.back() = 10;//書き換えもできる
```

`front()`は`arr[0]`と変わらないので使い道は余りないが、`back()`は要素数にかかわらず最後の要素にアクセスできるので便利

### fill関数

同じ値をすべての要素にセットする

```c++
std::array<int, 3> arr;

arr.fill(1);//すべての要素に1を代入

std::fill(arr.begin(), arr.end(), 3);//指定したイテレータの範囲で数字を代入する
```

他のコンテナ型にはfill関数は存在しないので代わりにassign関数を使う

arrayクラスに関してはfillもassign関数も同じ

fill関数は標準関数として用意されてるのでこれも利用できる
ただし、algorithmをインクルードする必要がある  
イテレータに関してはsection5で説明する

### swap関数

swap関数は二つのarrayオブジェクトの要素を丸ごと入れ替える

```c++
std::array<int, 3> arr1{ 1, 2, 3 };
std::array<int, 3> arr2{ 4, 5, 6 };

arr1.swap(arr2);//これでarr1とarr2が入れ替わった

std::swap(arr1, arr2);//標準関数
```

ちなみにswap関数は標準関数として用意されているのでこれも利用できる
これもalgorithmをインクルードする必要がある

2021/12/2  
written by 西永
