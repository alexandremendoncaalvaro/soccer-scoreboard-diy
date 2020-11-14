#include "LedDisplay.h"

void LedDisplay::begin()
{
    delay(3000); // power-up safety delay
    FastLED.addLeds<WS2812B, D7, GRB>(leds, _totalLeds).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(_ledBrightness);
    allColors(CRGB::Black);
    updateLeds();
}

void LedDisplay::allColors(CRGB ledColor)
{
    for (int i = 0; i < _totalLeds; i++)
    {
        leds[i] = ledColor;
    }
}

void LedDisplay::set_LedColor(ValueRGB color)
{
    _ledColor = CRGB(color.r, color.g, color.b);
    updateLeds();
}

ValueRGB LedDisplay::get_LedColor()
{
    ValueRGB color = {_ledColor.r,
                      _ledColor.g,
                      _ledColor.b};
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
        allColors(_ledColor);
        FastLED.show();
    }
    yield();
}

LedDisplay ledDisplay;