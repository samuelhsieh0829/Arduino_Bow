#include <Mouse.h>
#include "Keyboard.h"

struct DataPacket {
  uint8_t startMarker;  // 頭部標記
  int16_t ax, ay, az, gx, gy, gz;
  bool lmbPressed;
  bool ePressed;
  uint8_t endMarker;    // 尾部標記
};

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);  // 用於接收數據
  Mouse.begin();
  Keyboard.begin();
}

void loop() {
  if (Serial1.available() >= sizeof(DataPacket)) {
    // 當接收到完整的結構體數據
    DataPacket packet;
    Serial1.readBytes((uint8_t*)&packet, sizeof(packet));
    if (packet.startMarker == 0xAA && packet.endMarker == 0x55) {
    
      // Serial.print("X: "); Serial.println(packet.gx);
      // Serial.print("Y: "); Serial.println(packet.gy);
      // Serial.print("Z: "); Serial.println(packet.gz);
      // Serial.print("AX: "); Serial.println(packet.ax);
      // Serial.print("AY: "); Serial.println(packet.ay);
      // Serial.print("AZ: "); Serial.println(packet.az);
      Serial.print(packet.gx); Serial.print("\t");
      Serial.print(packet.gy); Serial.print("\t");
      Serial.print(packet.gz); Serial.print("\t");
      Serial.print(packet.ax); Serial.print("\t");
      Serial.print(packet.ay); Serial.print("\t");
      Serial.print(packet.az); Serial.println("\t");
      // Serial.print("LMB: "); Serial.println(packet.lmbPressed);
      // Serial.print("e: "); Serial.println(packet.ePressed);

      // 根據接收到的數據進行滑鼠操作
      int x = packet.gx / 300;
      int y = packet.gy / 300;

      Mouse.move(-x*6, y*6);  // 調整數據的比例來控制移動

      // 按鈕操作
      if (packet.lmbPressed) {
        Mouse.press(MOUSE_LEFT);  // 按下左鍵
      } else {
        Mouse.release(MOUSE_LEFT);  // 釋放左鍵
      }
      if (packet.ePressed) {
        Keyboard.press('e');
      } else {
        Keyboard.release('e');
      }
    }
  }
}
