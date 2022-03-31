# GPIOピン

LチカでおなじみのIOピンに関する関数やマクロを紹介していく  
マイコンはstmf446reを使う

## MXでの設定

こうやって設定する 

今回はPA13を`output`、PA12を`input`に設定する

![stm32f446re6t](imgs/Screenshot%20from%202022-03-31%2022-10-47.png)

### output

PA13押して

![output1](imgs/Screenshot%20from%202022-03-31%2022-11-04.png)

こうやって出るから`GPIO_Output`押して

![output2](imgs/Screenshot%20from%202022-03-31%2022-11-10.png)

設定終わり

![output3](imgs/Screenshot%20from%202022-03-31%2022-11-18.png)

### input

PA12を押して

![input](imgs/Screenshot%20from%202022-03-31%2022-12-59.png)

![input](imgs/Screenshot%20from%202022-03-31%2022-13-05.png)

`GPIO_Input`押して終わり

![input](imgs/Screenshot%20from%202022-03-31%2022-13-17.png)

## 光らせたり消したり

早速だがLチカしよう

### `HAL_Delay`関数

一定時間待機する関数

指定時間の単位は[ms]

使い方

```c++
HAL_Delay(ms);
```

#### 実装を見てみようか

<details><summary> 少し詳しい内容になるのでみたい人のみ</summary><div>

実際に何をしているのか見てみようじゃないか  
難しいと思うなら読み飛ばしてもらって構わない

それではコピペしたものがこちら

```c++
__weak void HAL_Delay(uint32_t Delay)
{
  uint32_t tickstart = HAL_GetTick();
  uint32_t wait = Delay;

  /* Add a freq to guarantee minimum wait */
  if (wait < HAL_MAX_DELAY)
  {
    wait += (uint32_t)(uwTickFreq);
  }

  while((HAL_GetTick() - tickstart) < wait)
  {
  }
}
```

なんだこの実装となった人もいるだろう

とりあえず上から解説していこう

##### `__weak`

<details><summary> ここからそれなりに長い解説</summary><div>
マクロである

```c++
#define __weak   __attribute__((weak))
```

実装はこうなっている

`__attribute__`は関数に属性を与える効果がある

今回は`weak`属性が与えられているがどういう意味だろうか

結論から言うと弱い関数定義が行われるというもの  
別に同じ名前の関数を定義するとその定義した方が実行されるもの

例えば`hello.c`と`main.c`があったとして

```c++
//sum.h
void hello();

//sum.c
void hello(){
    printf("hello");
}

//main.c
#include"sum.h"
int main(){
    hello();
}
```

これだと出力は当然`hello`になる

ではこれはどうだろうか

```c++
//sum.h
void hello();

//sum.c
void hello(){
    printf("hello");
}

//main.c
#include"sum.h"

void hello(){
    printf("hello!!!!!!");
}

int main(){
    hello();
}
```

多重定義でコンパイルエラーだ  
これはあくまでどちらの実装を優先したいかにもよるけど今回は`main.c`の実装を優先しよう

```c++
//sum.h
void hello();

//sum.c
__atteribute__((weak)) void hello(){
    printf("hello");
}

//main.c
#include"sum.h"

void hello(){
    printf("hello!!!!!!");
}

int main(){
    hello();
}
```

これの結果は`hallo!!!!!!`だね

見事に`main.c`で定義した関数が優先されているね  
これは拡張子で気がついてる人がいるかもしれないがCでも使える機能である

ライブラリを書くときにユーザー側でも定義できるような余地を残すことができるようにできるから便利だね

他にもつけられる属性があるがそれはあとで出てきたときに別で説明しよう

あくまで`GCC`の拡張機能なので他のコンパイラなら使えなくなるので注意

</div></details>

##### `HAL_GetTick();`

なんというか名前通りな気がするけど一応

現在のタイマの値を取る

関数の定義見る？

<details><summary> 特に難しいことは書いてないはず</summary><div>

```c++
__weak uint32_t HAL_GetTick(void)
{
  return uwTick;
}
```

非常に単純な関数

さて、`uwTick`とはなんだろうか

1msごとに一回割り込まれて増えるグローバル変数

はい以上正直これ以上でもこれ以下でもない

`SysTick`で1kHz割り込まれてるとかなんとかこれ以上踏み込むのは命の危険を感じたので各々で頑張ってくれ

</div></details>

##### if (wait < HAL_MAX_DELAY)

<details><summary> これはまぁ簡単だね</summary><div>

HAL_MAX_DELAYの定義を探ると

```c++
#define HAL_MAX_DELAY      0xFFFFFFFFU
```

32bitの最大値をいれられてる  
つまり4294967296ms以上待っては行けないんですね()
ちなみに大体50日に相当する

この中の実行されるコードは

```c++
wait += (uint32_t)(uwTickFreq);
```

uwTickFreqを追っていこう

```c++
HAL_TickFreqTypeDef uwTickFreq = HAL_TICK_FREQ_DEFAULT;  /* 1KHz */

//======================
typedef enum
{
  HAL_TICK_FREQ_10HZ         = 100U,
  HAL_TICK_FREQ_100HZ        = 10U,
  HAL_TICK_FREQ_1KHZ         = 1U,
  HAL_TICK_FREQ_DEFAULT      = HAL_TICK_FREQ_1KHZ
} HAL_TickFreqTypeDef;
```

うーんこの

1じゃんけ

何らかの条件で別のものが呼ばれるのだろうか  
もしも詳しいひとがいたら教えてください

</div></details>

#####   while((HAL_GetTick() - tickstart) < wait)

中身のないwhile

指定の時間まで中身のないwhileを回し続けるのが本質だったんですね！

なんか拍子抜けした人も多いんじゃないでしょうか  
世の中そんなもんだ()

</div></details>

## マクロ

GPIOピンを設定するには切れない関係にあるやつ  

まずピンに名前をつけることができる


