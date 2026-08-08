#include "SystemClock.h"

bool SystemClock::begin()
{
    tmElements_t tm;
    if (RTC.read(tm))
    {
        if (_debug)
        {
            Serial.print(F("[RTC] "));
            printTwoDigits(tm.Hour);
            Serial.print(':');
            printTwoDigits(tm.Minute);
            Serial.print(':');
            printTwoDigits(tm.Second);
            Serial.println();
        }
        return true;
    }

    if (RTC.chipPresent())
    {
        // DS1307 presente mas oscilador parado (CH bit set); limpa o bit escrevendo tempo padrão
        tmElements_t init = {};
        init.Year = 2024 - 1970;
        init.Month = 1;
        init.Day = 1;
        RTC.write(init);
        if (_debug)
            Serial.println(F("[RTC] DS1307 iniciado em 00:00 - sincronize via clock.html"));
    }
    else if (_debug)
        Serial.println(F("[RTC] DS1307 não encontrado no barramento I2C"));

    return true;
}

void SystemClock::printTwoDigits(int number)
{
    if (number >= 0 && number < 10)
    {
        Serial.write('0');
    }
    Serial.print(number);
}

bool SystemClock::printTime()
{
    tmElements_t tm;

    if (RTC.read(tm))
    {
        Serial.print(F("[RTC] Ok, Time = "));
        printTwoDigits(tm.Hour);
        Serial.print(F(":"));
        printTwoDigits(tm.Minute);
        Serial.print(F(":"));
        printTwoDigits(tm.Second);
        Serial.print(F(", Date (DD/MM/YYYY) = "));
        printTwoDigits(tm.Day);
        Serial.print(F("/"));
        printTwoDigits(tm.Month);
        Serial.print(F("/"));
        Serial.println(tmYearToCalendar(tm.Year));
    }
    else
    {
        if (RTC.chipPresent())
        {
            Serial.println(F("The DS1307 is stopped. Please run the SetTime"));
            Serial.println(F("example to initialize the time and begin running."));
                }
        else
        {
            Serial.println(F("DS1307 read error! Please check the circuitry."));
        }
        delay(9000);
        return false;
    }
    Serial.println();
    delay(1000);
    return true;
}

bool SystemClock::readTime(int& hour, int& minute, int& second)
{
    tmElements_t tm;
    if (!RTC.read(tm))
    {
        if (_debug)
        {
            if (RTC.chipPresent())
                Serial.println(F("[RTC] DS1307 parado - sincronize via clock.html"));
            else
                Serial.println(F("[RTC] DS1307 não encontrado"));
        }
        return false;
    }
    hour = tm.Hour;
    minute = tm.Minute;
    second = tm.Second;
    return true;
}

bool SystemClock::setDateTime(int year, int month, int day, int hour, int minute, int second)
{
    tmElements_t timeElements;

    timeElements.Year = year - 1970;
    timeElements.Month = month;
    timeElements.Day = day;

    timeElements.Hour = hour;
    timeElements.Minute = minute;
    timeElements.Second = second;

    return RTC.write(timeElements);
}

SystemClock systemClock;