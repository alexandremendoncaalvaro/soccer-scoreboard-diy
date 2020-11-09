#include "LedDisplay.h"

void LedDisplay::set_LedColor(RGB color)
{
    _ledColor = color;
}

RGB LedDisplay::get_LedColor()
{
    return _ledColor;
}

void LedDisplay::set_LedBrightness(byte brightness)
{
    _ledBrightness = brightness;
}

byte LedDisplay::get_LedBrightness()
{
    return _ledBrightness;
}
LedDisplay ledDisplay;