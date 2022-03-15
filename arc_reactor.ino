#include "modeRoutines.hpp"


// global pins and varibles for sms and struct for modes
int outputEnablePinSH1 = 5; //control brightness with pwm for shift reg 1 (inner lights)
int outputEnablePinSH2 = 6; //control brightness with pwm for shift reg 2 (outter lights)
const int button = 7; // button pin for manual mode cyclying 

static reactor_mode* inUse; // using static to keep mode between fun calls, only lights sm or bluetooth sm can edit this,

// light mode designation and audio designation

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
    
} task;

const unsigned short tasksNum = 2;
task tasks[tasksNum];

enum Light_States { lightmode_SMStart, lightmode_Welcome , lightmode_Input};
//writes to global lightmode_Select

int TickFct_Light(int state) { 
static int localtick_Light;
static reactor_mode* tempMode;
static int tempDurration;

  switch (state){ // transition
    case lightmode_SMStart:
      inUse = &allModes[0];
      tempMode = &allModes[0];
      localtick_Light = 0;
      state = lightmode_Welcome;
      
      sr.setAllLow();
    break;

    case lightmode_Welcome:
    //button input
      if(digitalRead(button)){
        //Serial.print(digitalRead(button));
        tempMode = &allModes[inUse->modeNumber + 1];
        localtick_Light = 0;
      }
      else{
          inUse = tempMode;
      }
    //
      if(localtick_Light % inUse->modeDuration == 0) {
        state = lightmode_Input;
        inUse = &allModes[inUse->modeNumber + 1];
        tempMode = inUse;
        localtick_Light = 0;
      }   
    break;

    case lightmode_Input:
    state = lightmode_Input;
    //button input
      if(digitalRead(button)){
         //Serial.print(digitalRead(button));
        if(inUse->modeNumber < totalModes){
         tempMode = &allModes[inUse->modeNumber + 1];
         }
         else{
          tempMode = &allModes[1];
         }
         localtick_Light = 0;
     }else{
          inUse = tempMode;
        }
       
    break;

    default:
    break;
    }
    
  switch(state){ //action
    case lightmode_SMStart:
    break;

    case lightmode_Welcome:
    localtick_Light++;
    welcomeMrStarkLights(localtick_Light);  
    
    break;

    case lightmode_Input:
    localtick_Light++;
    Serial.print('\n');
    Serial.print("mode num");
    Serial.print(inUse->modeNumber);
    Serial.print('\n');
      if(inUse->modeNumber == 1){
       // systemsOnLights(localtick_Light);
      }

      if(inUse->modeNumber == 2){
      //  repulsorBlastLights(localtick_Light);
      }  
    break;

    default:
    break;

    }
  
  return state;
}

//reads lightmode_select to set audiomode_Select
enum Audio_States {audiomode_SMStart, audiomode_Welcome , audiomode_Input };
int TickFct_Audio(int state) { 
  switch(state){//transitions
    case audiomode_SMStart:
    
    break;
    }
  switch(state){//actions
    }
  
return state; 
}

void setup() {
  unsigned char i = 0;
  tasks[i].state = lightmode_SMStart;
  tasks[i].period = 100;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &TickFct_Light;
  i++;
  tasks[i].state = audiomode_SMStart;
  tasks[i].period = 100;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &TickFct_Audio;

  pinMode(outputEnablePinSH1, OUTPUT);
  pinMode(outputEnablePinSH2, OUTPUT);

  pinMode(button, INPUT);
  Serial.begin(9600);
  
}


void loop() {
  // put your main code here, to run repeatedly:
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
     if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
      
     }
   }
  delay(100); // GCD.
}
