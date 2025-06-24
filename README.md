# Arduino Bow
用實體弓箭模型操控電腦的弓箭手角色
---
這個模型目前分為三大部分:**弓箭本體**、**無線接收端**及**信號發送端** <br>
弓箭本體上由一顆左鍵按鈕(在拉弓時觸發，模擬左鍵按下)、技能按鍵(對應鍵盤上的e，用於觸發多數遊戲的弓箭技能)、加速度感測器(用於偵測弓箭移動來模擬滑鼠移動)及無線模組，並且由壓克力板拼裝而成，並且將橡皮筋固定在上面並黏在箭矢，箭頭有一凸出，在拉動時可壓到弓本體上的左鍵按紐，藉以模擬拉弓操作 <br>
無線接收端則有一個無線模組，用以接收弓箭本體傳送的信號，包括了按鍵的按下情況、加速度感測器的動量等，並且與信號發送端用序列埠進行溝通，將上述數據轉送，再由信後發送端拆解資料，將其轉換成對應的HID信號，透過USB發送至電腦，完成移動滑鼠、按下鍵盤按鍵等操作。
## 材料
- 三個Arduino
- - 一個要包含HID功能(如Arduino Pro Micro、Arduino Leonardo)，用以連接電腦，發送滑鼠鍵盤訊號
  - 另外兩個需要有3.3V電壓腳位，用以提供nRF24l01電源(如Arduino Uno、Arduino Leonardo)
  - 本作品使用Arduino Leonardo作為弓上裝置、Arduino Uno當無線接收端以及Arduino Pro Micro作為訊號傳送端
  - 若未來有機會優化，可使用兩個Arduino Leonardo，並將2.4g_receive和bow程式合併
- 幾個按鈕(像是青軸)
- MPU6050感測器
- 兩個nRF24l01
- 單芯線/多芯線
- 壓克力板或是可以用來製作弓箭模型的材料
- 焊接器具和錫

## 弓箭本體接線
首先選擇一個有3.3V的Arduino板，接著
- 將MPU6050的SDA及SCL接到板上對應位置(如Arduino Leonardo的SDA、SCL、Arduino UNO的A4、A5)
- 將nRF24l01依照[此教學](https://swf.com.tw/?p=1044)進行接線
- 將左鍵按鈕接到Pin5
- 將技能按鈕接到Pin6

## 無線接收端、信號發送端接線
將nRF24l01用跟弓箭本體一樣的接法接到無線接收端的Arduino(一樣要有3.3V)，接著與信號發送端(具HID功能的Arduino)對接:
- 無線接收端的0接到信號發送端的1
- 無線接收端的1接到信號發送端的0 (其實就是RX、TX互相對接)
- 信號發送端的5V接到無線接收端的Vin
- 信號發送端的GND接到無線發送端的GND

## 程式
- 將[gpt_2.4g_send.ino](https://github.com/samuelhsieh0829/Arduino_Bow/blob/main/gpt_2.4g_send.ino)燒入弓箭本體
- 將[gpt_2.4g_receive.ino](https://github.com/samuelhsieh0829/Arduino_Bow/blob/main/gpt_2.4g_receive.ino)燒入無線接收端
- 將[gpt_bow.ino](https://github.com/samuelhsieh0829/Arduino_Bow/blob/main/gpt_bow.ino)燒入信號發送端

## 示範成品圖
