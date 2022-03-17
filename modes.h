#ifndef MODES_H
#define MODES_H


typedef struct reactor_mode{ // settings for light/audio mode
  int modeNumber ; // might delete
  int modeDuration ; //in ms 
  String modeName;
  String audioFile;
  } reactor_mode;

#define totalModes 5

const reactor_mode welcomeMrStark {0, 12 * 10 , "welcome", "welcome.wav"}; // outter rings move in clockwise while middle fades on "hello mr stark"
const reactor_mode systemsOn {1, 8 * 10, "system on", "systemson.wav"}; // all lights are on
const reactor_mode whoIsJarvis {4, 1 * 10 , "who is jarvis", "jarvis.wav"}; // all lights are on
const reactor_mode repulsorBlast {2, 2.2 * 10 , "repulsor blast", "repulsor.wav"}; // all lights are on
const reactor_mode systemsOff {3, 2.2 * 10 ,"system down", "repulsor.wav"}; // all lights are on







reactor_mode allModes[totalModes] = {welcomeMrStark, systemsOn, repulsorBlast, systemsOff, whoIsJarvis};


#endif
