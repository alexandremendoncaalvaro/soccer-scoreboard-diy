#include "LedDisplay.h"

using namespace Digits;

bool LedDisplay::begin()
{
    return begin(D3);
}

bool LedDisplay::begin(uint8_t ledPin)
{
    delay(3000); // power-up safety delay
    // FastLED.addLeds pin needs to be declare as a constant
    switch (ledPin)
    {
    case D3:
        FastLED.addLeds<WS2812B, D3, GRB>(leds, _totalLeds).setCorrection(TypicalLEDStrip);
        break;
    case D4:
        FastLED.addLeds<WS2812B, D4, GRB>(leds, _totalLeds).setCorrection(TypicalLEDStrip);
        break;
    case D5:
        FastLED.addLeds<WS2812B, D5, GRB>(leds, _totalLeds).setCorrection(TypicalLEDStrip);
        break;
    case D6:
        FastLED.addLeds<WS2812B, D6, GRB>(leds, _totalLeds).setCorrection(TypicalLEDStrip);
        break;
    case D7:
        FastLED.addLeds<WS2812B, D7, GRB>(leds, _totalLeds).setCorrection(TypicalLEDStrip);
        break;
    default:
        if (_debug)
        {
            Serial.println(F("[LED] Invalid Led Pin!"));
            Serial.println();
        }
        return false;
        break;
    }
    // FastLED.setBrightness(_ledBrightness);
    // setAllColors(CRGB::Black);
    // updateLeds();
    return true;
}

void LedDisplay::setAllColors(CRGB ledColor)
{
    for (int i = 0; i < _totalLeds; i++)
    {
        leds[i] = ledColor;
    }
}

void LedDisplay::setSeparatedColors()
{    
    displayNumber(get_ScoreTeamA(), 0, _ledColorT1);
    //displayNumber(get_ScoreTeamB(), 1, _ledColorT2);
    //displayNumber(get_Time(), 2, _ledColorTm);
    
    // for (int i = 0; i < 10; i++)
    // {
    //     leds[i] = _ledColorT1;
    // }
    // for (int i = 10; i < 20; i++)
    // {
    //     leds[i] = _ledColorT2;
    // }
    // for (int i = 20; i < _totalLeds; i++)
    // {
    //     leds[i] = _ledColorTm;
    // }
}

void LedDisplay::set_LedColor(ValueRGB color, int id)
{
    switch (id)
    {
    case 1:
        _ledColorT1 = CRGB(color.r, color.g, color.b);
        break;
    case 2:
        _ledColorT2 = CRGB(color.r, color.g, color.b);
        break;
    case 3:
        _ledColorTm = CRGB(color.r, color.g, color.b);
        break;
    default:
        break;
    }
    updateLeds();
}

ValueRGB LedDisplay::get_LedColor(int id)
{
    auto ledColor = CRGB(255, 255, 255);
    switch (id)
    {
    case 1:
        ledColor = _ledColorT1;
        break;
    case 2:
        ledColor = _ledColorT2;
        break;
    case 3:
        ledColor = _ledColorTm;
        break;
    default:
        break;
    }
    ValueRGB color = {ledColor.r,
                      ledColor.g,
                      ledColor.b};
    return color;
}

void LedDisplay::set_LedBrightness(byte brightness)
{
    _ledBrightness = brightness;
    updateLeds();
}

byte LedDisplay::get_LedBrightness()
{
    return _ledBrightness;
}

void LedDisplay::updateLeds()
{
    unsigned long currentMillis = millis();
    if (currentMillis - _previousMillis >= (1000 / _updatesPerSecond))
    {
        _previousMillis = currentMillis;
        FastLED.setBrightness(_ledBrightness);
        setSeparatedColors();
        FastLED.show();
    }
    yield();
}

void LedDisplay::displayNumber(byte number, byte segment, CRGB color)
{
    /*
      __ __ __        __ __ __          __ __ __        __ __ __
    __        __    __        __      __        __    __        __
    __        __    __        __      __        __    __        __
    __        __    __        __      __        __    __        __
      __ __ __        __ __ __          __ __ __        __ __ __
    __       149    __       128      __       107    __        86
    __        __    __        __      __        __    __        __
    __        __    __        __      __        __    __        __
      __ __ __       __ __ __           __ __ __        __ __ __

      __ __ __        __ __ __          __ __ __        12 13 14
    __        __    __        __      __        __    11        15
    __        __    __        __      __        __    10        16
    __        __    __        __  42  __        __    _9        17
      __ __ __        __ __ __          __ __ __        20 19 18
    __        65    __        44  43  __        21    _8        _0
    __        __    __        __      __        __    _7        _1
    __        __    __        __      __        __    _6        _2
      __ __ __       __ __ __           __ __ __        _5 _4 _3
   */
    // top segment from left to right:    7, 6, 5, 4
    // bottom segment from left to right: 3, 2, 1, 0

    byte startindex = segment < 2 ? (segment * 21) : (segment * 21) + 2;

    for (byte i = 0; i < 21; i++)
    {
        yield();
        leds[i + startindex] = ((DIGITS[number] & 1 << i) == 1 << i) ? color : CRGB::Black;
    }
}

void LedDisplay::set_ScoreTeamA(byte score)
{
    scoreTeamA = score;
}

void LedDisplay::set_ScoreTeamB(byte score)
{
    scoreTeamB = score;
}

byte LedDisplay::get_ScoreTeamA()
{
    return scoreTeamA;
}

byte LedDisplay::get_ScoreTeamB()
{
    return scoreTeamB;
}

LedDisplay ledDisplay;