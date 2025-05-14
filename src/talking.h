#ifndef talking_h
#define talking_h
#include <parameters.h>
#include <Wire.h>

#define I2C_SLAVE_ADDR 0x08  // Must match master's address

const int NUM_SLIDERS = 14;
uint8_t sliderValues[NUM_SLIDERS];

int mapToFixedSet(uint8_t input) {
    const int lookup[] = {4, 2, 0, 1, 3};
    int index = input / 51; // 256 / 5 = approx. 51.2
    if (index > 4) index = 4;
    return lookup[index];
  }

void updateSliderValues(){
    sinFreqR=sliderValues[0]/16;
    sinFreqG=sliderValues[1]/16;
    sinFreqB=sliderValues[2]/16;
    xScale1=sliderValues[3]*50;
    yScale1=sliderValues[4]*50;
    xScale2=sliderValues[5]*50;
    yScale2=sliderValues[6]*50;
    xScale3=sliderValues[7]*50;
   yScale3=sliderValues[8]*50;
   tScale1=sliderValues[9];
   tScale2=sliderValues[10];
   tScale3=sliderValues[11];
   scramble1=mapToFixedSet(sliderValues[12]);
   scramble2=mapToFixedSet(sliderValues[13]);
}
void initSliderValues(){
    for(int i=0;i<NUM_SLIDERS;i++){
        sliderValues[i]=128;
    }
    updateSliderValues();
}
void receiveEvent(int numBytes) {
  int i = 0;
  while (Wire.available() && i < NUM_SLIDERS) {
    sliderValues[i++] = Wire.read();
  }
  updateSliderValues();

}
void requestEvent() {
    Wire.write(sliderValues, NUM_SLIDERS); 
}

void initTalking(){
    Wire.begin(I2C_SLAVE_ADDR); // Initialize as I2C slave
    Wire.onReceive(receiveEvent); // Register receive handler
    Wire.onRequest(requestEvent);
}


#endif