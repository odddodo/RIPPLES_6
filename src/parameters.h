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

uint8_t sinFreqR = 3;
uint8_t sinFreqG = 15;
uint8_t sinFreqB = 7;

uint8_t amp_R=255;
uint8_t amp_G=255;
uint8_t amp_B=255;

uint8_t bias_R =0;
uint8_t bias_G =0;
uint8_t bias_B =0;

uint8_t phase_R=0;
uint8_t phase_G=0;
uint8_t phase_B=0;

uint16_t xScaleR= 100, yScaleR= 100;
uint16_t xScaleG = 3000, yScaleG= 3000;
uint16_t xScaleB = 9000, yScaleB = 9000;

int tScaleR=10;
int tScaleG=30;
int tScaleB=10;

int smoothing=96;

int sinFreqM = 2;
uint16_t MxScale1=300, MyScale1=300;
int MtScale1=150;
int m_smoothing=64;

int scramble1=0;
int scramble2=0;




#endif