#pragma once

#include <Arduino.h>
#include <FastLED.h>

struct ValueRGB
{
    byte r;
    byte g;
    byte b;
};

const long NUMBERS_SHAPE[] = {
    0b000111111111111111111, // [0] 0
    0b000111000000000000111, // [1] 1
    0b111111111000111111000, // [2] 2
    0b111111111000000111111, // [3] 3
    0b111111000111000000111, // [4] 4
    0b111000111111000111111, // [5] 5
    0b111000111111111111111, // [6] 6
    0b000111111000000000111, // [7] 7
    0b111111111111111111111, // [8] 8
    0b111111111111000111111, // [9] 9
    0b000000000000000000000, // [10] off
    0b111111111111000000000, // [11] degrees symbol
    0b000000111111111111000, // [12] C(elsius)
    0b111000111111111000000, // [13] F(ahrenheit)
};

class LedDisplay
{
private:
    CRGB _ledColor = CRGB(255, 255, 255);
    byte _ledBrightness = 100;
    byte _totalLeds = 30;
    CRGB* leds = new CRGB[_totalLeds];
    unsigned long _updatesPerSecond = 100;
    unsigned long _previousMillis = 0;

    void allColors(CRGB ledColor);
public:
    void begin();
    void set_LedColor(ValueRGB color);
    ValueRGB get_LedColor();

    void set_LedBrightness(byte brightness);
    byte get_LedBrightness();

    void updateLeds();
};

extern LedDisplay ledDisplay;