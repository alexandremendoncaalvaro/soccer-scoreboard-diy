#pragma once

class TimeControl
{
private:
    int hour;
    int minute;
    int second;

public:
    int h1;
    int h2;
    int m1;
    int m2;
    int s1;
    int s2;
    TimeControl(unsigned long timeInMillis) {
        update_Time(timeInMillis);
    }

    void update_Time(unsigned long timeInMillis);
};

extern TimeControl timeControl;