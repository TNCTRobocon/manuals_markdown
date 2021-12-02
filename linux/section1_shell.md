# シェル

## ターミナルとは

ターミナルは、ユーザーとの入出力をシェルに渡すアプリケーションである。

NOTE: まあ、一般に使われているGUIで動くターミナルは、ターミナルを模したもので
あることから仮想ターミナルと言われます。

## シェルとは

文字の入出力ができるターミナルを介してOSの機能を呼び出す対話的インタープリターの
一種である。代表的なものとして、sh, bash,zsh,fish,csh,ashがある。

# 標準入力と標準出力、標準エラー

入出力を指定せずにプログラムを実行する場合、ターミナルからの入力が入る
標準入力(`/dev/stdin`)とターミナルへの出力を行う標準出力(`/dev/stdout`)と
標準エラー(`/dev/stderr`)のファイルディスクリプタが渡させる。

```sh
echo hello world
# hello world
seq 5
# 1 2 3 4 5
```

NOTE: seqは順番に並んだ整数を出力するコマンド

しかし、パイプと言われる機能を用いることで入出力を切り替えることができる。

```sh
echo hello | rev
# olleh
```

NOTE: revは文字を逆順にするコマンド

この例では、echoから出力されたhelloを、revが入力として受け取り、ひっくり返して
出力している。

プログラム無しで関数型言語のようにコマンドをフィルタとして用いることで、
1から10のうち、偶数の総和を求めることもできる。

```sh
seq 10 | awk '($1 %2 ==0){print $1}' | awk '{s+=$1} END{print s}'
# 30
```

NOTE: awkは、条件にあった文字を加工して表示するコマンド

また、出力された文字をファイルに保存することもできる。

```sh
echo "hello" > hello.txt
# 新規保存
cat hello.txt
# hello
echo "world" >> hello.txt
# 上書き保存
cat hello.txt
# hello world

echo "bye" > hello.txt
cat hello.txt
# bye
```

そして、表示を消すこともできる。

```sh
echo "hoge" > /dev/null
```

## 変数

シェルでももちろん変数を扱うことができる。ただし、通常の言語と異なり=の間に空白を
入れていけないことに注意が必要だ。

```sh
x=10
y=a
z = a # NG
```

そして、変数の値を使うときは$演算をつけると利用できる。また、変数の値を
展開したくないときは`'`で囲う。

```sh
hello='hola'
echo $hello
# hola
echo "$hello mundo"
# hola mundo
echo '$hello mundo'
# $hello mundo
```

NOTE: hola = hello, mundo = worldなのでスペイン語版hello worldでした。

## 条件分岐

プログラムといったらif文のイメージがあるが、当然シェルでもif文を
使うことができる。なお、若干直感に反するが、戻り値が0のときが成功とみなされる。

```sh
command=true #false
if $command;then
  echo true
else
  echo false
fi
```

NOTE: trueは常に成功するコマンド
NOTE: falseは常に失敗するコマンド

`&&`と`||`を使えばシェルではもっと簡単に書くことができる。これらの演算子は、
C言語同様に短絡評価されるのだ。

```sh
true && echo a
# a
false && echo a
# (何も表示されない)
false || echo a
# a
true || echo a
# (何も表示されない)
```

もちろん、for文やwhile文のお手のものだ。

```sh
for index in `seq 10`;do
  echo $index
done
# 1から10が表示される

seq 10 | while read index;do
  echo $index
done
# 1から10が表示される
```

---
2021/12/3  
writen by てるりん
