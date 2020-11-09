#pragma once

#include <Arduino.h>

struct RGB
{
    byte r;
    byte g;
    byte b;
};

class LedDisplay
{
private:
    RGB _ledColor = {255, 255, 255};
public:
    void set_LedColor(RGB color);
    RGB get_LedColor();
};

extern LedDisplay ledDisplay;