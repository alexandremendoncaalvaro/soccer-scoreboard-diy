#include "SystemClock.h"

bool SystemClock::begin(){
    return printTime();
}

time_t SystemClock::getTime()
{
    auto currentTime = now();
    return currentTime;
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

bool SystemClock::setDateTime(int year, int month, int day, int hour, int minute, int second)
{
    tmElements_t timeElements;

    timeElements.Year = year - 1970;
    timeElements.Month = month;
    timeElements.Day = day;

    timeElements.Hour = hour;
    timeElements.Minute = minute;
    timeElements.Second = second;

    auto ret = RTC.write(timeElements);

    delay(1000);

    return ret;
}

SystemClock systemClock;