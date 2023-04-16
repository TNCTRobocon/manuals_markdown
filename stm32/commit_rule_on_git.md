# gitを使うときに気をつけてほしいこと

`cubeIDE`や`cubeMX`のプロジェクトを`github`に`push`するときに見てほしい

最低限書いてほしい`.gitignore`を書いておいた

```.gitignore
Binary/
Includes/
Drivers/
Debug/
/*.ld/
Core/Startup/
```

>`.gitignore`とは  
`git`でステージングを無視するやつ  
わからなかったら`git_github`を参照

その他は随意追加してほしい

## cubeMXやcubeIDEで生成されるコードたち

これらのコード自動生成機能はかなりの量の自動生成コードがある
`git` で管理したり`github`などに`push`するときに自動生成コードがそのまま残っているとかなり邪魔になるので、自動生成されたコードは無視したほうがメリットがある

なので最低限これらを`.gitignore`に記述して自動生成したコードだけ無視して書いた分をより見やすくしようという話

2022/2/19
written by 西永