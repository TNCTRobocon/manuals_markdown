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

システムコールをラップしているヘッダーファイル`<unistd.h>`の`write`を
用いて次のように記述します。

なお、一般的な環境において標準入力と標準出力、標準エラーは最初から
開かれており、そのファイル記述子の番号は既知であることから定数と
して利用できます。

```c
#include <unistd.h>

int main(int argc,char** argv){
    const char hello[] = "hello world\n";
    write(STDOUT_FILENO, hello, sizeof(hello));
    return 0;
}
```

### バッファを使った文字列の表示

先程の実装例は、マイコン環境ならUARTの送信を、Linux環境ならシステムコールを
その都度、同期的に待つ必要があり、CPUを怠けさせてしまいます。

バッファを使って効率よくまとめれて文字列を書き込む方法を習得しましょう。

### メモリー管理の補助関数

バッファを使って効率よく読み書きする前に、効率よくバッファを操作できるように
`<string.h>`の一部の関数を実装しましょう。

なお、セキュアになった関数を省略していますが、実装してみるといい練習に
なるでしょう。

* 実装例: `my_string.h`
```c
#pragma once
#ifndef __MY_STRING_HEADER_GUARD__
#define __MY_STRING_HEADER_GUARD__

#include <stddef.h>

size_t my_strlen(const char*);
// 転送系
void* my_memset(void*,int,size_t);
void* my_memcpy(void*,const void*,size_t);
char* my_strcpy(char*,const void*);
char* my_strcat(char*,const void*);

// 比較系
int my_memcmp(const void*,const void*,size_t);
int my_strcmp(const char*,const char*);

#endif /*__MY_STRING_HEADER_GUARD__*/
```

* 実装例: `my_string.c`
```c
#include "my_string.h"
size_t my_strlen(const char* s){
  // WARN: sがヌル終端文字列を終端されている保証はあるのか?
  size_t i=0;
  for (;*s!='\0';s++,i++);
  return i;
}

void* my_memset(void* _d,int _v,size_t s){
  uint8_t *d=_d;
  const uint8_t v=_v;
  for (;s>0;s--,d++){
    *d=v;
  }
  return _d;
}

void* my_memcpy(void* _dest,const void *_src,size_t sz){
  // HACK: 実はワードのアライメントを意識してワード帳と等しい長さを持つ
  // uint32_tもしくはuint64_tのポインタを利用すると高速化できる。
  // HACK: 更に高速化したい場合は、DMAの機能を用いると良い
  // (インテルのコンパイラでは自動的にmemcpyがdma転送になる)
  // WARN: sizeof(dest)>=sizeof(src)として扱っているが、本当か?
  uint8_t* dest=_dest;
  const uint8_t* src=_src;
  for (;sz>0;sz--){
    *src=*dest;
  }
  return _dest;
}

char* my_strcpy(char* d,const void* s){
  //WARN: dがstrlen(s)+1の大きさのメモリーを持つことが引数から読み取れない。
  char *r=d;
  for (;*s!='\0';s++,d++){
    *d=*s;
  }
  *d='\0';
  return r;
}

char* my_strcat(char* d,const void* s){
  //WARN: dがstrlen(d)+strlen(s)+1の大きさのメモリーを持つことが引数から読み取れない。
  char *r=d;
  for(;*d!='\0';s++);//move last of d ,無駄な箇所
  for(;*s!='\0';s++,d++){
    *d=*s;
  }
  *d='\0';

  return r;
}

int my_memcmp(const void* _a,const void* _b,size_t s){
  // HACK: 実はワードのアライメントを意識してワード帳と等しい長さを持つ
  // uint32_tもしくはuint64_tのポインタを利用すると高速化できる。
  const uint8_t *a=_a;
  const uint8_t *b=_b;
  for (;s>0;s--){
    if (a>b){
      return 1;
    }
    if (a<b){
      return -1;
    }
  }
  return 0;
}


int my_strcmp(const char*,const char*){
  //TODO: my_memcmpを参考に実装せよ
  return 0;
}

```

### バッファとフラッシュ

マイコン環境・Linux環境共にまとめて文字列を書き込むリングバッファについて
説明します。

リングバッファは、性能に制限があるマイコン環境では固定長のメモリー領域を
もつものを一般に利用し、性能に余裕がある環境では可変長のメモリー領域を持つ
データ構造です。C++が使えるリッチな環境においては、通常はstd::dequeを
利用すると良いでしょう。(C++が使えるものの、リッチではない環境では
templateを使って実装すると良いでしょう)

リングバッファは、内部的に先頭と末尾の添字を持ち、要素の追加には
先頭の添字を進ませ、要素の取り出しには末尾の添字を進ませると
いったことが行われます。

よって、リングバッファは次のような性質を持ちます。

| 操作                     | 計算量 |
| ------------------------ | ------ |
| 先頭への要素の追加・削除 | O(1)   |
| 末尾への要素の追加・削除 | O(1)   |
| 途中への要素の削除・挿入 | O(n)   |

次に実装例を示します。なお、複数の要素を書き込む・読み込む関数の実装例を
示していないので各々で実装してみてください。

実装例: リングバッファ

