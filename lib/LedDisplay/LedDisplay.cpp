#include "LedDisplay.h"

using namespace Digits;

bool LedDisplay::begin()
{
    bool initiated = begin(D3);
    testLeds();
    return initiated;
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
    setAllColors(CRGB::Black);
    FastLED.setBrightness(0);
    FastLED.show();
    return true;
}

void LedDisplay::testLeds()
{
    Serial.print("Total Leds: ");
    Serial.println(_totalLeds);

    FastLED.setBrightness(_ledBrightness);
    for (int i = 0; i < _totalLeds; i++)
    {
        leds[i] = CRGB::Red;
        FastLED.show();
        delay(88);
    }

    Serial.println("Tests were finished!");
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
    byte score = get_ScoreTeamA();
    byte firstDigit = get_FirstDigit(score);
    byte secondDigit = get_SecondDigit(score);
    displayNumber(secondDigit, 6, _ledColorT1, false);
    displayNumber(firstDigit, 7, _ledColorT1, true);

    score = get_ScoreTeamB();
    firstDigit = get_FirstDigit(score);
    secondDigit = get_SecondDigit(score);
    displayNumber(secondDigit, 4, _ledColorT2, false);
    displayNumber(firstDigit, 5, _ledColorT2, true);

    scoreboardClock.updateTime();
}

byte LedDisplay::get_FirstDigit(byte score)
{
    return score / 10 % 10;
}

byte LedDisplay::get_SecondDigit(byte score)
{
    return score % 10;
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

void LedDisplay::displayNumber(byte number, byte segment, CRGB color, boolean blackIfZero)
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

    color = blackIfZero && number == 0 ? CRGB::Black : color;
    byte ledsPerDigit = Digits::LEDS_PER_SEGMENT * Digits::SEVEN_SEGMENTS;
    byte startindex = segment < 2 ? (segment * ledsPerDigit) : (segment * ledsPerDigit) + Digits::DOTS;

    for (byte i = 0; i < ledsPerDigit; i++)
    {
        yield();
        leds[i + startindex] = ((DIGITS[number] & 1 << i) == 1 << i) ? color : CRGB::Black;
    }
}

void LedDisplay::set_ScoreTeamA(byte score)
{
    scoreTeamA = score > Digits::MAX_SCORE ? Digits::MAX_SCORE : score;
    updateLeds();
}

void LedDisplay::set_ScoreTeamB(byte score)
{
    scoreTeamB = score > Digits::MAX_SCORE ? Digits::MAX_SCORE : score;
    updateLeds();
}

byte LedDisplay::get_ScoreTeamA()
{
    return scoreTeamA;
}

byte LedDisplay::get_ScoreTeamB()
{
    return scoreTeamB;
}

void LedDisplay::blinkDots()
{
    dotsAreOff = !dotsAreOff;
    CRGB color = dotsAreOff ? CRGB::Black : _ledColorTm;
    leds[42] = color;
    leds[43] = color;
    yield();
}

void LedDisplay::set_Time()
{
    // if (_debug) {
    //     Serial.print(timeControl.h1);
    //     Serial.print(timeControl.h2);
    //     Serial.print(":");
    //     Serial.print(timeControl.m1);
    //     Serial.print(timeControl.m2);
    //     Serial.print(":");
    //     Serial.print(timeControl.s1);
    //     Serial.println(timeControl.s2);
    // }

    if (timeControl.h1 > 0 || timeControl.h2 > 0)
    {
        displayNumber(timeControl.h1, 3, _ledColorTm, true);
        displayNumber(timeControl.h2, 2, _ledColorTm, false);
        displayNumber(timeControl.m1, 1, _ledColorTm, false);
        displayNumber(timeControl.m2, 0, _ledColorTm, false);
    }
    else
    {
        displayNumber(timeControl.m1, 3, _ledColorTm, true);
        displayNumber(timeControl.m2, 2, _ledColorTm, false);
        displayNumber(timeControl.s1, 1, _ledColorTm, false);
        displayNumber(timeControl.s2, 0, _ledColorTm, false);
    }
    yield();
}

LedDisplay ledDisplay;