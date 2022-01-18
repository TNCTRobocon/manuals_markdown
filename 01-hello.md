# あらすじ

## 序章

あなたは、未知の星(環境)を開拓(開発)するエンジニアです。
不慮の事故により、未開の星(環境)に不時着(アサインされて)して
しまいました。しかし、あなたは、この未開の星(環境)を整えて、
ロケット(成果物)を打ち上げなくてはいけません。

> まあ、Factorio的な世界観です。
> あと、茶番は読み飛ばしてもらって構いません。

## 真っ暗闇の中で

あなたは未開の星(環境)がどうなっているのか調べなくてはいけません。
そのためには、まず明かり(デバック環境)を用意しましょう。

# 演習

本演習は、今後の前提となる文字の出力関数を実装します。
なお、開発環境ごとに手順がことなるため、適時読み替えて実装してください。

## バッファーを使わない文字列の表示

バッファを使わずに文字列を表示してみましょう。

### A.マイコン環境

マイコン環境において最初にするべきことは次の手順です。

1. LEDを光らせる
2. UARTでなんからの文字を出力する
3. UARTでなんからの文字列を出力する

今回に関しては、擬似コードでしか説明できないため、擬似コードを
用いて説明していきます。

#### 1.LEDを光らせる

次のようなコードを記述します。

1. クロックを設定する
   + PLLを有効にする必要がある場合はPLLをロックする
2. GPIOを初期化する
   + 入出力方法を設定する
   + 他の機能を無効化する(例: ADC)
3. LEDを反転させる
4. 一定時間時間待つ
   + 最初は何もしないfor文を回すといいでしょう
5. 3に戻る

```c
#define LED //TODO: 設定すること

void main(){
  init();
  while(1){
    LED=!LED;
    delay(1000);//適当
  }
}

void init(){
  clock_init();
  gpio_init();
}
```

ヒント: 

* オシロスコープを持っている場合、意図した周波数になっているか
  確認するといいでしょう
* コンパイラの最適化を防ぐために、`volatile`を利用するといいでしょう

TODO: STM32環境向けのサンプルコードを書く

#### 2. UARTで文字を出力する

次のようなコードを記述します。

1. クロックを設定する
   + PLLを有効にする必要がある場合はPLLをロックする
2. GPIOを初期化する
   + 入出力方法を設定する
   + 他の機能を無効化する(例: ADC)
3. UARTを初期化する
4. TXREGのBUSYフラグが消えるまで待機する
5. TXREGになんからの文字を書きこむ。
6. 4に戻る

```c
#define TXREG //TODO: 設定すること
#define TXBUSY //TODO: 設定すること

void main(){
  init();
  while(1){
    uart_putc('a');//適当
  }
}

void init(){
  clock_init();
  gpio_init();
  uart_init();//115200bps
}

void uart_putc(char c){
  while(TXBUSY);
  TXREG=c;
}
```

#### 3. UARTで文字列を出力する

2とあまり変わりませんが、次のようなコードを記述します。

1. クロックを設定する
   + PLLを有効にする必要がある場合はPLLをロックする
2. GPIOを初期化する
   + 入出力方法を設定する
   + 他の機能を無効化する(例: ADC)
3. UARTを初期化する
4. 文字列の先頭から最後までの文字cを取得する。
   1. TXREGにcを書きこむ。
   2. TXREGのBUSYフラグが消えるまで待機する
5. 4に戻る

```c
#define TXREG //TODO: 設定すること
#define TXBUSY //TODO: 設定すること

void main(){
  init();
  while(1){
    uart_puts("hello planet\n");//適当
  }
}

void init(){
  clock_init();
  gpio_init();
  uart_init();//115200bps
}

void uart_puts(const char* s){
  for(;*s!='\0';s++){
    uart_putc(*s);
  }
}

void uart_putc(char c){
  while(TXBUSY);
  TXREG=c;
}

```

### B.Linux環境

システムコールを使って文字列を表示してみましょう。

#### 1.標準入出力とデバイスファイル

