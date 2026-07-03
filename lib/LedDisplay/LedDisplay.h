#pragma once

#include <Arduino.h>
// #define FASTLED_INTERRUPT_RETRY_COUNT 1
// #define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
#include "ScoreboardClock.h"
#include "TimeControl.h"

namespace Digits
{
    struct ValueRGB
    {
        byte r;
        byte g;
        byte b;
    };

    const byte SEVEN_SEGMENTS = 7;
    const byte LEDS_PER_SEGMENT = 3;
    const byte DOTS = 2;
    const byte MAX_SCORE = 99;
    const byte TOTAL_DIGITS = 8;
    const long DIGITS[] = {
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
}

class LedDisplay
{
private:
    bool _debug = false;
    CRGB _ledColorT1 = CRGB(255, 255, 255);
    CRGB _ledColorT2 = CRGB(255, 255, 255);
    CRGB _ledColorTm = CRGB(255, 255, 255);
    byte _ledBrightness = 100;
    byte _totalDigits = 8;
    byte _totalLeds = _totalDigits * Digits::SEVEN_SEGMENTS * Digits::LEDS_PER_SEGMENT + Digits::DOTS;
    CRGB leds[Digits::TOTAL_DIGITS * Digits::SEVEN_SEGMENTS * Digits::LEDS_PER_SEGMENT + Digits::DOTS];
    unsigned long _updatesPerSecond = 100;
    unsigned long _previousMillis = 0;

    void setAllColors(CRGB ledColor);
    void setSeparatedColors();
    byte scoreTeamA = 0;
    byte scoreTeamB = 0;

    byte get_FirstDigit(byte score);
    byte get_SecondDigit(byte score);
    void testLeds();

public:
    void set_debug(bool debug) { _debug = debug; }

    bool begin();
    bool begin(uint8_t ledPin);

    void set_LedColor(Digits::ValueRGB color, int id);
    Digits::ValueRGB get_LedColor(int id);

    void set_LedBrightness(byte brightness);
    byte get_LedBrightness();

    void updateLeds();

    void displayNumber(byte number, byte segment, CRGB color, boolean isFirstDigit);

    void set_ScoreTeamA(byte newScore);
    byte get_ScoreTeamA();
    void set_ScoreTeamB(byte newScore);
    byte get_ScoreTeamB();

    bool dotsAreOff = true;
    void blinkDots();
    void set_Time();
};

extern LedDisplay ledDisplay;