# 左辺値と右辺値

## 意味

**左辺値**(lvalue)とは変数に代入されている値  
**右辺値**(rvalue)は変数に代入する前の定義や計算結果。何もしなければ消えて使えなくなってしまう

実際に例を見てみよう

```c++
int n = 1;//nは左辺値、1は右辺値
int m = n + 1;//mが左辺値、n + 1 は右辺値、nは左辺値
int l = func(m + 2);//lは左辺値、func関数の戻り値は右辺値、m + 2は右辺値

1;//1は右辺値
```

このような意味である

### もっと詳しく

左辺値、右辺値をlvalue, rvalueとあらわすことにしてさらに細かく分類するとこうなる

- lvalue(左辺値)
- rvalue(右辺値)
- prvalue
- xvalue
- glvalue

それぞれ見ていこう

#### lvalue

左辺値のこと  
ここは省略する

#### rvalue

右辺値のこと  
prvalueとxvalueに分類できる  
ここも省略する

#### prvalue

pure rvalue(純粋右辺値)
リテラルや参照を返す関数を除く関数の戻り値がここに分類される

#### xvalue

expiring value(死にかけの値)という意味  
使えなくなる値
std::moveを使った時などに役に立つ

#### glvalue

general lvalue(総合左辺値)  
lvalueとxvalueの総称  
さっきxvalueは右辺値といったが本質的には左辺値に分類されるので総称してglvalueという

## 左辺値参照と右辺値参照

左辺値参照とは左辺値を束縛すること、またはその参照変数  
右辺値参照は右辺値を束縛すること、またはその参照変数

>束縛とは:  
対象を=で代入、もしくは実引数にする形で参照変数に関連付けること

```c++
  //[]は束縛対象（参照元）
  //<>はコピーされた値
  int x=1;//xは左辺値<1> 1は右辺値
  int& lref = x;//lrefが左辺値参照[x] xは左辺値
  int& lref2 = lref;//lref2が左辺値参照[x] lrefは左辺値参照[x]
  int& lref3 = 1;//エラー　lref3が左辺値参照 1は右辺値
  int y = lref;//yが左辺値<xの値> lrefは左辺値参照[x]

  int&& rref = 1;//rrefが右辺値参照[1] 1は右辺値
  int&& rref2 = x; //エラー　rref2が右辺値参照 xは左辺値
  int&& rref3 = lref; //エラー　rref3が右辺値参照 lrefは左辺値参照
  int&& rref4 = rref; //エラー　rref4が右辺値参照 rrefは右辺値参照
  int&& rrefm = std::move(lref);  //rrefmが右辺値参照      std::moveは後で解説
  int w = rref; //wが左辺値<1> rrefは右辺値参照[1]
```

section 3で紹介した参照は左辺値参照である

`int&&`と書かれているところは**右辺値参照**という