Unix/Linuxにおいて、ほとんどの要素[^1]はファイルとして抽象化されています。
もちろん、標準入力(`/dev/stdin`)と標準出力(`/dev/stdout`)、
標準エラー(`/dev/stderr`)もデバイスファイルとして見ることができます。

シェルを使って振る舞いを確認してみましょう。

```sh
$ echo "hello" | cat /dev/stdin # デバイスファイルから文字列を読み込んでいる
hello
$ echo "hello" > /dev/stdout # デバイスファイルに文字列を書き込んでいる
hello
$ echo "hello" > /dev/stderr # デバイスファイルに文字列を書き込んでいる
hello
```

[^1] デバイスファイルの設定等は抽象されていません。例えば、UART(`/dev/tty??`)の
通信を速度を示すプロパティはファイルとして抽象化されておらず。ioctlを介して
設定を行います。

#### 2. 標準的な方法

一般的にC言語では文字列を表示する場合、`libc`の含まれている`printf`や`puts`と
いった関数を使います。これらの関数を呼び出すとどのように文字列が
表示されるのでしょうか。

アプリケーションが`puts`を呼び出すと静的リンクされているlibcの`putc`が
呼び出され、システムコール`write`を呼び出します。すると、システムコールを
受け取ったLinuxがデバイスファイルへデータを渡して文字列の表示が行われます。

> 後半をぼかして書いたのは、動作環境により振る舞いが変化するからです。例えば、
> 仮想ターミナルなら仮想ターミナルへ、SSH接続としているならSSHへ、
> シリアル通信をしている場合はシリアルデバイスへと変化してしまいます。

#### 3. システムコールを使ってみよう。

TODO: 書く

### バッファを使った文字列の表示

先程の実装例は、マイコン環境ならUARTの送信を、Linux環境ならシステムコールを
その都度、同期的に待つ必要があり、CPUを怠けさせてしまいます。

バッファを使って効率よくまとめれて文字列を書き込む方法を習得しましょう。

### バッファとフラッシュ

マイコン環境・Linux環境共にまとめて文字列を書き込むリングバッファについて
説明します。

TODO: 振る舞いについて書く

実装例: 

```c
#include <stddef.h>
#include <stdint.h>

typedef struct ling_buffer{
  // これらの値は、ling_buffer_*とつく関数以外から見えないものとして扱うこと
  uint8_t *bufffer;// バッファそのものを内包しないことで汎用性を高める
  size_t in,out;
  size_t used,size;//usedは省略可能ですが、実装がめんどくなります。
}ling_buffer_t;

ling_buffer_t* ling_buffer_init(ling_buffer_t* lb, void* buffer, size_t size){
  if (!lb)return NULL;
  if (!buffer)return NULL;

  lb->buffer =buffer;
  lb->in=lb->out-lb->used=0;
  lb->size=size;
  return lb;
}

char ling_buffer_putc(ling_buffer_t* lb,uint8_t value){
  if (!lb)return 0;
  if (lb->used +1 >= lb->size)return 0;

  lb->buffer[lb->in]=value;
  lb->in = (lb->in+1)%lb->size;
  lb->used++;
  return value;
}

char ling_buffer_getc(ling_buffer_t* lb){
  if (!lb)return 0;
  if (lb->used==0)return 0;

  const uint8_t value=lb->buffer[lb->out];
  lb->out = (lb->out+1)%lb->size;
  lb->used--;
  return value;
}

size_t ling_buffer_used(ling_buffer_t* lb){
  return lb?lb->used:0;
}

size_t ling_buffer_size(ling_buffer_t* lb){
  return lb?lb->size:0;
}

void ling_buffer_clear(ling_buffer_t* lb){
  if (!lb)return;

  lb->in=lb->out=lb->used=0;
}

```

TODO: バッファ内容を書き出すタイミングについて書く

TODO: リングバッファもread,write,flushをもつファイルの一種なのではと気づかせること

### A. マイコン環境での割り込みを用いた文字列の書き出し

TODO: 書く

ヒント: 

* 私が開発したモータードライバーのコードを参考にしてください。
  + [MDU_COM](https://github.com/TNCTRobocon/MDU_COM)

### B. Linux環境での方法

TODO: 書く
