# オペアンプの使用例  

オペアンプはアナログ回路においては一番と言っていいぐらい重要で便利な素子です。是非使いこなせるようになりましょう。  

## そもそもオペアンプって何ぞや  
オペアンプは下図のような回路図記号で表される回路部品です。  
![opamp_symbol](images/op-amp_symbol.png)  
オペアンプは**非反転入力**（図の3番ピン）、**反転入力**（図の2番ピン）、**出力**（図の1番ピン）の3つのピンからなる部品です。  
~~電源がないジャマイカ？？省略されているだけです。~~  
ではこの部品はどのような動作をするのでしょうか。  答えは簡単、反転入力と非反転入力の間の電位差を増幅するだけです。  

式で表すとこんな感じ。  

<img src="https://latex.codecogs.com/svg.image?V_{out}=A(V_{IN&plus;}-V_{IN-})" />  

なお、  

- <img src="https://latex.codecogs.com/svg.image?V_{IN&plus;}" /> : 非反転入力の電位
- <img src="https://latex.codecogs.com/svg.image?V_{IN-}" /> : 反転入力の電位
- <img src="https://latex.codecogs.com/svg.image?A" /> : オープンループゲイン（理想的には無限大）  

です。  

簡単ですね。でもこれだとただのコンパレータと何が違うんやんけってなると思います。  
オペアンプの真髄は**負帰還**をかけられる、という点にあります。  
つまり出力された信号からフィートバック回路を通して入力に様々なゲインをかけられますよ。っていうことです。  

### イマジナリーショート（仮想短絡）[^1]  
イマジナリーショートはオペアンプの働きを説明する上で最も良く用いられる考え方で、**オペアンプは非反転入力と反転入力の間の電位差が0になるような電圧を出力する**という考え方です。  

………良くわかりませんね。具体例で考えてみましょう。  

次のような回路を考えます。  
![non-inv-amp](images/non-inv_amp.png)  
オペアンプの出力がR1とR2によって分圧されて反転入力端子に入っていますね。  
ではまず、この回路において<img src="https://latex.codecogs.com/svg.image?V_{IN-}"/>はどのような電圧になるのでしょうか。分圧則より  

<img src="https://latex.codecogs.com/svg.image?V_{IN-}&space;=&space;\frac{R_{2}}{R_{1}&plus;R_{2}}V_{OUT}" />  

となりますね。  
さて、ここで非反転入力端子に<img src="https://latex.codecogs.com/svg.image?V_{IN&plus;}" />が入力されているとします。<img src="https://latex.codecogs.com/svg.image?V_{OUT}"/>はどんな電圧になるでしょうか。  
ここで、先ほど述べたイマジナリーショートの**非反転入力と反転入力の電位が同じになるようになる**という考えを持ってきます。  
つまり<img src="https://latex.codecogs.com/svg.image?V_{IN&plus;}=V_{IN-}" />になるということですね。  
で、<img src="https://latex.codecogs.com/svg.image?V_{IN-}"/>は先ほどすでに求めたので、代入してみると  

<img src="https://latex.codecogs.com/svg.image?V_{IN&plus;}&space;=&space;\frac{R_{2}}{R_{1}&plus;R_{2}}V_{OUT}" />  

整理して

<img src="https://latex.codecogs.com/svg.image?V_{OUT}&space;=&space;(1&plus;\frac{R_{1}}{R_{2}})V_{IN&plus;}" />

となります。なんとなく分かったでしょうか。こんな具合にオペアンプは負帰還とイマジナリーショートによって入力を増幅することができます。

## よくある回路例  

オペアンプを活用するありがちな回路を紹介していきます。

### 非反転増幅回路  

![non-inv-amp](images/non-inv_amp.png)  

<img src="https://latex.codecogs.com/svg.image?V_{OUT}&space;=&space;(1&plus;\frac{R_{1}}{R_{2}})V_{IN}" />  

さっき上で紹介した回路ですね。微小な電圧を増幅する時にどうぞ。

### 反転増幅回路  

