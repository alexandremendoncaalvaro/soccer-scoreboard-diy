#pragma once

#include <FastLED.h>
#include "LedDisplay.h"
#include "TimeControl.h"

class ScoreboardClock
{
private:
    bool _debug = false;
    bool _showRTCClock = false;
    unsigned long _clockPrevTime = 0;
public:
    unsigned long currentMillis = millis();
    unsigned long prevTime = 0;
    unsigned long elapsedTime = 0;
    bool begin();
    void set_debug(bool debug) { _debug = debug; }
    bool started = false;
    bool paused = false;
    void startResumeTimer();
    void updateTime();
    void pauseTimer();
    void stopTimer();
    void setDisplayMode(bool showClock);
};

extern ScoreboardClock scoreboardClock;