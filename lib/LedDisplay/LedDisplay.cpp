#include "LedDisplay.h"

void LedDisplay::set_LedColor(RGB color)
{
    _ledColor = color;
}

RGB LedDisplay::get_LedColor()
{
    return _ledColor;
}

LedDisplay ledDisplay;