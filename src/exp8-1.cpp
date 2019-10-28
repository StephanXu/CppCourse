/**
 * @file exp8-1.cpp
 * @author Xu Zihan (stephanxu@foxmail.com)
 * @brief Experiment 8. Item 1
 * @version 0.1
 * @date 2019-10-28
 * @copyright Copyright (c) 2019
 */
#include <iostream>
#include <sstream>
#include <cassert>
#include <memory>
#include <cmath>
#include <ctime>
#include <cstring>

class Date
{
private:
    int year, month, day;

private:
    //以下定义计算的基准,即从1970年1月1日开始
    enum
    {
        YearBase = 1970
    };
    enum
    {
        MonthBase = 1
    };
    enum
    {
        DayBase = 1
    };
    static int nDaysofMonth[13];

    void LeapYearEnabled() const
    {
        if (IsLeapYear(year))     //若是间年
            nDaysofMonth[2] = 29; //设为29天
        else
            nDaysofMonth[2] = 28; //仍改回28天
    }

    /**
     * @brief Get the Tm object
     * @return struct tm tm object
     */
    struct tm GetTm() const
    {
        struct tm tmDate;
        memset(&tmDate, 0, sizeof(tm));
        tmDate.tm_mday = day;
        tmDate.tm_mon = month - 1;
        tmDate.tm_year = year - 1900;
        tmDate.tm_isdst = -1;
        mktime(&tmDate);
        return tmDate;
    }

    /**
     * @brief Get the Tm object's pointer
     * @return std::shared_ptr<struct tm> pointer
     */
    std::shared_ptr<struct tm> GetTmPtr() const
    {
        std::shared_ptr<struct tm> tmDate = std::make_shared<struct tm>();
        memset(tmDate.get(), 0, sizeof(tm));
        tmDate->tm_mday = day;
        tmDate->tm_mon = month - 1;
        tmDate->tm_year = year - 1900;
        tmDate->tm_isdst = -1;
        mktime(tmDate.get());
        return tmDate;
    }

public:
    //-----------------------------------------------------------
    // Original function

    Date(int y = YearBase, int m = MonthBase, int d = DayBase)
    {
        SetDate(y, m, d);
    }
    Date(const Date &d)
    {
        if (this != &d)
        {
            year = d.year;
            month = d.month;
            day = d.day;
        }
    }
    Date &operator=(const Date &rhs)
    {
        if (this != &rhs)
        {
            year = rhs.year;
            month = rhs.month;
            day = rhs.day;
        }
        return *this;
    }
    void SetDate(int y, int m, int d)
    {
        year = y >= YearBase ? y : YearBase;       //设置年份
        month = m >= 1 && m <= 12 ? m : MonthBase; //设置月份

        this->LeapYearEnabled(); //考虑间年的影响
        day = d >= 1 && d <= nDaysofMonth[month] ? d : DayBase;
    }
    void Print() const
    {
        std::cout << this->year << "-" << this->month
                  << "-" << this->day << std::endl;
    }
    static bool IsLeapYear(int y)
    {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }
    static int DaysOfThisYear(int y)
    { //该年的总天数
        if (IsLeapYear(y))
            return 366;
        else
            return 365;
    }
    int Date2Days() const
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
    static Date Days2Date(int n)
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

    //-----------------------------------------------------------
    // Added function

    /**
     * @brief Build a string according format
     * Examples * 
     *      M/d/yy          2/29/12
     *      MM/dd/yyyy      02/29/2012
     *      MMMM dd, yyyy   February 29, 2012
     * @param format string format
     * @return std::string result
     */
    std::string ToString(const std::string format = "MM/dd/yyyy") const
    {
        std::string res;
        int count = 0;
        char lastChar = 0;
        auto Fill{[](std::string &refOutput, int &count, int oprParam) {
            while (std::pow(10, count) <= oprParam)
            {
                refOutput.insert(refOutput.begin(),
                                 '0' + static_cast<int>(oprParam / std::pow(10, count)) % 10);
                count++;
            }
        }};
        for (auto it = format.rbegin(); it != format.rend(); ++it)
        {
            if (*it != lastChar)
            {
                switch (lastChar)
                {
                case 'y':
                    Fill(res, count, year);
                    break;
                case 'd':
                    Fill(res, count, day);
                    break;
                case 'M':
                    Fill(res, count, month);
                    break;
                }
                lastChar = *it;
                count = 0;
            }
            switch (*it)
            {
            case 'y':
                res.insert(res.begin(), '0' + static_cast<int>(year / std::pow(10, count)) % 10);
                break;
            case 'd':
                res.insert(res.begin(), '0' + static_cast<int>(day / std::pow(10, count)) % 10);
                break;
            case 'M':
            {
                static const std::string monthName[]{
                    "January", "February", "March", "April", "May", "June",
                    "July", "August", "September", "October", "November",
                    "December"};
                if (3 == count)
                {
                    res.erase(0, 3);
                    res.insert(0, monthName[month - 1]);
                    break;
                }
                res.insert(res.begin(), '0' + static_cast<int>(month / std::pow(10, count)) % 10);
                break;
            }
            default:
                res.insert(res.begin(), *it);
                break;
            }
            ++count;
        }
        switch (lastChar)
        {
        case 'y':
            Fill(res, count, year);
            break;
        case 'd':
            Fill(res, count, day);
            break;
        case 'M':
            Fill(res, count, month);
            break;
        }
        return res;
    }