![inv-amp](images/inv_amp.png)   

<img src="https://latex.codecogs.com/svg.image?V_{OUT}&space;=&space;-\frac{R_{2}}{R_{1}}V_{IN}" />  

今度は出力が反転する回路です。正負電源を使っていないと負電圧は当然出力できないので気を付けましょう。

### ボルテージフォロワ  

![voltage_follower](images/voltage_follower.png)  

<img src="https://latex.codecogs.com/svg.image?V_{out}=V_{IN}" />

ボルテージフォロワは入力電圧をそのまま出力する回路です。意味ないやんけって思われるかもしれませんが、オペアンプの入力インピーダンスは非常に高いため、高インピーダンスな電圧源（＝あまり電流を出力できないセンサーとか）をマイコンなど他の機器に接続する時などに間に挟んだりします。

### 差動増幅回路  

![difference_amp](images/difference_amp.png)  

<img src="https://latex.codecogs.com/svg.image?V_{OUT}&space;=&space;\frac{R_{1}&plus;R_{2}}{R_{1}}\frac{R_{4}}{R_{3}&plus;R_{4}}V_{IN&plus;}-\frac{R_{2}}{R_{1}}V_{IN-}" />  


んー長い。というわけで<img src="https://latex.codecogs.com/svg.image?R_{1}&space;=&space;R_{3},R_{2}&space;=&space;R_{4}" />としまして  

<img src="https://latex.codecogs.com/svg.image?V_{out}=\frac{R_{2}}{R_{1}}(V_{IN&plus;}-V_{IN-})" />

こちらは二つの入力電圧の差を増幅する回路です。シャント抵抗などを使用するハイサイド電流アンプや、コモンモードノイズが発生するような状況で使用できます。

### 積分回路  

![integral_circuit](images/integral_circuit.png)  

<img src="https://latex.codecogs.com/svg.image?V_{OUT}&space;=&space;-\frac{1}{RC}\int&space;V_{IN}dt" />  

入力を積分して反転出力する回路です。  

ちなみに非反転型もあります。  
![non_inv_integral](images/non_inv_integral.png)  
抵抗とコンデンサはそれぞれ同じ物を使用しましょう。  

### 微分回路  

![differential_circuit](images/differential_circuit.png)  

<img src="https://latex.codecogs.com/svg.image?V_{OUT}&space;=&space;-RC\frac{dV_{IN}}{dt}" />  

入力を微分して反転出力する回路です。  

### 加算回路  

![adder](images/adder.png)  
<img src="https://latex.codecogs.com/svg.image?R_{1}=R_{2}=R_{3}=R_{4}=...=R_{N}" />として、

<img src="https://latex.codecogs.com/svg.image?V_{OUT}&space;=&space;\frac{R/(N-1)}{R&plus;R/(N-1)}(V_{in1}&plus;V_{in2}&plus;V_{in3}&plus;V_{in4}&plus;...&plus;V_{inN})" />  

## ちょこっと応用

オペアンプのイマジナリーショートを便利に使っていきましょう。  

### リニアレギュレータ（3端子レギュレータ）  

![liner_regulator](images/liner_regulator.png)  
おなじみ3端子レギュレータもオペアンプを使うことで実現することができます。  
オペアンプの非反転入力には出力電圧が入ってきますが、オペアンプがその電圧がVrefと同じになるように制御してくれます。  
まあもちろんこのままでは直ぐに発振してしまうので出力の電源ラインにコンデンサを挿入して発振を防止する必要があります。  

### 電子負荷  

![electronic_load](images/electronic_load.png)  
これはあまりロボコンではなじみはないかもしれませんが、電源の試験などに良く用いられる電子負荷と呼ばれる回路です。  
電子負荷の反転入力には流れている電流に比例した電圧が入力されるので、VCCの値が変動してもMOSFETには常に同じ電流を流すように制御できます。

[^1]:イマジナルショートとも言います。が、個人的にイマジナリーの方がカッコいい気がしたのでイマジナリーで行きます。