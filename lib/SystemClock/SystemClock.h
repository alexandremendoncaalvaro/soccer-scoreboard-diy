#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

class SystemClock
{
private:

public:
    time_t getTime();
};

extern SystemClock systemClock;