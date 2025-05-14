#include <Arduino.h>
#include <convolution.h>
#include <talking.h>

void setup() {
 
    Serial.begin(115200);
initSliderValues();
initTalking();
  
    Serial.println("I2C Slave Ready");

FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_PIXELS);
//FastLED.setCorrection(TypicalLEDStrip);  // or UncorrectedColor
FastLED.setBrightness(BRIGHTNESS);
}

void loop() {

generateNoiseFrame();

//applyMaskedConvolution(strongSharpenKernel, sharpenMask, 5, 5);
//applyMaskedConvolution(edgeKernel, edgeMask, 5, 7);
//applyMaskedConvolution(blurKernel,m1, 15, 15);

FastLED.show();

}