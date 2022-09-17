# rosのインストール

## コマンド

```sh
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt install curl
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -

sudo apt update
sudo apt install ros-noetic-desktop-full # 何種類かあるのであとで説明

sudo apt-get install python3-rosdep
sudo rosdep init
rosdep update

echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
source ~/.bashrc
source /opt/ros/noetic/setup.bash

sudo apt-get -y install python3-rosinstall
sudo apt-get install -y python3-catkin-tools # catkin buildが使えるようになる。後述
```

基本的に上から実行していけば問題なくインストールできる

## 説明

### リポジトリの登録
```sh
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt install curl
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
```

リポジトリの登録をしている  
これで`apt install`でrosがインストールできるようになる

### インストール

```sh
sudo apt update
sudo apt install ros-noetic-desktop-full
```

`update`してから`install`する  
ubuntuなどを使っていれば違和感がないと思う

ちなみにインストールできるrosの種類にはいくつかあり、それぞれ`ros-noetic-desktop-full`、`ros-noetic-desktop`、`ros-noetic-ros-base`の3つがある

違いはインストールするもので、

`ros-noetic-ros-base`　には基本的な機能すべて(パッケージ、ビルド、通信やライブラリなど。GUIツール以外は入っている)。

`ros-noetic-desktop`には`ros-noetic-ros-base`に`rqt`や`rviz`のGUIツールが混ざる。

`ros-noetic-desktop-full`はすべてのツールが入って、gazeboと言った2D/3Dのツールが入っている

手元の環境に合わせてダウンロードすると良い(普通にPCだったら`ros-noetic-desktop-full`でいいんだけどね)

### 依存関係の解決

```sh
sudo apt-get install python-rosdep
sudo rosdep init
rosdep update
```

rosの依存しているパッケージのダウンロード

要するにrosを動かすために必要なもののダウンロードがコレだけでできる

### bashrcの設定

```sh
echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
source ~/.bashrc
source /opt/ros/noetic/setup.bash
```

rosのパスをbash(コマンドライン)で起動時に通すスクリプト  
パスを通さないと動かないらしいからしょうがないね

### 周辺ツールのインストール

```sh
sudo apt-get -y install python3-rosinstall
sudo apt-get install -y python3-catkin-tools
```

ros関連のライブラリがインストールされる  
特に2つ目の`python3-catkin-tools`は個人的に使いやすいと思っている`catkin build`が使えるのでおすすめ

#### catkin buildについて

rosのビルドシステムはcatkinというものが使われている。それがビルドから依存関係の解決、ライブラリのリンクまでを一手に担う`cmake`ベースのつよつよ君が使われている
デフォルトでは`catkin_make`が使われ、それでビルドされている。しかし、それは古い方のビルドツールなのでこのコマンドは並列ビルドができなかったり、`catkin_ws/src`にいないとコマンドが有効でなかったりとなかなか不便なので`catkin build`を使う。

`python3-catkin-tools`をインストールすれば使えるとさっき書いた。コレを使えばとても便利にコンパイルできるようになる。

今後の話のときのビルドツールは`catkin build`を使うので覚えておいてほしい

これ以上は話が逸れるので一旦切るが、機会があれば別の時に書こうと思う。

2022/09/27  
written by 西永
