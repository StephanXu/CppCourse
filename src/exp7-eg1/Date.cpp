#include <iostream>
#include <cassert>
#include "Date.h"
//列举每个月的天数 : 为符合习惯, 用月份作为下标
int Date::nDaysofMonth[13] = {0,
                              31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
Date::Date(int y, int m, int d)
{
    SetDate(y, m, d);
}
Date::Date(const Date &d)
{
    if (this != &d)
    {
        year = d.year;
        month = d.month;
        day = d.day;
    }
}
Date &Date::operator=(const Date &rhs)
{
    if (this != &rhs)
    {
        year = rhs.year;
        month = rhs.month;
        day = rhs.day;
    }
    return *this;
}
bool Date::IsLeapYear(int y)
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}
int Date::DaysOfThisYear(int y)
{ //该年的总天数
    if (IsLeapYear(y))
        return 366;
    else
        return 365;
}
void Date::SetDate(int y, int m, int d)
{
    year = y >= YearBase ? y : YearBase;       //设置年份
    month = m >= 1 && m <= 12 ? m : MonthBase; //设置月份

    this->LeapYearEnabled(); //考虑间年的影响
    day = d >= 1 && d <= nDaysofMonth[month] ? d : DayBase;
}
void Date::LeapYearEnabled() const
{
    if (IsLeapYear(year))     //若是间年
        nDaysofMonth[2] = 29; //设为29天
    else
        nDaysofMonth[2] = 28; //仍改回28天
}
int Date::Date2Days() const
{
    this->LeapYearEnabled(); //考虑间年的影响

    int s = 0;
    // 累加求和, 先初始化为0
    for (int m = 1; m < month; ++m)
        s += nDaysofMonth[m]; //再计算经过整月的天数
    for (int y = YearBase; y < year; ++y)
        s += DaysOfThisYear(y); //最后计算经过整年的天数
    return s;
}
Date Date::Days2Date(int n)
{
    Date d;
    int y = YearBase;
    while (n >= DaysOfThisYear(y))
    {                               //判断n是否超过整年的天数
        n -= DaysOfThisYear(y);     //从中去除之
        ++y;                        //得到经过的年数
        if (n == DaysOfThisYear(y)) //若剩下的天数刚好够一整年
            break;                  //恰好为年末,不用再减
    }
    d.year = y;          //y为所求年份
    d.LeapYearEnabled(); //考虑间年的影响

    int m = 1;
    while (n >= nDaysofMonth[m])
    {                             //判断剩余天数是否超过整月
        n -= nDaysofMonth[m];     //从中去除之
        ++m;                      //得到经过的月数
        if (n == nDaysofMonth[m]) //若剩下的天数刚好够一个月
            break;                //恰好为月末,不用再减
    }
    d.month = m; //得到经过的月份
    d.day = n;   //剩余则为经过的天数
    return d;    //返回得到的当前日期对象
}
void Date::Print() const
{
    std::cout << this->year << "-" << this->month
              << "-" << this->day << std::endl;
}