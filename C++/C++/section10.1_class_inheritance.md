# 継承

## 継承とは

クラスの機能を受けついで新しいクラスを作り出す機能

ポリモーフィズムと大いに関わる機能  
うまく使えば便利だが、うまく使えないとコードが複雑になるだけでメリットを感じられないことも多い機能

```C++
#include<iostream>

class base_class{
public:
    void print(){
        std::cout << "base class\n";
    }
};

class derived_class : public base_class{
public:
    void print_new{
        std::cout << "derived class\n";
    }
};

int main(){
    derived_class dc;

    dc.print();//base class
    dc.print_new();//derived class
}
```

継承元となるクラスを基底クラス(スーパークラス、親クラス)という  
今回はbase_classが親クラスに当たる


