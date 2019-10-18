#ifndef DATE_CLASS
#define DATE_CLASS
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
    void LeapYearEnabled() const;

public:
    Date(int y = YearBase, int m = MonthBase, int d = DayBase);
    Date(const Date &d);
    Date &operator=(const Date &rhs);

    void SetDate(int y, int m, int d);
    void Print() const;
    
    static bool IsLeapYear(int y);
    static int DaysOfThisYear(int y);
    
    int Date2Days() const;
    static Date Days2Date(int n);
};
#endif // DATE_CLASS