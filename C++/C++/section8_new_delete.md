# メモリの動的確保

`malloc`とは違うメモリ確保方法

## new演算子

簡単に確保できるようになったメモリ  
特にファイルをインクルードする必要はない

```C++
int buf = 100;

int nums[buf];//error

int *nums = new int[buf];//これでメモリを確保

delete[] nums;//メモリの解放
```

このように簡単にメモリを確保することができる

new演算子で帰ってくるのはポインタ型なので受け取り側を変数にする必要がある

## delete演算子

`new`で確保したメモリを解放するためのもの

`new`で確保したメモリは必ず`delete`で返さなくてはならない

>mallocと同じくプログラムが終了したときにメモリを解放するので短いプログラムであればdeleteする必要はない  
当然メモリは解放した方がいいのでするべき

## 動的メモリを返す関数

```C++
int*create_array(int size, int n = 0){
    int *arr = new int[size];

    for(int i = 0; i < size; i++){
        arr[i] = n;
    }

    return arr;
}

int main(){
    int*num = create_array(100, 1);

    //コード

    delete[] num;
}
```

関数内で配列を宣言したときは関数が抜けた時に関数内で配列の寿命も尽きるが、`new`を使った場合は勝手に消去されないので残り続ける

関数が終わった後もアクセス可能であるという点はあるがメモリの管理をしなければならないという点で非常にめんどくさい

## 注意点

`new`や`delete`はほぼほぼ`malloc`や`free`の代用として利用できる  
しかし、`malloc`との互換性があるわけではない  
`new`で確保したメモリは`free()`で解放できないし、`malloc`で確保したメモリは`delete`で解放もできない

作法として`delete`や`free`を行ったら速やかにポインタに`nullptr`を代入する

2021/12/15  
written by 西永
