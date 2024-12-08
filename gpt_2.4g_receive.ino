#include "SPI.h"
#include "RF24.h"

RF24 radio(7, 8); // CE腳, CSN腳

const byte addr[] = "1Node";
const byte pipe = 1;

// 定義數據結構
struct DataPacket {
  uint8_t startMarker;  // 頭部標記
  int16_t ax, ay, az, gx, gy, gz;
  bool lmbPressed;
  bool ePressed;
  uint8_t endMarker;    // 尾部標記
};

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_1MBPS);
  radio.setChannel(120);
  radio.openReadingPipe(pipe, addr);
  radio.startListening();
}

void loop() {
  if (radio.available(&pipe)) {
    DataPacket packet;
    radio.read(&packet, sizeof(DataPacket));

    // 驗證數據包頭尾標記
    if (packet.startMarker == 0xAA && packet.endMarker == 0x55) {
      Serial.write((uint8_t*)&packet, sizeof(packet));
      // Serial.print("GX: "); Serial.print(packet.gx);
      // Serial.print(" GY: "); Serial.print(packet.gy);
      // Serial.print(" LMB: "); Serial.print(packet.lmbPressed);
      // Serial.print(" E: "); Serial.println(packet.ePressed);
    } 
    // else {
    //   Serial.println("Invalid packet!");
    // }
  }
}
