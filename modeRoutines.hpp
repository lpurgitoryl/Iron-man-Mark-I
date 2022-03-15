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

void welcomeMrStarkLights( int localTick){ // runes for 12 secs
//outer ring
if(localTick < 90  ){
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
setBrightness(oeInner, 255);
setBrightness(oeInner, 255);

    Serial.print("\n tick ");
    Serial.print(localTick);
    Serial.print("\n");
    
if(localTick < 10  ){
      //if( localTick % 10 == 0 ){
        sr.get(1) == 0 ? sr.set(1 , HIGH) : sr.set(1 , LOW) ;
        sr.get(3) == 1 ? sr.set(3 , HIGH) : sr.set(3 , LOW);
        sr.get(2) == 1 ? sr.set(2 , HIGH) : sr.set(2 , LOW);
        sr.get(4) == 0 ? sr.set(4 , HIGH) : sr.set(4 , LOW);

}else{sr.setAllHigh();}

}

void repulsorBlastLights(int localTick){
sr.set(0, HIGH);
//mkae sure outter lights are on
for(int i = 0; i <= ledsOutter ; i++ ){
      if(sr.get(i + firstOutterPin) == 0){
      sr.set(i + firstOutterPin, HIGH);
      }
}  
setBrightness(oeInner, 255);
setBrightness(oeInner, 255);
    
if(localTick < 80  ){
      if( localTick % 10 == 0 ){
        sr.get(1) == 0 ? sr.set(1 , HIGH) : sr.set(1 , LOW) ;
        sr.get(3) == 1 ? sr.set(3 , HIGH) : sr.set(3 , LOW);
        sr.get(2) == 1 ? sr.set(2 , HIGH) : sr.set(2 , LOW);
        sr.get(4) == 0 ? sr.set(4 , HIGH) : sr.set(4 , LOW);

        
      }else{
        sr.get(1) == 1 ? sr.set(1 , LOW) : sr.set(1 , HIGH) ;
        sr.get(3) == 0 ? sr.set(3 , HIGH) : sr.set(3 , LOW);
        sr.get(2) == 0 ? sr.set(2 , HIGH) : sr.set(2 , LOW);
        sr.get(4) == 1 ? sr.set(4 , LOW) : sr.set(4 , HIGH);}
    } 
  
}
