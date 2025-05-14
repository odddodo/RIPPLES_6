#ifndef parameters_h
#define parameters_h

#include <FastLED.h>



#define DISPLAY_WIDTH 32
#define DISPLAY_HEIGHT 32
#define NUM_PIXELS (DISPLAY_WIDTH * DISPLAY_HEIGHT)
#define LED_PIN 19
#define COLOR_ORDER RBG
#define CHIPSET WS2812B
#define BRIGHTNESS 128

CRGB leds[NUM_PIXELS];
CRGB ledsPrev[NUM_PIXELS];  // buffer to hold previous smoothed values

CRGB m1[NUM_PIXELS];
CRGB m1_prev[NUM_PIXELS];

uint8_t sharpenMask[NUM_PIXELS];
uint8_t edgeMask[NUM_PIXELS];
uint8_t blurMaskBuffer[NUM_PIXELS];

int sinFreqR = 3;
int sinFreqG = 15;
int sinFreqB = 7;

uint16_t xScale1 = 100, yScale1 = 100;
uint16_t xScale2 = 3000, yScale2 = 3000;
uint16_t xScale3 = 9000, yScale3 = 9000;

int tScale1=10;
int tScale2=30;
int tScale3=10;

int smoothing=96;

int sinFreqM = 2;
uint16_t MxScale1=300, MyScale1=300;
int MtScale1=150;
int m_smoothing=64;

int scramble1=0;
int scramble2=0;




#endif