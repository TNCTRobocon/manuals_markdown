# メッセージ型について

ROS2のメッセージ型は星の数より多いので、ざっとかいつまんで説明していきます。  

## [std_msgs](https://docs.ros2.org/foxy/api/std_msgs/index-msg.html)  

基本的な数字や文字が扱える型の集まりです。  
Foxy以降のバージョンで非推奨な型は紹介しません。

- Int〇〇系  
  〇〇のところに入ってる大きさのInt型メッセージです。
  ex. Int8、Int16

- Uint〇〇系  
  大きさはInt〇〇系と同じですが、符号なしのInt型メッセージです。  
  ex. Uint8、Uint16
  
- Float〇〇系  
  〇〇のところに入ってる大きさのFloat型メッセージです。  
  Float64って、つまりdoubleですね。  
  ex. Float32、Float64
  
- 〇〇MultiArray系  
  上のような型の配列を扱うためのメッセージです。  
  ex. Int32MultiArray、Uint8MultiArray、Float64MultiArray、ByteMultiArary
  
- Byte
  名前通りです。  
  
- Bool
  名前通りです。  
  
- Char
  名前通りです。~~実態はただのuint8~~
  
- String
  名前通りです。  
  
- ColorRGBA  
  色の情報(赤緑青+透明度)を管理します。  
  使ったことは2回しかないです。  
  
- Header  
  タイムスタンプやフレームIDと呼ばれる情報を管理します。詳しくは調べてね。  
  
## [sensor_msgs](https://docs.ros2.org/foxy/api/sensor_msgs/index-msg.html)  

多すぎるのと、たまによくわかんないのがあるので適当です。

- Imu  
  中身はQuaternion(四元数)とAngularVelocity(角速度)とLinearAcceleration(加速度)です。  
  QuaternionからRPY(ロール/ピッチ/ヨー)への変換は調べてね。  

- PointCloud/PointCloud2  
  点群データを管理します。LidarだったりRealsenseだったり。
  (難しいことは無視)  
  
- Image/CompressedImage  
  カメラからの映像などを扱います。圧縮に関しては自分で調べてね。  
  
- Joy/JoyFeedBack/JoyFeedBackArray  
  ジョイスティックを取り扱います。スティックとボタンの情報を持ちます。  
  対応したコントローラーへの触覚フィードバックを行うこともできます。  
  たのしいです(当社比)
  
- JointState  
  ロボットのジョイント部の状態を取り扱います。  
  
- LaserScan  
  Lidarのスキャンデータを扱います。角度の情報や距離の情報を持ちます。  
  
その他にも、温湿度や気圧、地磁気、超音波距離計のデータやGPSデータ、バッテリーデータに至るまで目白押しです。  
なんとなく使いそうなものだけ紹介しました。  

## [geometry_msgs](https://docs.ros2.org/foxy/api/geometry_msgs/index-msg.html)  

これもちょっとだけ紹介。  

- Point  
  x, y, z座標を持ちます。
  
- Quaternion  
  さっき紹介したやつです。  
  
- Pose  
  Point型とQuaternion型を持ちます。まとめて管理できる感じ。  
  
- Pose2D  
  x, yとthetaを持ちます。平面でのロボット座標の管理に最適です。  
  
- Vector3  
  x, y, zのベクトルを管理します。  
  
- Twist  
  Vector3型のlinearとangularを持ちます。ロボットの移動速度の管理に最適。  
  
- 〇〇Stamped  
  〇〇の情報に加えて、std_msgs/Headerを持ちます。  
  ex. QuaternionStamped、PoseStamped
  
- Transform  
  後にTFを使うときに役立ちます。  
  
この他にも無限にあります。ほぼ使い方わからん。  

## その他

他にも、visualization_msgsやnav_msgs、map_msgsなど様々なメッセージ型群があります。  
必要に応じて調べると良いです。  

2024/12/23 written by Kohki S.  
にゃーん  
