#include "SystemClock.h"

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

void SystemClock::printTime()
{
    tmElements_t tm;

    if (RTC.read(tm))
    {
        Serial.print("Ok, Time = ");
        printTwoDigits(tm.Hour);
        Serial.write(':');
        printTwoDigits(tm.Minute);
        Serial.write(':');
        printTwoDigits(tm.Second);
        Serial.print(", Date (D/M/Y) = ");
        Serial.print(tm.Day);
        Serial.write('/');
        Serial.print(tm.Month);
        Serial.write('/');
        Serial.print(tmYearToCalendar(tm.Year));
        Serial.println();
    }
    else
    {
        if (RTC.chipPresent())
        {
            Serial.println("The DS1307 is stopped.  Please run the SetTime");
            Serial.println("example to initialize the time and begin running.");
            Serial.println();
        }
        else
        {
            Serial.println("DS1307 read error!  Please check the circuitry.");
            Serial.println();
        }
        delay(9000);
    }
    delay(1000);
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

    if (_debug)
    {
        Serial.print(day);
        Serial.print("/");
        Serial.print(month);
        Serial.print("/");
        Serial.print(year);
        Serial.print(" ");
        Serial.print(hour);
        Serial.print(":");
        Serial.print(minute);
        Serial.print(":");
        Serial.println(second);
    }

    auto ret = RTC.write(timeElements);

    delay(1000);

    return ret;
}

SystemClock systemClock;