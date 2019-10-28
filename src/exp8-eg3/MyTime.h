#ifndef TIME_CLASS
#define TIME_CLASS
#include <iostream>
class Time
{
private:
    int hour, minute, second;
    static int Time2Seconds(const Time &t); //把时间t化为秒数
    static Time Seconds2Time(int s);        //把秒数化为时间
public:
    Time(int h = 0, int m = 0, int s = 0);  //构造函数
    Time &operator++();                     //++Time
    Time operator++(int);                   //Time++
    Time &operator--();                     //--Time
    Time operator--(int);                   //Time--
    int operator-(const Time &rhs) const;   //Time-Time
    Time operator+(int s) const;            //Time+int
    bool operator==(const Time &rhs) const; //Time==Time
    friend std::ostream &operator<<(std::ostream &os, const Time &rhs);
    friend std::istream &operator>>(std::istream &is, Time &rhs);
};
#endif //TIME_CLASS