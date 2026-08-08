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

    // Timer continua acumulando independente do modo de exibição
    if (started && !paused && (currentMillis - prevTime >= 1000))
    {
        elapsedTime += currentMillis - prevTime;
        prevTime = currentMillis;
        if (!_showRTCClock)
        {
            timeControl.update_Time(elapsedTime);
            ledDisplay.blinkDots();
            ledDisplay.set_Time();
        }
    }

    // Modo relógio: display atualizado com hora do RTC em paralelo
    if (_showRTCClock && (currentMillis - _clockPrevTime >= 1000))
    {
        _clockPrevTime = currentMillis;
        int h, m, s;
        if (systemClock.readTime(h, m, s))
        {
            Serial.printf("[CLOCK] RTC ok: %02d:%02d:%02d\n", h, m, s);
            unsigned long ms = ((unsigned long)h * 3600 + (unsigned long)m * 60 + s) * 1000UL;
            timeControl.update_Time(ms);
            ledDisplay.blinkDots();
            ledDisplay.set_Time();
        }
        else
        {
            Serial.println("[CLOCK] readTime() falhou");
        }
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
    if (showClock)
        _clockPrevTime = 0; // dispara atualização imediata do RTC
}
