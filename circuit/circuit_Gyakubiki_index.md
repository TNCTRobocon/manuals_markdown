# 回路逆引き目次  

「回路動きそう？」  
  回路製作が上手くいっていない時に制御班から稀によく言われるこの言葉の持つメンタル破壊力の底知れなさを、回路班員の多くが実感した経験があることでしょう。回路が動かないというのは回路班員に掛かるストレスランキング万年一位ですし、それが頑張って設計製作したものであった時の精神的ダメージは計り知れません。  
  回路は設計した通りではなく作った通りに動きます。あなたがどれだけ頑張って設計した回路も、重大なミスが一つでもあれば、それはただの産業廃棄物です。ゴミです。ええ。  
というわけで本稿ではよくある設計ミスや設計の際のヒントになりそうなことを逆引き辞書的に書いていこうと思います。


## マイコン関係  

### なんかマイコンの電源が入らない  

- マイコンのリセットピンはプルアップされていますか？ほとんどの場合プルアップしてあげないと動きません  

### nucleo等のマイコンボードで特定のピンから信号が出ない

- そのピンはマイコンボード上でどこか他の素子（水晶など）につながっていませんか？つながっているとたとえその素子を使用していなくても上手く信号が取り出せない場合があります。

### arduino等のマイコンボードでシリアル通信ができない

- そのシリアルポートはUSBにシリアル変換器を介して繋がっているような物ではないですか？マイコンボードをパソコンと接続している場合、USB側とも繋がっているポートは使用できないことがあります。

### 3.3V電源のマイコンと5V電源のマイコンをつなげたい  

- 基本的にはレベル変換回路を使用しましょう
- 5V側から3.3V側につなげるのであれば、ツェナーや分圧などで降圧してあげるのもいいかもしれません  


## 通信関係  

### なんか良くわからんけど通信エラーが頻発するor動かない

- **I2C通信の場合**  
  プルアップ抵抗は入れてありますか？I2Cが動かないと喚き散らした結果、原因がプルアップ忘れだったときの恥ずかしさはたとえようがありません。気をつけましょう。  
  また、I2Cの通信線が長すぎたりはしませんか？基本的にI2Cはノイズ耐性がクソザコなので基板外へ取り出すときなども十分注意しましょう。

- **UART等非同期通信の場合**  
  マイコンのクロック源の精度はどのくらいですか？クロックの精度が低い場合、非同期通信ではエラーの原因になりがちです。内蔵クロックは極力使用せず、水晶発振器などを使用しましょう。  

- **SPI,I2Cなどの同期通信やCANなどの差動通信の場合**  
  それぞれの通信線の長さに差がありますか？電気信号が伝わる速さは有限なので、配線長に差があると信号が届くタイミングに差が出てしまい、エラーの原因になります。できる限り同じ長さになるように配線しましょう。  

## PCBパターン設計
## センサー関係  

## モータードライバ、電力関係