# HelloWorldしてみよう〜subscriber編〜  

## subscriberの実装  

1. プログラムを実装する  
   前の章でパッケージは作ってあるものとします。
   subscriber用に、`src/hello_world`内に`helloworld_sub.py`という新しいファイルを作りましょう。  
   中身はこちら↓  

   ```python {.line-numbers}
    import rclpy
    from rclpy.node import Node

    from std_msgs.msg import String

    class HelloWorldSubscriber(Node):
            def __init__(self):
                super().__init__('hello_world_subscriber')
                self.subscription = self.create_subscription(String, 'topic', self.listener_callback, 10)
        
            def listener_callback(self, msg):
                self.get_logger().info('I heard: "%s"' % msg.data)
                
    def main(args=None): 
        rclpy.init(args=args)
        hello_world_subscriber = HelloWorldSubscriber()
        rclpy.spin(hello_world_subscriber)
        hello_world_subscriber.destroy_node()
        rclpy.shutdown()
        
    if __name__ == '__main__':
        main()   
   ```  

    短くて幸せですね。重要なとこ1個だけ解説します。  

   - ```python
            def __init__(self):
                super().__init__('hello_world_subscriber')
                self.subscription = self.create_subscription(String, 'topic', self.listener_callback, 10)
            
            def listener_callback(self, msg):
                self.get_logger().info('I heard: "%s"' % msg.data)
        ```  

    3行目では、Nodeクラスの持つcreate_subscription関数を実行し、オブジェクトをsubscription変数に代入しています。  
    引数は(ROSメッセージ型, トピック名, コールバック関数, QoSプロファイル)です。QoSは、publisher側と合わせる必要があります。コールバック関数に引数を渡したい場合はラムダ式などを使うといいでしょう。  
    6行目は、Nodeクラスの持つログ表示用関数です。get_logger関数はかなり多機能なので補足にでも書きます。  

2. `setup.py`を変更する  

   - ```python
        entry_points={
            'console_scripts': [
                'hello_world_node = hello_world.hello_world:main',
                'hello_world_sub_node = hello_world.hello_world_sub:main'
            ],
        },
        ```

3. 実行する  
   1. `colcon build`  
   2. `ros2 run hello_world hello_world_sub_node`  


## get_logger()について(補足)

デバッグをする上で情報を出力することは手軽で有用な方法です。  
ROSでは、情報を出力するためにloggerの仕組みがあり、どのノードがいつ出力した情報であるか、簡単に表示できます。  

### ログの出力先  

ROS2のログシステムでは、3つの出力先を選べます。
  
1. ターミナル  
2. ストレージ上のログファイル  
3. `/rosout`トピック  

### ログレベル  

出力するログにレベルを設定することができます。高い順に以下のものがあります。  

```txt
Fatal
Error
Warn
Info
Debug
```

いくつかの方法を用いて、実行時に表示するログレベルを設定できます。  
実際は、設定したものより上のログがすべて表示されます。  
たとえば、ログレベルをWarnにするとWarn、Error、Fatalが、  
ログレベルをDebugにするとWarn、Error、Fatal、Info、Debugのすべてが表示されます。  

### 実装(python)  

```python
self.get_logger().info("Hello, info!")
self.get_logger().debug("Hello, debug!")
```

超かんたんです。

### 実装(C++)

```cpp
RCLCPP_INFO(this->get_logger(), "Hello, info!");
RCLCPP_DEBUG(this->get_logger(), "Hello, debug!");
```

超かんたんです。  

### 実行時に表示するログレベルを変更する(ros2 run編)  

`ros2 run 〇〇 △△ --ros-args --log-level debug`  
普通に見たとおりです。  

### 実行時に表示するログレベルを変更する(ros2 launch編)  

launchファイルの話をまだしてない気がしますが、書いてしまいます。  
全部書くのだるいので必要な部分だけ書きます。全体像はlaunchの回を見てください。  

```python
    ld = LaunchDescription()
    log_level = LaunchConfiguration("log_level")
    log_level_arg = DeclareLaunchArgument(
        "log_level", 
        default_value = ["info"],
        description = "Logging level",
    )
    
    hello_world_node = Node(
        package="hello_world",
        executable="hello_world_node",
        name="hello_world_node",
        emulate_tty=True,
        arguments=["--ros-args", "--log-level", log_level]    
    )
    ld.add_action(log_level_arg)
    ld.add_action(hello_world_node)
```

実行方法は`ros2 launch helloworld_launch log_level:=debug`  
みたいな感じです。デフォルト引数でinfoを指定しているので`log_level:=debug`がないとinfoになります。  