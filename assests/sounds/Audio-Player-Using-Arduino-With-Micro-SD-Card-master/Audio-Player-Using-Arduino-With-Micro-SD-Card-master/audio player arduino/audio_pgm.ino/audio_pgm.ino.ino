
#include "SD.h"
#define SD_ChipSelectPin 10
#include "TMRpcm.h"
#include "SPI.h"

TMRpcm tmrpcm;


#include <ShiftRegister74HC595.h>
ShiftRegister74HC595<3> sr(2, 3, 4);

void setup()
{
tmrpcm.speakerPin=8;
Serial.begin(9600);
if(!SD.begin(SD_ChipSelectPin))
{
  Serial.println("SD fail");
  return;
}
tmrpcm.setVolume(6);
tmrpcm.play("welcome.wav");

}

void loop() {
  // put your main code here, to run repeatedly:

}
