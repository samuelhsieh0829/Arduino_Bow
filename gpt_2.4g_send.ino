#include <SPI.h>
#include "RF24.h"
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <avr/wdt.h>

MPU6050 mpu;
RF24 rf24(7, 8); // CE腳, CSN腳

const byte addr[] = "1Node";

// 定義數據結構
struct DataPacket {
  uint8_t startMarker;  // 頭部標記
  int16_t ax, ay, az, gx, gy, gz;
  bool lmbPressed;
  bool ePressed;
  uint8_t endMarker;    // 尾部標記
};

void setup() {
  rf24.begin();
  rf24.setChannel(120);
  rf24.openWritingPipe(addr);
  rf24.setPALevel(RF24_PA_LOW);
  rf24.setDataRate(RF24_1MBPS);
  rf24.stopListening();

  pinMode(5, INPUT_PULLUP); // lmb
  pinMode(6, INPUT_PULLUP); // e
  
  Wire.begin();
  mpu.initialize();
}

void loop() {
  DataPacket packet;
  packet.startMarker = 0xAA; // 設置頭部標記
  mpu.getMotion6(&packet.ax, &packet.ay, &packet.az, &packet.gx, &packet.gy, &packet.gz);
  packet.lmbPressed = (digitalRead(5) == LOW);
  packet.ePressed = (digitalRead(6) == LOW);
  packet.endMarker = 0x55; // 設置尾部標記

  rf24.write(&packet, sizeof(DataPacket)); // 傳送整個數據包
  // delay(10); // 控制傳輸頻率
}
