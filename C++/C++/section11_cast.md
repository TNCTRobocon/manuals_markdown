# キャスト

新しいキャスト構文

- static_cast
- const_cast
- reinterpret_cast
- dynamic_cast

の4つ

**キャスト構文<変換先の型>(変換したい値)**で行う

## static_cast

一般型のデータ型のキャスト

```C++
int num_i;
double num_d = 10.22;

num_i = static_cast<int>(num_d);
```

※従来のキャスト

```C++
int num_i = 10;
double num_d;

num_i = (int)num_d;
```

### ポインタの変換

```C++
int num = 10;
int *p = &num;

float*fp = static_cast<float*>(static_cast<void*>(p));
```

このようにポインタをキャストする場合は`void*`を経由しなければならない

C++11以降では後述する`reinterpret_cast`では`void*`を経由することなく直接変換できる

## const_cast

ポインタや参照の`const`を外すキャスト  
`const`は基本的に理由があって付けられているものなのでむやみに使わない方がいい

`const`以外にも`volatile`修飾子も外す

```C++
int num = 10;
const int*p1 = &num;

int*p2 = const_cast<int*>(p1);

*p1 = 0;//error
*p2 = 0;//ok
```

## reinterpret_cast

reinterpret → 再解釈

データ型に手を加えることなくそのままべつの型として解釈するキャスト

bit表現を変えずに表現する  
例えばint型の10とfloat型の10.0fはキャストするときに内部でのビットの表記が変わるが、これはそういった加工をしないキャスト

```C++
int num = 10;
int*ip;
float*fp;

ip = &num;

fp = reinterpret_cast<float*>(ip);
```

## dynamc_cast

### アップキャストとダウンキャスト

派生クラスのインスタンスを基底クラスとして扱うことは特別な構文を使用することなく使用できる

```C++
class base{

};

class derivide : public base{

};

int main(){
    base*b = new derived();

    delete b;
}
```

このような変換を**アップキャスト**という

基底クラスと派生クラスの流れを流れと考え、基底クラスを上流、派生クラスを下流と考えると下から上のキャストなのでアップキャストという  
派生クラスは基底クラスの情報を含むので安全に利用できる

問題は次に説明するダウンキャストである

```C++
class base{

};

class derived : public base{
public:
    int num;
};

int main(){
    base*b = new base();
    derived*d = static_cast<derived>(b);

    d->num;//存在しないメンバへのアクセス
}
```

基底クラスのインスタンスで派生クラスにキャストすると存在しない変数にアクセスすることになるので意図した動作にならない

### dynamicにcast

ダウンキャストを使うことはあまりないが、した方が都合が良い場合が存在する

ダウンキャストはアップキャストとセットで使うのが一般的である

```C++
#include<vector>

class base{

};

class derived_a{
    int a;
public:
    void setter(int _a){//隠蔽されなくなる
        a = _a;
    }
};

class derived_b{
    int b;
public:
    void setter(int _b){
        b = _b;
    }
};

int main(){
    std::vector<base*>b_vec = {
    new base(),
    new derived_a(),
    new derived_b();

    for(int i = 0; i < b_vec.size(); i++){
        derived_a*a = dynamic_cast<derived_a>(b_vec.at(i));
        if(a != NULL){
            a.setter(i);
        }
    }
}
```

ポインタをキャストしたときにキャスト可能かどうか判断して可能ならキャストし、不可能なら`NULL`を返すキャスト

判断する手間が増えるので重い処理になるので何回も使わないのがベスト

安全であるなら`static_cast`でもまったく問題ない

2021/1/16  
written by 西永
