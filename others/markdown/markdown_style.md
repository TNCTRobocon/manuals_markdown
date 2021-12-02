# markdown記法

markdownの記法まとめ

- 見出し
- リスト
- 番号付きリスト
- 改行、空行
- インライン表示
- コードの挿入
- リンクの挿入
- 引用
- テーブルの挿入
- 文字色
- 太字、斜体、打消し線
- 水平線
- 注釈
- マークダウンのエスケープ

## 見出し

- 見出し

```markdown:test
# 見出し1
## 見出し2
```

- 結果
  
# 見出し1
## 見出し2

## 番号付きリスト

- 書き方

```markdown
1. テキスト
2. テキスト
    1. テキスト
```

- 結果
  
1. テキスト
2. テキスト
    1. テキスト

## 改行、空行

- 書き方
  
```markdown
1行目__<-空白二つ
2行目  <-空白二つ
<-改行
3行目
```

- 結果

1行目  
2行目  

3行目

## インライン表示

- 書き方

```markdown
`int i = 0;`
```

- 結果

`int i = 0`

## コードの挿入

- 書き方

都合で今回は表記が異なるが許してほしい

\`\`\`c:title  
int i = 0;  
\`\`\`

- 結果

```c
int i = 0;
```

※その他言語にも対応  
シンタックスハイライトも使えるお

## リンクの挿入

- 書き方
  
```markdown
[github](https://github.com/TNCTRobocon)
```

- 結果
  
[github](https://github.com/TNCTRobocon)

## 引用

- 書き方

```markdown
>テキスト
>> テキスト
```

- 結果

>テキスト
>>テキスト

## テーブルの挿入

- 書き方

```markdown
行数x列数
↓
3x1
| 1 | 2 | 3 |
|:-:|:-:|:-:|
|   |   |   |
```

- 結果

| 1 | 2 | 3 |
|:-:|:-:|:-:|
|   |   |   |

## 文字色

- 書き方

```markdown
<font color="red">テキスト</font>
```

- 結果

<font color="red">テキスト</font>

## 太字 斜体 打消し線

- 書き方

```markdown
太字
**テキスト**

斜体
*テキスト*

打消し線
~~テキスト~~
```

- 結果

太字
**テキスト**

斜体
*テキスト*

打消し線
~~テキスト~~

## 水平線

- 書き方

```markdown
*** or ---
```

- 結果

***

## 画像の挿入

- 書き方
  
```markdown
ドラッグ&ドロップ
or
![代替文](URL or ローカルのファイル指定)
```

![豊田高専](data:image/jpeg;base64,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)

## 注釈

- 書き方

```markdown
テキスト[^1]
[^1]: 注釈内容
```

- 結果

テキスト[^1]
[^1]: 注釈内容

## マークダウンのエスケープ

- 書き方

```markdown
\`インライン表示されなくなる`
```

- 結果

\`インライン表示されなくなる`

<br><br>
2021/11/27
writen by 西永