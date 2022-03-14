# 右辺値ってなんだろう

右辺値という言葉と左辺値という言葉を解説していくよ

## 式(`expression`)を分解していこう

```c++
int i = 0;
1;
func();
&func;
```

これらはすべて何らかの値であり、オブジェクトかポインタである

まず分類としては`glvalue`, `rvalue`があり、  
`glvalue`は`lvalue`か`xvalue`に分類される  
そして、`rvalue`は`xvalue`に分類される

関係としてはこんな感じ

```markdown
      expression  
       /     \  
   glvalue  rvalue  
   /    \    /    \  
lvalue_1  xvalue  prvalue  
```

### `lvalue`(左辺値)

```c++
int lvalue;
lvalue = 0;
```

`lvalue`のように左辺に置くことができる数のことを指す

基本的に名前のつけられるものとして捉えてもらって構わない

### `rvalue`(右辺値)

```c++
int lvalue_1 = 1, lvalue_2 = 2;
f();
int&&r_ref = static_cast<int&&>lvalue_1;//右辺値参照にキャストする詳しくはsection13.1_rvalue_reference.mdを参照
int k = std::move(lvalue_2);//move、詳しくはsection13.2_move.mdを参照
```

一度使ったらなくなる値  
基本的に左辺に来ることはない(右辺値参照)
下記の`prvalue`と`xvalue`に分類できる

### `prvalue`(純粋右辺値(`pure rvalue`))

```c++
1;
2+3;
```

名前なしのオブジェクトや計算結果などの一時的なオブジェクトのこと  
ほとんどの場合式を評価するときに自動的に生成されて自動的に破棄されるので特に意識することはない

### `xvalue`(死にかけの値(`eXpiring value`))

```c++
int lvalue_1 = 1, lvalue_2 = 2;

int&& r_ref = static_cast<int&&>lvalue_1;
int move = std::move(lvalue_2);
int return_func = func();
```

一番上の変数定義以外のすべての右辺が`xvalue`

なくなりそうな値のこと  
ムーブセマンティクスの基本的な概念  

関数の返り値や左辺値を右辺値にキャストしたときなどに`xvalue`になったなどと表現される  
詳しいことは`section13_rvalue_reference.md`を参照してほしい

### `glvalue`(総合左辺値(`generalized lvalue`))

`xvalue`と`lvalue`を総合しただけ  
`xvalue`は本来右辺値であるがまぁ左辺値にも見えるだろうということでできた値

2022/02/21
written by 西永
