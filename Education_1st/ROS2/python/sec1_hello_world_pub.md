# HelloWorldしてみよう
## 概要
publisher/subscriber型通信を行ってみましょう。  
ここでは、publisherが送ったString型のトピックをsubscriberで受け取って表示してみることにします。  

## publisherの実装
1. ROS2のパッケージとノードを作る  
基本的にワークスペースフォルダにsrcフォルダを作り、その中にパッケージを作るのがおすすめです(C++との兼ね合い)。  
    ```
    robocon2024_ws/
        | src/
    ```  

`cd robocon2024_ws/src/` : フォルダに移動  
`ros2 pkg create --build-type ament_python --node-name helloworld_node helloworld`: パッケージを作るコマンド。  
-  `--build-type`: ビルドの方法を指定。`ament_cmake`か`ament_python`が選べる。  
- `--node-name`: ノード名 パッケージ名の順番で指定する
  
2. プログラムを作成する
   ```python {.line-numbers}
    import rclpy
    from rclpy.node import Node

    from std_msgs.msg import String

    class HelloWorldPublisher(Node):
        def __init__(self):
            super().__init__('helloworld_pub')
            self.publisher_ = self.create_publisher(String, 'topic', 10)
            timer_period = 1.0
            self.timer = self.create_timer(timer_period, self.timer_callback)
            self.count = 0

        def timer_callback(self):
            self.count += 1
            msg = String()
            msg.data = 'Hello World' + str(self.count)
            self.publisher_.publish(msg)
            self.get_logger().info('Publishing: "%s"' % msg.data)
            
            
    def main(args=None):
        rclpy.init(args=args)
        hello_world_publisher = HelloWorldPublisher()
        rclpy.spin(hello_world_publisher)
        hello_world_publisher.destroy_node()
        rclpy.shutdown()
        
    if __name__ == '__main__':
        main()
   ```  
    ざっと説明していきます。  
    
   - ```python  
        import rclpy  
        from rclpy.node import Node
        from std_msgs.msg import String
        ```  
        1,2行目ではros2-python用ライブラリrclpyと、Nodeクラスをインポートしています。  
        このクラスを継承することでノードを作ることが出来ます。  
        3行目でトピックのメッセージ型をインポートしています。  
        
   - ```python
        class HelloWorldPublisher(Node):
            def __init__(self):
                super().__init__('helloworld_pub')
        ```  
        1行目では、Nodeクラスを継承したHelloWorldPublisherノードを定義しています。この時点では実体化はされていません。  
        2行目は、クラスが実体化された際に実行される初期化処理(コンストラクタといいます)です。  
        3行目で、継承元の親クラスのコンストラクタを実行しています。引数に渡しているのはノード名です。  
        
    - ```python
                self.publisher_ = self.create_publisher(String, 'topic', 10)
                timer_period = 1.0
                self.timer = self.create_timer(timer_period, self.timer_callback)
                self.count = 0
        ```
        1行目では、Nodeクラスがもつcreate_publisher関数を実行し、結果のオブジェクトをpublisher_変数に代入しています。このオブジェクトのもつ関数をつかってトピックをpublishします。  
        引数は(ROSメッセージ型, トピック名, QoSプロファイル)の順番です。QoSについては後ほど。  
        2,4行目では、それぞれ内部処理用の変数を宣言しながら代入しています。  
        3行目では、Nodeクラスが持つcreate_timer関数を実行し、結果のオブジェクトをtimer変数に代入しています。  
        引数は(実行周期(s), 実行したい関数オブジェクト)です。呼び出す関数に引数を渡したい場合はラムダ式などを使うといいでしょう。  
    - ```python
            def timer_callback(self):
                self.count += 1
                msg = String()
                msg.data = 'Hello World' + str(self.count)
                self.publisher_.publish(msg)
                self.get_logger().info('Publishing: "%s"' % msg.data)
        ```  
        先程のcreate_timerから呼び出される関数です。  
        2, 4行目で内部処理用の変数として先程宣言したcountを1増やし、文字列と結合しています。  
        `msg.data`という形でデータを代入しているのはROSのString型の構造のためです。くわしくは調べてね。  
        5行目では、先程宣言したpublisher_オブジェクトのもつpublish関数にトピックメッセージを渡してpublushしています。  
        6行目は、Nodeクラスのもつログ表示用関数です。  
    - ```python
         def main(args=None):
            rclpy.init(args=args)
            hello_world_publisher = HelloWorldPublisher()
            rclpy.spin(hello_world_publisher)
            hello_world_publisher.destroy_node()
            rclpy.shutdown()
        ```
        擬似的なmain関数です。pythonにはmain関数の概念は存在しませんが、諸々の理由で実装してあります。
        2行目でROSの初期化、3行目でNodeクラスを継承した HelloWorldPublisherクラスを実体化しています。  
        4行目で、ROSの処理を開始しています。これは、ctrl+cなどの例外が発生するまで動き続けます。  
        例外が発生すると、5行目,6行目に移り、終了処理を行います。
    - ```python
        if __name__ == '__main__':
            main()
        ```
        ターミナルからプログラムが起動した際に、main関数が実行されるようなコードです。
        
3. 実行してみよう  
    1. `robocon2024_ws`まで上のフォルダに移動しよう。`cd ..`でひとつ上に移動できるよ。  
    2. `colcon build`を実行
    3. `ros2 run  helloworld helloworld_node`を実行しよう

## 補足
### QoSについて  
QoSとはQuality of Serviceのこと。ノード間の通信をネットワークを介して行うROSでは、大量のデータをやり取りする際に優先度のようなものを決めて通信する必要がある。  
その優先度を設定するのがQoSプロファイルで、割と細かく設定できる。  
QoSの概念についてくわしくは[こちら](https://www.infraexpert.com/study/telephony6.html)。  

### String型のデータ構造について
[ROS2のドキュメント](https://docs.ros2.org/foxy/api/std_msgs/msg/String.html)にはこのような記載があります。  
```txt
# This was originally provided as an example message.

# It is deprecated as of Foxy

# It is recommended to create your own semantically meaningful message.

# However if you would like to continue using this please use the equivalent in example_msgs.


string data
```  
まあC言語の構造体みたいなもんだと思ってください。  
std_msgsの中には、[Int16](https://docs.ros2.org/foxy/api/std_msgs/msg/Int8.html)、[UInt8](https://docs.ros2.org/foxy/api/std_msgs/msg/UInt8.html)、[Float64](https://docs.ros2.org/foxy/api/std_msgs/msg/Float64.html)型や、これらの配列である[Int16MultiArray](https://docs.ros2.org/foxy/api/std_msgs/msg/Int8MultiArray.html)、[UInt8MultiArray](https://docs.ros2.org/foxy/api/std_msgs/msg/UInt8MultiArray.html)、[Float64MultiArray](https://docs.ros2.org/foxy/api/std_msgs/msg/Float64MultiArray.html)型の他、色を表す[ColorRGBA](https://docs.ros2.org/foxy/api/std_msgs/msg/ColorRGBA.html)型など、様々なものがあります。  


