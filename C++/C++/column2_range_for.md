# 範囲for文と条件付きif文

## foreach

C++11ではforの仕様が拡張され、配列やコンテナ型などのデータの集合に対して新しいループ方法が用意されている

~~イテレータでforの条件書くのめんどくさいからね~~

他の言語だとforeachという構文で用意されている

`vector`クラスや`array`クラスなどの配列で一回ずつアクセスするという条件でループ処理を行うならば有用な方法である

```C++
std::vector<int> vec = {0, 1, 2, 5};

for (int v : vec){
    std::cout <<v << std::endl;
}
```

```markdown
0
1
2
5
```

`v`にはその配列要素のコピーが入る  
なので書き換えても元データには影響しない

配列要素のコピーなので`v`の型は配列の要素の型に依存する  
いちいち調べるのも面倒なのだが、`auto`を使うと楽に書ける

また、先ほど、`v`はコピーといった。つまり、`each`の中で`v`を書き換えても`vec`の中身は書き変わらない  

これも中身の書き換えができるようにすることができる

```C++
std::vector<int> vec = {0, 1, 2, 5};

for (auto&v : vec){
    v *= 2;
}

std::cout << vec << std::endl;
```

```markdown
0
2
4
10
```

見事に中身が書き変わった

さらに、`const`を付けて参照元の書き換えを不可能にすることもできる

```C++
std::vector<int> vec = {0, 1, 2, 5};

for (const auto&v : vec){
    v *= 2;//error
}
```

コンパイルした時点でエラーが発生する

|`auto v`|`auto&v`|`const auto&v`|
|-|-|-|
|コピー|参照|const付き参照|

しかし、この便利な範囲for文も注意するべき点がある

for文を使っている最中に要素の追加や削除を行ってはいけない  
これは範囲for文の中でイテレータというものが使われているのだが、要素の追加や削除が行われるとそのイテレータが無効になり、範囲for文が使えなくなってしまうからだ。

## 進化したif文

if文の中で初期化を行えるようになった(C++17)

```C++
if ( auto status = func(); status.isError()){
    cout << status.getMessage();
}
```

このようにif文の中で初期化を可能にした

`switch`文でも同様の記述が可能になった

従来のif文も参考までに載せておく

```C++
{
    status = func();
    if(status != SUCCESS){
        ...
    }
}
```

このようにネストを一つ深くして書くので冗長になる  

ちなみに、C++20からは範囲for文でも初期化式を入れることができる

```C++
for(T thing = f(); auto&v : thing.item()){
    ...
}
```

このように一つの文で初期化条件を指定できる

2022/01/21
written by 西永
