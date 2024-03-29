# ワイヤードOR接続  

二つのディジタル出力をまとめたいとき、一般的にはこのようにOR素子を挿入する。  
![or_example](images/or_example.png)  

でもわざわざOR素子入れるのめんどいじゃん？そうでしょ？  
というわけでOR素子を入れずに直接配線を束ねてしまうのがワイヤードORである。  

![wired_or](images/wired_or.png)  

## 注意点  

ワイヤードORするためには[オープンドレインタイプ](open_collector_drain.md)の素子を使う必要がある  
[プッシュプルタイプ](push_pull.md)のICをつかうのはご法度だ。  

というわけで問題
#### 問. なぜプッシュプル出力のICをワイヤード接続してはいけないのか。簡潔に説明せよ。  

ヒント：uartのtx同士を繋いではいけないのと同じ理由  

あと、出力インピ―ダンスが大きい（自明）ので高速信号にはあまり向いていません。寄生キャパシタンスで波形がなまってしまう可能性があります。

***
### 余談
プッシュプルタイプのICであってもダイオードを追加するだけでワイヤードORが可能になる（ダイオードORともいう）。  
どのようにダイオードを挿入すればいいか考えてみると面白いかも