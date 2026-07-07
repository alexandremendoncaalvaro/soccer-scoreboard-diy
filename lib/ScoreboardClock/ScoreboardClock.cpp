#include "ScoreboardClock.h"
#include "SystemClock.h"

ScoreboardClock scoreboardClock;

bool ScoreboardClock::begin()
{
    Serial.println("Clock started!");
    ledDisplay.set_Time();
    return true;
}

void ScoreboardClock::startResumeTimer()
{
    if (_debug)
        Serial.println("Timer started/resumed.");
    started = true;
    paused = false;
    prevTime = millis();
}

void ScoreboardClock::updateTime()
{
    currentMillis = millis();

    if (_showRTCClock)
    {
        if (currentMillis - prevTime >= 1000)
        {
            int h, m, s;
            if (systemClock.readTime(h, m, s))
            {
                unsigned long ms = ((unsigned long)h * 3600 + (unsigned long)m * 60 + s) * 1000UL;
                timeControl.update_Time(ms);
                prevTime = currentMillis;
                ledDisplay.blinkDots();
                ledDisplay.set_Time();
            }
        }
        return;
    }

    if (started && !paused && (currentMillis - prevTime >= 1000))
    {
        elapsedTime += currentMillis - prevTime;
        timeControl.update_Time(elapsedTime);
        prevTime = currentMillis;
        ledDisplay.blinkDots();
        ledDisplay.set_Time();
    }
}

void ScoreboardClock::pauseTimer()
{
    if (_debug)
        Serial.println("Timer paused.");
    paused = true;
}

void ScoreboardClock::stopTimer()
{
    if (_debug)
        Serial.println("Timer stopped.");
    started = false;
    elapsedTime = 0;
    timeControl.update_Time(0);
    ledDisplay.set_Time();
}

void ScoreboardClock::setDisplayMode(bool showClock)
{
    _showRTCClock = showClock;
    // prevTime = 0 → clock mode: dispara atualização imediata
    // prevTime = millis() → timer mode: evita absorver o tempo em modo relógio
    prevTime = showClock ? 0 : millis();
}
