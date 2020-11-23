#include "LedDisplay.h"

void LedDisplay::begin()
{
    delay(3000); // power-up safety delay
    FastLED.addLeds<WS2812B, D7, GRB>(leds, _totalLeds).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(_ledBrightness);
    setAllColors(CRGB::Black);
    updateLeds();
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
    for (int i = 0; i < 10; i++)
    {
        leds[i] = _ledColorT1;
    }
    for (int i = 10; i < 20; i++)
    {
        leds[i] = _ledColorT2;
    }
    for (int i = 20; i < _totalLeds; i++)
    {
        leds[i] = _ledColorTm;
    }
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

LedDisplay ledDisplay;