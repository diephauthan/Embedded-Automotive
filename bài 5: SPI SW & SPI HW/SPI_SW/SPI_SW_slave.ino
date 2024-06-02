
#include "stdbool.h"
#define SS 10
#define MOSI 11
#define SCK 13
volatile uint8_t dat=0x00;
void setup() {
  Serial.begin(9600);  
  pinMode(SS, INPUT_PULLUP);
  pinMode(MOSI,INPUT);
  pinMode(SCK, INPUT);

}
uint8_t SPI_SlaveReceive()
{
  uint8_t i = 0;  
  volatile uint8_t dataReceive=0x00;
  bool st=0;
  while (digitalRead(SS));
  while (!digitalRead(SCK));
    for(i=0; i<8;i++)
    { if(digitalRead(SCK)){
      while (digitalRead(SCK)) st = digitalRead(MOSI);
      dataReceive=dataReceive<<1;
      dataReceive=dataReceive|st;
    }
    while (!digitalRead(SCK));
    }
  return dataReceive;
}


// void loop(){
//   if(!(digitalRead(SS))){
//     dat=SPI_SlaveReceive();
//     Serial.println(dat,DEC);
//   }
// }

void loop() {
  uint8_t receivedData[7];
  int index = 0;

  // Chờ SS xuống mức thấp
  while (digitalRead(SS));

  // Nhận 7 byte dữ liệu
  for (index = 0; index < 7; index++) {
    receivedData[index] = SPI_SlaveReceive();
  }

  // In ra dữ liệu nhận được
  Serial.print("Received Data: ");
  for (int i = 0; i < 7; i++) {
    Serial.print(receivedData[i]);
    Serial.print(" ");
  }
  Serial.println();
  
  // Chờ SS lên mức cao (kết thúc truyền)
  while (!digitalRead(SS));
}