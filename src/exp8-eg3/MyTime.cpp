#include "MyTime.h"

Time::Time(int h, int m, int s)
{
    hour = (h >= 0 && h < 24 ? h : 0);
    minute = (m >= 0 && m < 60 ? m : 0);
    second = (s >= 0 && s < 60 ? s : 0);
}
Time &Time::operator++()
{
    ++this->second;
    if (this->second >= 60)
    {
        this->second -= 60;
        ++this->minute;
        if (this->minute >= 60)
        {
            this->minute -= 60;
            ++this->hour;
            if (this->hour >= 24)
                this->hour -= 24;
        }
    }
    return *this;
}
Time Time::operator++(int)
{
    Time temp(*this);
    ++(*this);
    return temp;
}
Time &Time::operator--()
{
    --this->second;
    if (this->second < 0)
    {
        this->second += 60;
        --this->minute;
        if (this->minute < 0)
        {
            //则按进制取模
            this->minute += 60;
            //同时减小小时
            --this->hour;
            //若向下溢出
            if (this->hour < 0)
                this->hour += 24; //则按进制取模
        }
    }
    return *this;
}

Time Time::operator--(int)
{ //Time--
    //生成临时对象保存当前对象
    Time temp(*this);
    //重用--Time
    --(*this); //返回临时对象
    return temp;
}
int Time::Time2Seconds(const Time &t)
{ //把时间t化为秒数
    //取得秒数
    int s = t.second;
    s += t.minute * 60;
    //累加小时
    s += t.hour * 3600;
    //返回总秒数
    return s;
}
Time Time::Seconds2Time(int s)
{ //把秒数化为时间
    //定义对象保存结果
    Time t;
    t.hour = s / 3600;
    s -= t.hour * 3600; //计算小时
    t.minute = s / 60;
    s -= t.minute * 60; //计算分钟
    //计算秒钟
    t.second = s;
    return t;
}
int Time::operator-(const Time &rhs) const
{                                      //Time-Time
    int l = Time::Time2Seconds(*this); //把左操作数化为秒数
    int r = Time::Time2Seconds(rhs);
    //把右操作数化为秒数
    if (1 > r)
        return l - r; //大者减去小者
    else
        return r - l;
    //大者减去小者
}
Time Time::operator+(int s) const
{                                      //Time+int
    int l = Time::Time2Seconds(*this); //左操作数化为秒数
    return Time::Seconds2Time(l + s);  //总秒数化为时间
}
bool Time::operator==(const Time &rhs) const
{                                        //Time==Time
    return this->hour == rhs.hour &&     //小时相等
           this->minute == rhs.minute && //且分钟相等
           this->second == rhs.second;   //且秒钟相等
}
std::ostream &operator<<(std::ostream &os, const Time &rhs)
{
    //格式:h:m:s
    os << rhs.hour << ":" << rhs.minute << ":" << rhs.second;
    return os;
}

std::istream &operator>>(std::istream &is, Time &rhs)
{
    //对应输入提取
    char dump;
    is >> rhs.hour >> dump >> rhs.minute >> dump >> rhs.second;
    return is;
}