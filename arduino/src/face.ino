#include "MeAuriga.h"
MeLEDMatrix matrix1(PORT_6);
MeLEDMatrix matrix2(PORT_7);

uint8_t faceA[16] = {1,9,12,13,12,138,0,40,0,128,10,13,12,13,0,1};
uint8_t faceB[16] = {0,0,0,0,17,114,8,125,114,19,0,0,0,0,0,0};
uint8_t buffer[32];
uint8_t index = 0;
uint8_t prevC = 0;
uint8_t pprevC = 0;
bool isStarting = false;
void setup(){
  Serial.begin(115200);
}
void loop(){
  if(Serial.available()){
    uint8_t c = Serial.read();
    if(!isStarting){
      if(c==0x20){
        if(prevC==0x55){
          if(pprevC==0xff){
            isStarting = true;
          }
        }
      }
      pprevC = prevC;
      prevC = c;
    }else{
      for(int i=0;i<16;i++){
        faceA[i] = buffer[i];
        faceB[i] = buffer[i+16];
      }
      matrix1.setBrightness(1);
      matrix2.setBrightness(1);
      matrix1.drawBitmap(0,0,16,faceA);
      matrix2.drawBitmap(0,0,16,faceB);
      buffer[index] = c;
      if(index>31){
        index = 0;
        isStarting = false;

      }else{
        index++;
      }
    }
  }
}
