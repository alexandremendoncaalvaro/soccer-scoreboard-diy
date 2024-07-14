#pragma once

#include "TimeControl.h"
#include <HardwareSerial.h>

TimeControl timeControl(0);

// TimeControl::TimeControl(unsigned long timeInMillis) {
//         update_Time(timeInMillis);
// }

void TimeControl::update_Time(unsigned long timeInMillis) {
    int seconds = timeInMillis / 1000;
    second = seconds % 60;
    minute = (seconds % 3600) / 60;
    hour = seconds / 3600;

    h1 = hour / 10;
    h2 = hour % 10;
    m1 = minute / 10;
    m2 = minute % 10;
    s1 = second / 10;
    s2 = second % 10;    
    // Serial.print(m1);    
    // Serial.print(m2);
    // Serial.print(":");
    // Serial.print(s1);
    // Serial.print(s2);
}