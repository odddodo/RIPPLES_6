#ifndef convolution_h
#define convolution_h

#include <FastLED.h>
#include <parameters.h>
#include <functions.h>

#define CLAMP(v) ((v) < 0 ? 0 : ((v) > 255 ? 255 : (v)))

uint8_t maskBuffer[NUM_PIXELS];   // Grayscale mask: 0–255
uint8_t prevMask[NUM_PIXELS];     // For temporal smoothing
uint8_t blurTemp[NUM_PIXELS];     // Temporary buffer for blur passes


const int8_t blurKernel[3][3] = {
  {1, 1, 1},
  {1, 1, 1},
  {1, 1, 1}
};

const int8_t edgeKernel[3][3] = {
  {-1, -1, -1},
  {-1,  8, -1},
  {-1, -1, -1}
};

const int8_t strongSharpenKernel[3][3] = {
  { 0, -1,  0},
  {-1,  9, -1},
  { 0, -1,  0}
};





  void applyMaskedConvolution(const int8_t kernel[3][3],  CRGB* mask, int divisor = 1, int bias = 0) {
    CRGB temp[DISPLAY_HEIGHT][DISPLAY_WIDTH];
    CRGB source[DISPLAY_HEIGHT][DISPLAY_WIDTH];
  
    // Copy current LED state
    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
      for (int x = 0; x < DISPLAY_WIDTH; x++) {
        source[y][x] = leds[getLedIndex32(x, y)];
      }
    }
  
    // Apply convolution
    for (int y = 0; y < DISPLAY_HEIGHT ; y++) {
      for (int x = 0; x < DISPLAY_WIDTH ; x++) {
        int idx = getLedIndex32(x, y);
        uint8_t blendAmount = mask[idx].r;  // Smooth mask value (0–255)
  
        int sumR = 0, sumG = 0, sumB = 0;
        for (int ky = -1; ky <= 1; ky++) {
          for (int kx = -1; kx <= 1; kx++) {
            CRGB neighbor = source[y + ky][x + kx];
            int kVal = kernel[ky + 1][kx + 1];
            sumR += neighbor.r * kVal;
            sumG += neighbor.g * kVal;
            sumB += neighbor.b * kVal;
          }
        }
  
        CRGB convolved;
        convolved.r = CLAMP((sumR / divisor) + bias);
        convolved.g = CLAMP((sumG / divisor) + bias);
        convolved.b = CLAMP((sumB / divisor) + bias);
  
        // Blend based on mask intensity
        temp[y][x] = blend(source[y][x], convolved, blendAmount);
      }
    }
  
    // Copy edges unchanged
    for (int x = 0; x < DISPLAY_WIDTH; x++) {
      temp[0][x] = source[0][x];
      temp[DISPLAY_HEIGHT - 1][x] = source[DISPLAY_HEIGHT - 1][x];
    }
    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
      temp[y][0] = source[y][0];
      temp[y][DISPLAY_WIDTH - 1] = source[y][DISPLAY_WIDTH - 1];
    }
  
    // Write result back to LED array
    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
      for (int x = 0; x < DISPLAY_WIDTH; x++) {
        leds[getLedIndex32(x, y)] = temp[y][x];
      }
    }
  }

#endif