* `ring_buffer.h`
```c
#pragma once
#ifndef __RING_BUFFER_HEADER_GUARD__
#define __RING_BUFFER_HEADER_GUARD__
#include <stddef.h>
#include <stdint.h>

typedef struct ring_buffer{
  // これらの値は、ring_buffer_*とつく関数以外から見えないものとして扱うこと
  uint8_t *bufffer;// バッファそのものを内包しないことで汎用性を高める
  size_t in,out;
  size_t used,size;//usedは省略可能ですが、実装がめんどくなります。
}ring_buffer_t;

ring_buffer_t* ring_buffer_init(ring_buffer_t* lb, void* buffer, size_t size);
char ring_buffer_putc(ring_buffer_t* lb,uint8_t value);
char ring_buffer_getc(ring_buffer_t* lb);
size_t ring_buffer_write(ring_buffer_t* lb,const uint8_t *bytes, size_t);
size_t ring_buffer_read(ring_buffer_t* lb,uint8_t *bytes, size_t);

static inline size_t ring_buffer_used(ring_buffer_t* lb){
  return lb?lb->used:0;
}

static inline size_t ring_buffer_size(ring_buffer_t* lb){
  return lb?lb->size:0;
}

static inline void ring_buffer_clear(ring_buffer_t* lb){
  if (!lb)return;
  lb->in=lb->out=lb->used=0;
}

#endif /*__RING_BUFFER_HEADER_GUARD__*/ // 対応するペアがわからなくなるのでつけておくj
```

* `ring_buffer.c`
```c 
#include "ring_buffer.h"
ring_buffer_t* ring_buffer_init(ring_buffer_t* lb, void* buffer, size_t size){
  if (!lb)return NULL;
  if (!buffer)return NULL;

  lb->buffer =buffer;
  lb->in=lb->out-lb->used=0;
  lb->size=size;
  return lb;
}

char ring_buffer_putc(ring_buffer_t* lb,uint8_t value){
  if (!lb)return 0;
  if (lb->used +1 >= lb->size)return 0;

  lb->buffer[lb->in]=value;
  lb->in = (lb->in+1)%lb->size;
  lb->used++;
  return value;
}

char ring_buffer_getc(ring_buffer_t* lb){
  if (!lb)return 0;
  if (lb->used==0)return 0;

  const uint8_t value=lb->buffer[lb->out];
  lb->out = (lb->out+1)%lb->size;
  lb->used--;
  return value;
}

size_t ring_buffer_write(ring_buffer_t* lb,const uint8_t *bytes, size_t size){
  //TODO: 実装せよ(課題)
  return 0;
}

size_t ring_buffer_read(ring_buffer_t* lb,uint8_t *bytes, size_t){
  //TODO: 実装せよ(課題)
  return 0;
}

```

そして、リングバッファをストリームを管理するものとして抽象化してみましょう。
これを使うことで、write,read,flushがある様々なストリームをまとめて管理できます。

* `file.h`

```c
#pragma once
#ifndef __IO_HEADER_GUARD__
#define __IO_HEADER_GUARD__

#include <stddef.h>
#include <stdint.h>
#include "my_string.h"

typedef struct file{
  void *object;
  size_t (*write)(void* object, const uint8_t* bytes,size_t size);
  size_t (*read)(void* object, uint8_t* bytes,size_t size);
  void (*flush)(void *object);
}file_t;

static inline file_t file_init(file_t* fp,
  void *object,
  size_t *write(void*,const uint8_t*,size_t),
  size_t *read(void* object, uint8_t* bytes,size_t size),
  void (*flush)(void *object)){
    if (!fp)return NULL;
    fp->object=object;
    fp->write=write;
    fp->read=read;
    fp->flush=flush;
}

static inline size_t file_write(file_t* fp,const uint8_t* bytes,size_t size){
    if (!fp)return 0;
    return fp->write(fp->object,bytes,size);
}


static inline size_t file_read(file_t* fp,uint8_t* bytes,size_t size){
    if (!fp)return 0;
    return fp->write(fp->object,bytes,size);
}

static inline void file_flush(file_t* fp){
    if (fp)return;
    fp->flush(fp->object);
}

static inline char file_putc(file_t*t fp,char c){
  return fp->write(fp->object, *c,sizeof(c))>0?c:0;
}

static inline const char* file_puts(file_t fp,const char* str){
  return fp->write(fp->object, str,my_strlen(str));
}

static inline char file_getc(file_t*t fp){
  char c;
  return fp->read(fp->object,&c,sizeof(c))>0?c:0;
}

static inline char* file_gets_s(file_t fp,char* str,size_t size){
  //NOTE: getsがあまりに危ないのでセキュア版の実装例を示す。
  size_t i;
  for (i=0;i<size-1;i++){
    char c=file_getc(fp);
    if (c=='\0'||c=='\n'){
      str[i]='\0';
      return str;
    }
    str[i]=c;
  }
  str[i]='\0';
  return str;
}

#endif /*__IO_HEADER_GUARD__*/
```


つぎにリングバッファの利用例であるコンソールへの入出力をバッファする実装を
示します。

* `console_.h`

```c
#pragma once
#ifndef __CONSOLE_HEADER_GUARD__
#define __CONSOLE_HEADER_GUARD__

#endif  /*__PIPE_BUFFER__HEADER_GUARD__*/
```

TODO: バッファ内容を書き出すタイミングについて書く


### A. マイコン環境での割り込みを用いた文字列の書き出し

TODO: 書く

ヒント: 

* 私が開発したモータードライバーのコードを参考にしてください。
  + [MDU_COM](https://github.com/TNCTRobocon/MDU_COM)

### B. Linux環境での方法

TODO: 書く
