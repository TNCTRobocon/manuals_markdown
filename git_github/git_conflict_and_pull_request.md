# conflict と pull request

gitignore_and_branch を見ていない人は先にそちらをみてほしい

## conflict

読めるとは思うが、一応コンフリクトと読む

### コンフリクトとは

マージをしようとしたときにコミットの変更の履歴の整合性が取れないときに発生する  
こうなるとマージができないと怒られる

### コンフリクトの解消方法

今回はmainブランチにmy/devブランチをマージしようとしてコンフリクトが発生したとする

```git
# my/devブランチに移って
git checkout my/dev

# mainブランチをmerge
git merge main
```

そうするとコンフリクトしてると出るので、コンフリクトしたファイルを参照する  
すると

```git
<<<<<<< HEAD
# 作業ブランチでの変更内容
・・・
=======
# main(マージしたブランチ)での変更内容
・・・
>>>>>>> main
```

この差分については各々で必要だと思うコードを取捨選択してほしい  

vscodeにおいてよく使うのは

- Accept Current Change : コンフリクトしたところで作業中のところを残したい時
- Accept Incoming Changes : コンフリクトしたところでマージしたところを残したい時
- Accept Both Changes : 両方残したいとき

なので参考までに

こうして変更を取り込んだらindexに追加してコミット

そしてマージすると成功する

### unrelated histries

ブランチの根本は共通してる必要がある  
gitはそうではない場合そもそもconflictすら生じさせてくれない

しかしどうしてもpullする必要がある時もある  

その時は

```git
git merge --allow-unrelated-histories target_branch
```

これでmergeできるのでconflict解消をするなりして変更の履歴にのこす

もともとのブランチが違うものの気づかずにmergeした場合、

```git
fatal:refusing to merge unrelated histories
```

と出る

## pull request

### プルリクとは

githubでマージするときに必要な工程

### プルリクの作り方

`pull request`というボタン押して、  
`new pull request` というボタンを押す

baseというところにはマージされるブランチ、  
compareというところではマージするブランチを指定する

そして`Create pull request`

するとpull requestができる

それでマージを許可したらマージされる

もしもマージができなかったらコンフリクトしている可能性があるので、ローカルでコンフリクトを解消してからもう一度pushすればマージできるようになるだろう

2021/12/29
writen by 西永
