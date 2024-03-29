<<<<<<< HEAD
# プルアップ・プルダウン抵抗
## 基本
　プルアップ抵抗やプルダウン抵抗はセンサーやスイッチの入力によく用いられる抵抗の挿入形式です。

![プルアップ&プルダウン](images/pull_up_down.png)

　図のように抵抗をスイッチのハイサイド側に設置したものをプルアップ抵抗、ローサイド側に設置したものがプルダウン抵抗といいます。

　プルアップ抵抗を挿入することで入力がハイインピーダンス状態になることを避けることができます。入力がハイインピーダンス状態だと状態が不定となってしまいノイズ耐性の低下など様々な不都合が発生する可能性があります。

　プルアップ・プルダウン抵抗が大きいと、消費電力は下がりますがノイズ耐性が劣化します。逆に、小さいとノイズ耐性は上がりますが消費電力は大きくなります。

## 備考
- スイッチの入力などに挿入する抵抗は10kΩ程度のものがよく用いられます。
- I²Cの信号線にはプルアップ抵抗を入れましょう。
- UARTなど、規格上はプルアップ抵抗の必要ない通信線にもプルアップ抵抗を入れることによってノイズ耐性の向上が期待できます。
=======
# プルアップ・プルダウン抵抗
## 基本
　プルアップ抵抗やプルダウン抵抗はセンサーやスイッチの入力によく用いられる抵抗の挿入形式です。

![プルアップ&プルダウン](images/pull_up_down.png)

　図のように抵抗をスイッチのハイサイド側に設置したものをプルアップ抵抗、ローサイド側に設置したものがプルダウン抵抗といいます。  
　プルアップ抵抗を挿入することで入力がハイインピーダンス状態になることを避けることができます。入力がハイインピーダンス状態だと状態が不定となってしまい、ノイズ耐性の低下など様々な不都合が発生する可能性があります。  

　プルアップ・プルダウン抵抗が大きいと、消費電力は下がりますがノイズ耐性が劣化します。逆に、小さいとノイズ耐性は上がりますが消費電力は大きくなります。

## 備考
- スイッチの入力などに挿入する抵抗は10kΩ程度のものがよく用いられます。
- **I²Cの信号線にはプルアップ抵抗を入れましょう。**[詳細はこっち](../micro_controller/I2C_introduction.md)
- UARTなど、規格上はプルアップ抵抗の必要ない通信線にもプルアップ抵抗を入れることによってノイズ耐性の向上が期待できます。
>>>>>>> ce5bb3aad07fe4a467d06ca857955e44822ee883
- 最近のマイコンだとマイコン内部にプルアップ抵抗が内蔵されているものもあります。部品点数を削減することができるので積極的に活用しましょう。