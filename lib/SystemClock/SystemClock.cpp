#include "SystemClock.h"    

time_t SystemClock::getTime()
{
    auto currentTime = now();
    return currentTime;
}

SystemClock systemClock;