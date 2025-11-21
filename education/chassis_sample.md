# 最小構成の足回りを作る（低レイヤ用）

> あえてちょっと言葉足らずな説明にしてます。\
> ここで説明なしに使った言葉は知識として知っといてほしいことです。\
> みんなで教えあって頑張ってね。

## ロボマスモーターについて
最小の前提知識だけ紹介する。\
ロボマスモーターはモーターの種類の名前である。\
うちにあるのはM2006, M3508の二種類。\
それぞれに対応したモータードライバが公式から出ており、c610, c620という\
データシートは以下。\
[c610](https://rm-static.djicdn.com/tem/17348/RoboMaster%20C610%20Brushless%20DC%20Motor%20Speed%20Controller%20User%20Guide.pdf)
[c620](https://rm-static.djicdn.com/tem/17348/RoboMaster%20C620%20Brushless%20DC%20Motor%20Speed%20Controller%20V1.01.pdf)
### c610, c620 の機能について
CAN通信を使って、所定の方式でデータを送ることで **電流値** の司令を送ることができる。\
方式はデータシート参照。\
**電流値** とは、モーターに流れる電流量を表す値のこと。\
モーターの回転速度ではなく、トルクと比例する点に注意。

CAN通信により、モーターの速度、回転角、出力トルク、（c620の場合は、加えて温度）をフィードバックとして送ってくれる。\
方式はデータシート参照。

## 期待する動き
PCからCAN1にモーターの速度司令が送られてくる。\
CAN2に接続されたロボマスモーター（正しくはモータードライバ[^1]）に司令を送り、PI制御によりなるべく司令された速度に近づける。\
PC間のCAN通信のプロトコルは以下。

|CAN ID|役割|
|-|-|
|0x10|id1のモーターの速度指令値(rad/s)|
|0x11|id2のモーターの速度指令値(rad/s)|
|0x12|id3のモーターの速度指令値(rad/s)|
|0x13|id4のモーターの速度指令値(rad/s)|

各idでは8バイトでデータが送られる。
先頭4バイトにfloat形式（リトルエンディアン）で速度指令値(rad/s)が入っている。


## stm32 プロジェクト作成
2025本ロボ基板想定で書きます。

マイコンはF446RE

CAN1, CAN2有効\
どちらもbaud rate 1Mbit/s にして割り込みを有効にしておく\
TX, RXのピンはデフォルト

TIM7有効\
周波数1kHzにして割り込み有効にしておく

以上。

## step1 とりあえずモーターを回そう

> プログラム構成はあくまで例です。\
> チュートリアル用に自分が考えただけなので、自分で考えてかける人はそれで書いちゃってOKです。

### 仕様
電流値300で繋がっているすべてのモーターを回す。

### 実装
#### 変数定義
```cpp
int current[4];
```
#### CANの初期設定
```cpp
void CAN_init(){
    CAN_FilterTypeDef can1_filter, can2_filter;
	can1_filter.FilterIdHigh         = 0 << 5;
	can1_filter.FilterIdLow          = 0 << 5;
	can1_filter.FilterMaskIdHigh     = 0 << 5;
	can1_filter.FilterMaskIdLow      = 0 << 5;
	can1_filter.FilterScale          = CAN_FILTERSCALE_16BIT;
	can1_filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	can1_filter.FilterBank           = 0;
	can1_filter.FilterMode           = CAN_FILTERMODE_IDMASK;
	can1_filter.SlaveStartFilterBank = 14;
	can1_filter.FilterActivation     = ENABLE;
	HAL_CAN_Start(&hcan1);
	HAL_CAN_ConfigFilter(&hcan1, &can1_filter);
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);

	can2_filter.FilterIdHigh         = 0 << 5;
	can2_filter.FilterIdLow          = 0 << 5;
	can2_filter.FilterMaskIdHigh     = 0 << 5;
	can2_filter.FilterMaskIdLow      = 0 << 5;
	can2_filter.FilterScale          = CAN_FILTERSCALE_16BIT;
	can2_filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	can2_filter.FilterBank           = 14;
	can2_filter.FilterMode           = CAN_FILTERMODE_IDMASK;
	can2_filter.SlaveStartFilterBank = 14;
	can2_filter.FilterActivation     = ENABLE;
	HAL_CAN_Start(&hcan2);
	HAL_CAN_ConfigFilter(&hcan2, &can2_filter);
	HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
}
```
フィルターしてCANを起動するだけ。コピペでOK

#### TIMの初期設定
```cpp
void TIM_Init(){
    HAL_TIM_Base_Start_IT(&htim7);
}
```
TIMを起動するだけ。コピペでOK。

#### CAN割り込み
```cpp
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    CAN_RxHeaderTypeDef RxHeader;
    uint8_t RxData[8];
    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK) return;
    uint32_t id = (RxHeader.IDE == CAN_ID_STD)? RxHeader.StdId : RxHeader.ExtId;
}
```
雛形だけで何もしない。コピペでOK
#### ロボマスに電流値を送る関数
```cpp
void send_current_data(){
    uint8_t TxData[8];
    CAN_TxHeaderTypeDef TxHeader;
    uint32_t TxMailbox;
    // データシート参照
    for(int i = 0;i < 4;i++){
        TxData[2 * i]     = current[i] >> 8;
        TxData[2 * i + 1] = current[i] & 255;
    }
    TxHeader.DLC = 8;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.StdId = 0x200; // データシート参照
    // CAN2でロボマスに電流値を送る
    HAL_CAN_AddTxMessage(&hcan2, &TxHeader, TxData, &TxMailbox);
}
```
中央のfor文は面倒でも、理解のためにタイプして写すのをおすすめする。\
`current[i] >> 8`は電流値の上位8bitを取り出す操作。\
`current[i] & 255`は電流値の下位8bitを取り出す操作[^2]。

#### TIM割り込み
```cpp
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if(htim == &htim7){
		for(int i = 0;i < 4;i++){
            current[i] = 300; // 全モーターの電流値を300に設定
		}
        send_current_data();
	}
}
```
電流値を300に設定し、先程作った関数でロボマスに電流値を送っている。
コピペでOK

### main関数
```cpp
int main(void)
{
	（略）
  /* USER CODE BEGIN 2 */
	CAN_init();
	TIM_init();
  /* USER CODE END 2 */
	（略）
}
```
### 実行
必ず足回りに下駄を履かせてから書き込む。
タイヤが回ったら成功。

## step2 PID制御をしよう

### 仕様
速度1(rad/s)で繋がっているすべてのモーターを回す。
モタドラからのフィードバックを受けて速度PI制御[^3]をする。

### 実装
#### 変数定義
```cpp
float p_gein[4] = {6, 6, 6, 6};
float i_gein[4] = {3, 3, 3, 3}; 
float integral[4];
float target_vel[4] = {1, 1, 1, 1}; // 1 (rad/s)
float velocity[4];
const float gear_ratio = 19;
```
PIゲイン、積分値、速度指令値、ギア比を定義
コピペOK
#### CAN割り込み
```diff
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    CAN_RxHeaderTypeDef RxHeader;
    uint8_t RxData[8];
    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK) return;
    uint32_t id = (RxHeader.IDE == CAN_ID_STD)? RxHeader.StdId : RxHeader.ExtId;
+ 	if(hcan == &hcan2){
+		if(0x200 <= id && id <= 0x203){
+			int robomas_id = id - 0x200;
+			velocity[robomas_id] = (RxData[2] << 8 | RxData[3]) / gear_ratio / 8192 * 6.28 // データーシート参照
+		}
+	}
}
```
（WIP）
#### TIM割り込み
```diff
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if(htim == &htim7){
		for(int i = 0;i < 4;i++){
-           current[i] = 300; // 全モーターの電流値を300に設定
+			const float dt = 0.001;
+			float error = target_vel[i] - velocity[i];
+			current[i] = p_gein * error + i_gein * integral[i];
+			integral[i] += error * dt;
		}
        send_current_data();
	}
}
```
（WIP）
### 実行
必ず足回りに下駄を履かせてから書き込む。
タイヤが回ったら成功。

## step3 PCからの司令を受け取ろう
#### CAN割り込み
```diff
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    CAN_RxHeaderTypeDef RxHeader;
    uint8_t RxData[8];
    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK) return;
    uint32_t id = (RxHeader.IDE == CAN_ID_STD)? RxHeader.StdId : RxHeader.ExtId;
+ 	if(hcan == &hcan1){
+		if(0x10 <= id && id <= 0x13){
+			int robomas_id = id - 0x10;
+			target_vel[robomas_id] = *(float*)RxData;
+		}
+	}
 	if(hcan == &hcan2){
		if(0x200 <= id && id <= 0x203){
			int robomas_id = id - 0x200;
			velocity[robomas_id] = (RxData[2] << 8 | RxData[3]) / gear_ratio / 8192 * 6.28 // データーシート参照
		}
	}
}
```
PCからのデータを読み取る。（WIP）

### 実行
必ず足回りに下駄を履かせてから書き込む。
タイヤが回ったら成功。お疲れ様でした。

[^1]: モタドラって略します
[^2]: 255は二進数で11111111(2)と書けるのがポイント
[^3]: [この記事](https://controlabo.com/pid-control-introduction/)がわかりやすいです\数学は難しいので後でちゃんと説明します。