    /**
     * @brief Get an object pointing to today's date
     * @return Date object pointing to today's date
     */
    static Date Today()
    {
        time_t now;
        time(&now);
        struct tm *tmNow{localtime(&now)};
        return Date(tmNow->tm_year + 1900, tmNow->tm_mon + 1, tmNow->tm_mday);
    }

    /**
     * @brief Set current object to today
     * @return Date& Reference of current object
     */
    Date &SetToday()
    {
        *this = Today();
        return *this;
    }

    /**
     * @brief Day number within year
     * @return int day number
     */
    int DayInYear() const
    {
        return GetTm().tm_yday + 1;
    }

    /**
     * @brief Week number within year
     * Refer to ISO-8601: The definition for week 01 is the week with the 
     * Gregorian year's first Thursday in it.
     * @return int week number
     */
    int WeekInYear() const
    {
        char buf[10]{};
        strftime(buf, sizeof(buf), "%W", GetTmPtr().get());
        return atoi(buf) + 1;
    }

    /**
     * @brief Set to advance day
     * @return Date& Reference of current object
     */
    Date &AdvanceDay()
    {
        LeapYearEnabled();
        if (++day > nDaysofMonth[month])
        {
            day = 1;
            if (++month > 12)
            {
                month -= 12;
                ++year;
            }
        }
        return *this;
    }

    /**
     * @brief Advance number of days
     * @param n number of days
     * @return Date& Reference of current object
     */
    Date &AdvanceDay(unsigned int n)
    {
        for (; n > 0; --n)
            AdvanceDay();
        return *this;
    }

    /**
     * @brief Set to previous day
     * @return Date& Reference of current object
     */
    Date &PrevDay()
    {
        LeapYearEnabled();
        if (--day < 0)
        {
            day += nDaysofMonth[month - 1];
            if (--month < 0)
            {
                month = 12;
                --year;
            }
        }
        return *this;
    }

    /**
     * @brief Prev number of days
     * @param n number of days
     * @return Date& Reference of current object
     */
    Date &PrevDay(unsigned int n)
    {
        for (; n > 0; --n)
            PrevDay();
        return *this;
    }

    /**
     * @brief The number of days between two dates
     * @param lhs a date
     * @param rhs another date
     * @return int The number of days
     */
    static int DateDiffInDay(const Date &lhs, const Date &rhs)
    {
        return difftime(mktime(lhs.GetTmPtr().get()),
                        mktime(rhs.GetTmPtr().get())) /
               (24 * 60 * 60);
    }
    int DateDiffInDay(const Date &rhs) const { return DateDiffInDay(*this, rhs); }

    Date operator++() { return AdvanceDay(); }
    Date operator++(const int _)
    {
        Date tmp{*this};
        AdvanceDay();
        return tmp;
    }
    Date operator--() { return PrevDay(); }
    Date operator--(const int _)
    {
        Date tmp{*this};
        PrevDay();
        return tmp;
    }
    bool operator<(const Date &rhs) const { return 0 > DateDiffInDay(rhs); }
    bool operator<=(const Date &rhs) const { return 0 >= DateDiffInDay(rhs); }
    bool operator>(const Date &rhs) const { return 0 < DateDiffInDay(rhs); }
    bool operator>=(const Date &rhs) const { return 0 <= DateDiffInDay(rhs); }
    bool operator==(const Date &rhs) const { return 0 == DateDiffInDay(rhs); }
    int operator-(const Date &rhs) const { return DateDiffInDay(rhs); }
    Date operator+(const int n) const { return Date(*this).AdvanceDay(n); }
    Date operator-(const int n) const { return Date(*this).PrevDay(n); }
};

//列举每个月的天数 : 为符合习惯, 用月份作为下标
int Date::nDaysofMonth[13] = {0,
                              31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

#include <sstream>

int main()
{
    std::cout << "Operators:" << std::endl;
    Date date{2019, 10, 10};
    std::cout << "\tOriginal date:\t" << date.ToString() << std::endl
              << "\tdate++\t\t" << (date++).ToString() << std::endl
              << "\tdate\t\t" << date.ToString() << std::endl
              << "\t++date\t\t" << (++date).ToString() << std::endl
              << "\tdate--\t\t" << (date--).ToString() << std::endl
              << "\tdate\t\t" << date.ToString() << std::endl
              << "\t--date\t\t" << (--date).ToString() << std::endl
              << "\tdate + 3\t" << (date + 3).ToString() << std::endl
              << "\tdate - 6\t" << (date - 6).ToString() << std::endl
              << "\ttoday\t\t" << Date::Today().ToString() << std::endl
              << "\tdate-today\t" << (date - Date::Today()) << std::endl;
}