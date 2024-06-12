#include <Wire.h>

#define SLAVE_ADDRESS 0x08

void setup() {
  Wire.begin(SLAVE_ADDRESS); // Thiết lập Arduino làm I2C slave với địa chỉ SLAVE_ADDRESS
  Wire.onReceive(receiveEvent); // Đăng ký hàm callback khi nhận dữ liệu
  Serial.begin(9600);
}

void receiveEvent(int howMany) {
  Serial.print("Received: ");
  while (Wire.available()) { // Lặp lại khi còn dữ liệu
    uint8_t c = Wire.read(); // Đọc dữ liệu
    Serial.print(c); // In dữ liệu ra Serial Monitor
    Serial.print(' '); // In dấu cách giữa các giá trị
  }
  Serial.println(); // In dấu xuống dòng sau khi nhận dữ liệu
}

void loop() {
  // Không làm gì trong loop
}


