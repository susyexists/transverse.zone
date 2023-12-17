#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h> // table for Oscils to play
#include <AutoMap.h> // maps unpredictable inputs to a range

Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> sinOscil (SIN2048_DATA);

const int MIN_CARRIER_FREQ = 0;
const int MAX_CARRIER_FREQ = 1023;
int oscilGain;

AutoMap mapSinOscil(0,4095,MIN_CARRIER_FREQ,MAX_CARRIER_FREQ);
AutoMap mapOscilGain(0,4095,0,7);

const int numPots = 7;
const int potPins[numPots]= {12,33,32,35,34,27,14};
int potVals[numPots]= {};

#define CONTROL_RATE 128 // faster than usual to help smooth CONTROL_RATE adsr interpolation (next())
void setup() {
  Serial.begin(115200);
  startMozzi(CONTROL_RATE); // :)
}

void updateControl(){
   for(int i=0; i<numPots;i++){
  potVals[i]=analogRead(potPins[i]);
}
  oscilGain = mapOscilGain(potVals[0]);
  int sinFreq = mapSinOscil(potVals[1]);
  

  sinOscil.setFreq(sinFreq);
  
  // fm_intensity = (potVals[3] * (kIntensityMod.next())); // shift back to range after 8 bit multiply
}


AudioOutput_t updateAudio(){
  
  return MonoOutput::from8Bit(oscilGain*sinOscil.next());
}


void loop(){
  audioHook(); // required here
}
