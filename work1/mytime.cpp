#include "mytime.h"

MyTime::MyTime()
{

}

void MyTime::inti(QString time)
{
    qlonglong t=time.toLongLong();
    year=t/10000000000;
    month=(t-year*10000000000)/100000000;
    day=(t-year*10000000000-month*100000000)/1000000;
    second=t%100;
    minute=(t%10000-second)/100;
    hour=(t%1000000-minute*100-second)/10000;
}



void MyTime::addSec()
{
    second++;
    if(second>59)
    {
        second=0;
        addMin();
    }
}

void MyTime::addMin()
{
    minute++;
    if(minute>59)
    {
        minute=0;
        addHour();
    }
}

void MyTime::addHour()
{
    hour++;
    if(hour>23)
    {
        hour=0;
        addDay();
    }
}

void MyTime::addDay()
{
    day++;

    if(ifLeapYear(year) &&month==2)
    {
        if(day>29)
        {
            day=0;
            addMonth();
        }
    }
    else
    {
        if(!ifLeapYear(year) && month==2)
        {
            if(day>28)
            {
                day=0;
                addMonth();
            }
        }
        else if(month==1 ||
                month==3 ||
                month==5 ||
                month==7 ||
                month==9 ||
                month==10 ||
                month==12 )
        {
            if(day>31)
            {
                day=0;
                addMonth();
            }
        }
        else if(month==4 ||
                month==6 ||
                month==8 ||
                month==11)
        {
            if(day>30)
            {
                day=0;
                addMonth();
            }
        }
    }
}

void MyTime::addMonth()
{
    month++;
    if(month>12)
    {
        month=0;
        addYear();
    }
}

void MyTime::addYear()
{
    year++;
}

bool MyTime::ifLeapYear(int y)
{
    if( ( y%4==0 && y%100 != 0) || y%400==0)
    {
        return true;
    }
    return false;
}

bool MyTime::operator ==(const MyTime &t)
{
    if(year==t.year && month == t.month
            &&day==t.day&&hour==t.hour
            &&minute==t.minute&&second==t.second)
    {
        return true;
    }
    return false;
}







QString MyTime::timeToString()
{
    //20201221162222
    qlonglong num=year*10000000000+month*100000000+day*1000000+hour*10000+minute*100+second;
    return QString::number(num);
}

