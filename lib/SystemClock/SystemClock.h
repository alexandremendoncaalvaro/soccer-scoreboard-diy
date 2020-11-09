#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

class SystemClock
{
private:
    bool _debug = false;
    void printTwoDigits(int number);
public:
    void set_debug(bool debug);
    time_t getTime();
    void printTime();
    bool setDateTime(int year, int month, int day, int hour, int minute, int second);
};

extern SystemClock systemClock;