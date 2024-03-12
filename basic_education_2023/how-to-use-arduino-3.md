# Arduinoを使ってみよう！ (その3)

## もくじ
* 1.Arduino IDEの起動と画面の説明 //[リンク](how-to-use-arduino-1.md)
* 2.Arduinoを使ってLチカをしてみよう！ //[リンク](how-to-use-arduino-2.md)  
* 3.Arduinoを使ってPWMを体験してみよう！　//今回はこれ  
* 4.Arduinoを使ってデジタル入力を体験してみよう！ //[リンク](how-to-use-arduino-4.md)  
* 5.Arduinoを使って自由に明るさを変えてみよう！（上級編） //[リンク](how-to-use-arduino-5.md)  

## 3.Arduinoを使ってPWMを体験してみよう！
さて、前回はArduinoを使って、LEDをチカチカさせた。  
この時LEDには、HIGH or LOW (1 か 0)のどちらかで光ってもらった。  
しかし、これでは明るさを変えることができない。 このままでは明るすぎて困ってしまうだろう...  
~~(抵抗変えればよくね？)~~  
...ということで、今回はPWMの仕組みを使って簡単だが、LEDの明るさを操ってみよう。

### 3-1 そもそも、PWMって？
端的に言うと、 ON と OFF を高速で繰り返すことで、出力される電気を調節する仕組みのこと。  
（詳しく知りたいのなら、調べてみるとよい。）  
PWMは、モーターなどの制御にもよくかかわってくるので、使えるようになっておこう。  

### 3-2 回路を作ろう！
...前回の回路は残っているだろうか。 今回もそれを用いる。  
しかし、Arduinoで、PWMを出力できるピンは限られている。 そのため、「Arduino ○○ PWM出力ピン」 などで、調べてみてほしい。  
（Arduinoに PWMと書いてあることもあるので、Arduinoをまずは見てみよう。）  
そこのピンに前回の回路の ＋ 側がつながるようにしよう。  
//写真のせたい。

### 3-3 プログラムを書こう！
...こちらも前回のプログラムを流用していく。  
前回のプログラムはこれ、  
```cpp
//出力を11番ピン, 間隔を100ミリ秒にした例
void setup(){
  pinMode(11, OUTPUT); //ピンの初期設定
}
  
void loop(){
  digitalWrite(11, HIGH); //11番ピンから電流を流す
  delay(100);             //100ms待つ
  digitalWrite(11, LOW);  //11番ピンからの電流を止める
  delay(100);             //100ms待つ
}
```

では、ここで今回新しく使用する関数を紹介する。  
```cpp
analogWrite(pin, value);
```  
この関数を使うとPWMを使うことができる。  
```pin```にはピン番号を、 ```value```にはデューティ比というものを入れるが、今回は電気の強さだと思ってくれていい。  
```value```の範囲は 0 ~ 255 だ。   

...今まで紹介したものと、これだけで今回のプログラムは書ける。  

ということで、早速だが前回のプログラムを参考にして、時間経過で、LEDの明るさが変化するプログラムを書いてみよう。  
前回のものを書き換えるだけでいい。  終わったら前回と同じようにArduinoに書きこんで、実行してみよう。 できたら、答えのプログラムを見てみてほしい。  

<details> <summary>答えのプログラム例</summary><div>
  
```cpp
//出力を11番ピン, 間隔を100ミリ秒にした例
void setup(){
  pinMode(11, OUTPUT); //ピンの初期設定 //analogWriteでは必ずしも必要ない(後述)
}
  
void loop(){
  analogWrite(11, 255); //11番ピンから 255(最大)
  delay(100);             //100ms待つ
  analogWrite(11, 150);  //11番ピンから 150
  delay(100);             //100ms待つ
}
```

こちらも必ずしも解答通りではなくてもよい。 期待通りに、LEDの明るさが変化したら正解だ。
<br>
ちなみに、```analogWrite();```では、 ```setup()```で、```pinMode();```を実行する必要はない。
<br>
しかし、これがあるとプログラムを読んだときにどのピンから出力されているか、わかりやすくなる。 プログラムを書くときは、読みやすく書くことを心掛けてほしい。
</div> </details>

さて、ここまでやってみてどうだろうか。うまくいっているだろうか。  
エラーが起きたら、先輩に聞くのもよいが、自分で原因を探してみるのもよいだろう。  
大体のことは今回や前回を読んでみると、解決できると思う。  

さて、できたら次の 4.Arduinoを使ってデジタル入力を体験してみよう！ に進もう。
次は[こちら](how-to-use-arduino-4.md)  
written by つつさん 2023/03/31  

<details> <summary>おまけ: 明るくなったり暗くなったりするプログラム</summary>
<div>  
  
```cpp
//出力を11番ピンにした例
void setup(){
  pinMode(11, OUTPUT);
}
  
void loop(){
  //for文: 繰り返しの処理ができる。
  for(int i = 0; i < 255; i++){ 
    analogWrite(11, i);
    delay(100);
  }

  for(int i = 255; i > 0; i--){
    analogWrite(11, i);
    delay(50);
  }
}
```
</div>
ここで使われているfor文などについては、後に学習するので、今は気にしなくてもよい。  
<br>
ただ、このようなプログラムで、LEDがどのように光るか見てみるとよい。
</details>