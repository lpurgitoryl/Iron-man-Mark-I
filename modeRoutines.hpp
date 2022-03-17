/*
  ShiftRegister74HC595 - Library for simplified control of 74HC595 shift registers.
  Developed and maintained by Timo Denk and contributers, since Nov 2014.
  Additional information is available at https://timodenk.com/blog/shift-register-arduino-library/
  Released into the public domain.
*/

#include <ShiftRegister74HC595.h>
#include "modes.h"
// parameters: <number of shift registers> (data pin, clock pin, latch pin)
ShiftRegister74HC595<3> sr(2, 3, 4);
//leds start at zero
//9th leds
#define firstOutterPin 8
#define ledsOutter 9
#define ledsInner 4
#define oeInner 5
#define oeOutter 6

//static int tempDur;
//varible pwm for where ouputEnable controled the inner or outter rings
void setBrightness(int outputEnable, int brightness) // 0 to 255
{
  analogWrite(outputEnable, 255-brightness);
}

// 

void welcomeMrStarkLights( int localTick){ // 
//outer ring
if(localTick < 70  ){//was 90
  bool oneOn = true;
    for(int i = 0; i <= ledsOutter ; i++ ){
      if(sr.get(i + firstOutterPin) == 0 && localTick % 4 == 0 && oneOn){
      setBrightness(oeOutter, (i != 0 ? i : 1) * 25);
      sr.set(i + firstOutterPin, HIGH);
     
      oneOn = false;
      }
    }  
}
else{
  if(localTick %  15 == 0 ){
    setBrightness(oeOutter, 255/5);
   }
  else {
    setBrightness(oeOutter, 255/ (localTick % 15)); 
    
    }
}
}

void systemsOnLights(int localTick){
sr.set(0, HIGH);

//mkae sure outter lights are on
for(int i = 0; i <= ledsOutter ; i++ ){
      if(sr.get(i + firstOutterPin) == 0){
      sr.set(i + firstOutterPin, HIGH);
      }
}  
setBrightness(oeOutter, 255);

if(localTick < 40){
  sr.setAllHigh();
  setBrightness(oeInner, 255/ (localTick % 10));
}else{setBrightness(oeInner, 255);setBrightness(oeOutter, 255);}

}

void repulsorBlastWarmup(int localTick){ // 7 ticks
   setBrightness(oeOutter , localTick * 35 );
   setBrightness(oeInner , localTick * 35 );  
}

void repulsorBlastFadeOut(int localTick){
  if(localTick <= 7){
    sr.setAllHigh();
    repulsorBlastWarmup(localTick);
    
   }else if ( localTick > 7){
    for(int i = 0; i <= ledsOutter ; i++ ){
      sr.set(i + firstOutterPin, LOW);
    } 
    for(int i = 0; i <= ledsInner ; i++ ){
      sr.set(i, LOW);
     
    }
}
}

void systemsDown(){
  sr.setAllLow();  
}

int setBTmode(String voiced){ // returns neg 1 if no match
  int modeSelect = -1;
      if(voiced == "*system on"){
       modeSelect = 1 ;
      }

      if(voiced == "*repulsor blast" ){
      modeSelect = 2;
      }
      if(voiced == "*system down"){
        modeSelect = 3;
      } 
    
  return modeSelect;    
}
