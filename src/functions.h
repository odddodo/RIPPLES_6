#ifndef functions_h
#define functions_h

#include <FastLED.h>
#include <math.h>
#include <stdint.h>
#include <parameters.h>


int getLedIndex32(int x, int y) {
  const int panelWidth = 32;
  const int panelHeight = 8;
  int panel = y / panelHeight;
  int localY = y % panelHeight;
  int baseIndex = panel * panelWidth * panelHeight;
  int panelX = (panel % 2 == scramble1) ? x : (panelWidth - 1 - x);

  if (x % 2 == scramble2)
    return baseIndex + panelX * panelHeight + localY;
  else
    return baseIndex + panelX * panelHeight + (panelHeight - 1 - localY);
}
uint8_t awesomeSin8(uint16_t input, uint8_t amplitude = 127, uint8_t bias = 128, uint8_t phase = 0, uint8_t frequency = 1) {
    // Apply frequency and phase shift
    uint8_t angle = ((input * frequency) ) + phase;

    // Generate base sine wave (0–255), center is 128
    uint8_t rawSin = sin8(angle);

    // Scale amplitude around center (128), then add bias
    int16_t scaled = ((int16_t(rawSin) - 128) * amplitude) / 128 + bias;

    // Clamp result to 0–255
    if (scaled < 0) return 0;
    if (scaled > 255) return 255;
    return static_cast<uint8_t>(scaled);
}

void generateNoiseFrame() {
    static uint32_t t1 = 0, t2 = 0, t3 = 0; // Z axes for R/G/B noise
    
  
    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
      for (int x = 0; x < DISPLAY_WIDTH; x++) {
        uint16_t i = getLedIndex32(x, y);  

    
        // Use high-resolution 16-bit noise and scale it down
        uint8_t valR = inoise16(x * xScaleR, y * yScaleR, t1) >> 8;
        uint8_t valG = inoise16(x * xScaleG, y * yScaleG, t2) >> 8;
        uint8_t valB = inoise16(x * xScaleB, y * yScaleB, t3) >> 8;
  
int sinValR=awesomeSin8(valR,amp_R,bias_R,phase_R,sinFreqR);
int sinValG=awesomeSin8(valG,amp_G,bias_G,phase_G,sinFreqG);
int sinValB=awesomeSin8(valB,amp_B,bias_B,phase_B,sinFreqB);

        // Apply sin curve for visual effect (like your sineTable)
        //CRGB targetColor = CRGB(sin8(valR * sinFreqR), sin8(valG * sinFreqG) ,sin8(valB * sinFreqB));
        CRGB targetColor=CRGB(sinValR,sinValG,sinValB);
              // Apply low-pass filter: blend previous value with current
      leds[i] = blend(ledsPrev[i], targetColor, smoothing);  // 96 = smoother, lower = slower response
      ledsPrev[i] = leds[i];  // Store for next frame     
      }
    }   
    t1 += tScaleR;  // evolve time
    t2 += tScaleG;
    t3 += tScaleB;
  
  }

void generateNoisyMask(){
  static uint8_t tM1=0;
  for (int y = 0; y < DISPLAY_HEIGHT; y++) {
    for (int x = 0; x < DISPLAY_WIDTH; x++) {
      uint16_t i = getLedIndex32(x, y);  

      uint8_t msk1=inoise16(x * MxScale1, y * MyScale1, tM1) >> 8;
      
      CRGB targetMask=CRGB(sin8(msk1* sinFreqM),sin8(msk1* sinFreqM),sin8(msk1* sinFreqM));
      m1[i]=blend(m1_prev[i],targetMask,m_smoothing);
      m1_prev[i]=m1[i];
    }
  }
  tM1+=MtScale1;
}
#endif

