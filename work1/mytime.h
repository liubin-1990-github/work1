#ifndef MYTIME_H
#define MYTIME_H


#include <QString>
class MyTime
{
public:
    MyTime();
    void inti(QString time);
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
public:
    void addSec();
    void addMin();
    void addHour();
    void addDay();
    void addMonth();
    void addYear();
    bool ifLeapYear(int y);
    bool operator ==(const MyTime &t);

    QString timeToString();


};

#endif // MYTIME_H
