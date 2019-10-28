#ifndef RATIONAL_CLASS
#define RATIONAL_CLASS
#include <iostream>
class Rational
{
private:
    int numerator, denominator; //分子,分母
    //以下为一组工具函数
    static int digits(double d);  //计算浮点数小数部分的位数
    static int gcd(int a, int b); //计算两个数的最大公约数
    Rational normalize();         //对有理数进行规范化
public:
    Rational(int n = 0, int d = 1);           //给定分子和分母
    Rational(double d);                       //由浮点数构造有理数
    Rational(const Rational &r);              //复制构造函数
    Rational &operator=(const Rational &rhs); //赋值运算符函数
    //以下一组函数实现两个Rational之间的算术运算
    Rational operator+(const Rational &rhs) const; //Rational+Rational
    Rational operator-(const Rational &rhs) const; //Rational-Rational
    Rational operator*(const Rational &rhs) const; //Rational*Rational
    Rational operator/(const Rational &rhs) const; //Rational/Rational
    //以下一组函数实现两个Rational之间的复合算术运算
    Rational &operator+=(const Rational &rhs); //Rational+=Rational
    Rational &operator-=(const Rational &rhs); //Rational-=Rational
    Rational &operator*=(const Rational &rhs); //Rational*=Rational
    Rational &operator/=(const Rational &rhs); //Rational/=Rational
    //以下一组函数实现int与Rational之间的算术运算
    friend Rational operator+(int n, const Rational &rhs); //n+Rational
    friend Rational operator-(int n, const Rational &rhs); //n-Rational
    friend Rational operator*(int n, const Rational &rhs); //n*Rational
    friend Rational operator/(int n, const Rational &rhs); //n/Rational
    //以下一组函数实现int与Rational之间的复合算术运算
    friend int &operator+=(int &n, const Rational &rhs);
    friend int &operator-=(int &n, const Rational &rhs);
    friend int &operator*=(int &n, const Rational &rhs);
    friend int &operator/=(int &n, const Rational &rhs);
    //以下一组函数实现double与Rational之间的算术运算
    friend Rational operator+(double d, const Rational &rhs);
    friend Rational operator-(double d, const Rational &rhs);
    friend Rational operator*(double d, const Rational &rhs);
    friend Rational operator/(double d, const Rational &rhs);
    //以下一组函数实现int与Rational之间的复合算术运算
    friend double &operator+=(double &d, const Rational &rhs);
    friend double &operator-=(double &d, const Rational &rhs);
    friend double &operator*=(double &d, const Rational &rhs);
    friend double &operator/=(double &d, const Rational &rhs);
    //以下一组函数实现两个Rational之间的关系运算
    bool operator>(const Rational &rhs) const;  //Rational>Rational
    bool operator==(const Rational &rhs) const; //Rational==Rational
    bool operator>=(const Rational &rhs) const; //Rational>=Rational
    bool operator<(const Rational &rhs) const;  //Rational<Rational
    bool operator<=(const Rational &rhs) const; //Rational<=Rational
    bool operator!=(const Rational &rhs) const; //Rational!=Rational
    //以下一组函数实现int与Rational之间的关系运算
    friend bool operator>(int n, const Rational &rhs);  //n>Rational
    friend bool operator>=(int n, const Rational &rhs); //n>=Rational
    friend bool operator<(int n, const Rational &rhs);  //n<Rational
    friend bool operator<=(int n, const Rational &rhs); //n<=Rational
    friend bool operator==(int n, const Rational &rhs); //n==Rational
    friend bool operator!=(int n, const Rational &rhs); //n!=Rational
    //以下一组函数 double与Rational之间的关系运算
    friend bool operator>(double d, const Rational &rhs);
    friend bool operator>=(double d, const Rational &rhs);
    friend bool operator<(double d, const Rational &rhs);
    friend bool operator<=(double d, const Rational &rhs);
    friend bool operator==(double d, const Rational &rhs);
    friend bool operator!=(double d, const Rational &rhs);
    //以下一组函数计算正负数
    Rational operator+() const; //+Rational
    Rational operator-() const; //-Rational
    //以下一组函数实现增量和减量运算
    Rational &operator++();   //++Rational
    Rational operator++(int); //Rational++
    Rational &operator--();   //--Rational
    Rational operator--(int); //Rational--
    //以下一组函数是转换运算符函数
    operator int() const;    //int(Rational)
    operator double() const; //double(Rational)
    //以下一组函数实现流插入和提取运算
    friend std::ostream &operator<<(std::ostream &os,
                                    const Rational &rhs);
    friend std::istream &operator>>(std::istream &is,
                                    Rational &rhs);
};
#endif // RATIONAL_CLASS