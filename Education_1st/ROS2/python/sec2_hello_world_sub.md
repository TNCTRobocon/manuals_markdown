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

## 補足

### get_logger()について

にゃーん