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
    byte _ledBrightness = 100;
public:
    void set_LedColor(RGB color);
    RGB get_LedColor();

    void set_LedBrightness(byte brightness);
    byte get_LedBrightness();
};

extern LedDisplay ledDisplay;