#include "ScoreboardClock.h"

ScoreboardClock scoreboardClock;

bool ScoreboardClock::begin()
{
    Serial.println("Clock started!");
    startResumeTimer();
    return true;
}

void ScoreboardClock::startResumeTimer()
{
    if (_debug)
    {
        Serial.println("Timer started/ resumed.");
    }
    started = true;
    paused = false;
    updateTime();
}

void ScoreboardClock::updateTime()
{

    currentMillis = millis();

    if (started && !paused &&
        (currentMillis - prevTime >= 1000))
    {
        // if (_debug) { Serial.println("Atualizando o timer!"); }
        elapsedTime += currentMillis - prevTime;
        timeControl.update_Time(elapsedTime);
        prevTime = currentMillis;
        ledDisplay.blinkDots();
        ledDisplay.set_Time();
        // ledDisplay.markLedsDirty(); // Garante atualização do display do relógio
    }
}

void ScoreboardClock::pauseTimer()
{
    if (_debug)
    {
        Serial.println("Timer paused.");
    }
    paused = true;
}

void ScoreboardClock::stopTimer()
{
    if (_debug)
    {
        Serial.println("Timer stopped.");
    }
    started = false;
    elapsedTime = 0;
    timeControl.update_Time(0);
}
