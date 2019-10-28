#include <iostream>
#include <cassert>
#include <cmath>
#include "Rational.h"
#include <cstring>
int Rational::digits(double d)
{                             //计算浮点数小数部分的位数char buffer[64];
    char buffer[64];          //临时存储字符串
    sprintf(buffer, "%g", d); //把double化为字符串
    int n = strlen(buffer);   //计算字符串长度
    int i = 0;                //定义下标

    while (buffer[i] != '\0' && buffer[i] != '.') //寻找小数点
        ++i;                                      //下标前进
    if (i == n)                                   //没有小数点
        return 0;
    return n - i - 1; //否则返回小数部分的位数
}
int Rational::gcd(int a, int b)
{                  //计算两个数的最大公约数
    int r;         //临时保存余数
    while (b != 0) //除数不能为0
    {
        r = a % b; //计算余数
        a = b;     //替换被除数
        b = r;     //替换除数
    }
    return a; //返回所求最大公约数
}

Rational Rational::normalize()
{                                                    //对有理数进行规范化
    int n = gcd(this->numerator, this->denominator); //先求最大公约数
    assert(n != 0);                                  //确保最大公约数不为0(除非分子分母都为0)
    this->numerator /= n;                            //分子化简
    this->denominator /= n;                          //分母化简
    if (this->denominator < 0)
    {                            //分母是否仍为0
        this->numerator *= -1;   //分子变号
        this->denominator *= -1; //分母为正
    }
    return *this; //返回化简结果
}

Rational::Rational(int n, int d)
{                                         //给定分子和分母构造对象
    this->numerator = n;                  //分子直接赋值
    this->denominator = (d == 0 ? 1 : d); //分母先判断再赋值
}

Rational::Rational(double d)
{                                //由浮点数构造有理数
    int n = Rational::digits(d); //先计算小数部分的位数
    double e = pow(10.0, n);     //化整需要的倍数

    this->numerator = int(d * e); //化整之后数的为分子
    this->denominator = int(e);   //倍数为分母
    this->normalize();            // 规范化
}

Rational::Rational(const Rational &r)
{                                      //复制构造函数
    this->numerator = r.numerator;     //复制分子
    this->denominator = r.denominator; //复制分母
}

Rational &Rational::operator=(const Rational &rhs)
{ //赋值运算

    this->numerator = rhs.numerator;     //复制分子
    this->denominator = rhs.denominator; //复制分母
    return *this;                        //返回当前对象
}
//以下一组函数实现两个Rational之间的算术运算
Rational Rational::operator+(const Rational &rhs) const
{
    Rational r;                                                                          // 生成临时对象保存结果
    r.numerator = this->numerator * rhs.denominator + this->denominator * rhs.numerator; //计算分子
    r.denominator = this->denominator * rhs.denominator;                                 //计算分母
    return r.normalize();                                                                //规范化之后返回
}
Rational Rational::operator-(const Rational &rhs) const
{
    Rational r;                                                                          //生成临时对象保存结果
    r.numerator = this->numerator * rhs.denominator - this->denominator * rhs.numerator; //计算分子
    r.denominator = this->denominator * rhs.denominator;                                 //计算分母
    return r.normalize();                                                                //化简之后返回
}
Rational Rational::operator*(const Rational &rhs) const
{
    Rational r;                                          //生成临时对象保存结果
    r.numerator = this->numerator * rhs.numerator;       //计算分子
    r.denominator = this->denominator * rhs.denominator; //计算分母
    return r.normalize();                                //化简之后返回
}
Rational Rational::operator/(const Rational &rhs) const
{
    assert(rhs.numerator != 0);
    Rational r;                                        //生成临时对象保存结果
    r.numerator = this->numerator * rhs.denominator;   //计算分子
    r.denominator = this->denominator * rhs.numerator; //计算分母
    return r.normalize();                              //化简之后返回
}
//以下一组函数实现两个Rational之间的复合算术运界
Rational &Rational::operator+=(const Rational &rhs)
{
    return *this = *this + rhs; //重用+和=
}
Rational &Rational::operator-=(const Rational &rhs)
{
    return *this = *this - rhs; //重用一和=
}
Rational &Rational::operator*=(const Rational &rhs)
{
    return *this = *this * rhs; //重用*和=
}
Rational &Rational::operator/=(const Rational &rhs)
{
    return *this = *this / rhs; //重用/和=
}
//以下一组函数实现整型数n与Rational对象之间的算术运算
Rational operator+(int n, const Rational &rhs)
{
    return Rational(n) + rhs; //重用+
}
Rational operator-(int n, const Rational &rhs)
{
    return Rational(n) - rhs; //重用-
}
Rational operator*(int n, const Rational &rhs)
{
    return Rational(n) * rhs; //重用*
}
Rational operator/(int n, const Rational &rhs)
{
    return Rational(n) / rhs; //重用/
}

//以下一组函数实现整型数n与Rationa1对象之间的复合算术运算
int &operator+=(int &n, const Rational &rhs)
{
    n = n * rhs.denominator + rhs.numerator;
    return n /= rhs.denominator;
}
int &operator-=(int &n, const Rational &rhs)
{
    n = n * rhs.denominator - rhs.numerator;
    return n /= rhs.denominator;
}
int &operator*=(int &n, const Rational &rhs)
{
    n = n * rhs.numerator;
    return n /= rhs.denominator;
}
int &operator/=(int &n, const Rational &rhs)
{
    assert(rhs.numerator != 0);
    n = n * rhs.denominator;
    return n /= rhs.numerator;
}

//以下一组函数实现浮点数d与Rational对象之间的算术运算
Rational operator+(double d, const Rational &rhs)
{
    return Rational(d) + rhs; //重用+
}
Rational operator-(double d, const Rational &rhs)
{
    return Rational(d) - rhs; //重用-
}
Rational operator*(double d, const Rational &rhs)
{
    return Rational(d) * rhs; //重用*
}
Rational operator/(double d, const Rational &rhs)
{
    return Rational(d) / rhs; //重用/
}
//以下一组函数实现浮点数d与Rational对象之间的复合算术运算
double &operator+=(double &d, const Rational &rhs)
{
    return d += (double)rhs.numerator / rhs.denominator;
}
double &operator-=(double &d, const Rational &rhs)
{
    return d -= (double)rhs.numerator / rhs.denominator;
}
double &operator*=(double &d, const Rational &rhs)
{
    return d *= (double)rhs.numerator / rhs.denominator;
}
double &operator/=(double &d, const Rational &rhs)
{
    assert(rhs.numerator != 0);
    return d /= (double)rhs.numerator / rhs.denominator;
}
//以下实现两个Rational对象之间的关系运算
bool Rational::operator<(const Rational &rhs) const
{
    return (*this - rhs).numerator < 0; //判断差的分子是否小于0
}
bool Rational::operator==(const Rational &rhs) const
{
    return this->numerator * rhs.denominator == this->denominator * rhs.numerator; //判断交叉相乘的结果
}
bool Rational::operator>(const Rational &rhs) const
{
    return rhs < *this; //重用<
}
bool Rational::operator>=(const Rational &rhs) const
{
    return !(*this < rhs); //重用<
}
bool Rational::operator<=(const Rational &rhs) const
{
    return !(rhs < *this); //重用<
}
bool Rational::operator!=(const Rational &rhs) const
{
    return !(*this == rhs); //重用==
}
//以下计算整数n与Rational对象之间的大小与相等关系
bool operator>(int n, const Rational &rhs)
{
    return n > (double)rhs.numerator / rhs.denominator;
}
bool operator>=(int n, const Rational &rhs)
{
    return n >= (double)rhs.numerator / rhs.denominator;
}
bool operator<(int n, const Rational &rhs)
{
    return n < (double)rhs.numerator / rhs.denominator;
}
bool operator<=(int n, const Rational &rhs)
{
    return n <= (double)rhs.numerator / rhs.denominator;
}
bool operator==(int n, const Rational &rhs)
{
    return n == (double)rhs.numerator / rhs.denominator;
}
bool operator!=(int n, const Rational &rhs)
{
    return n != (double)rhs.numerator / rhs.denominator;
}
//以下计算浮点数d与Rational对象之间的大小与相等关系
//以下计算浮点数d与Rational对象之间的大小与相等关系
bool operator>(double d, const Rational &rhs)
{
    return d > (double)rhs.numerator / rhs.denominator;
}
bool operator>=(double d, const Rational &rhs)
{
    return d >= (double)rhs.numerator / rhs.denominator;
}
bool operator<(double d, const Rational &rhs)
{
    return d < (double)rhs.numerator / rhs.denominator;
}
bool operator<=(double d, const Rational &rhs)
{
    return d <= (double)rhs.numerator / rhs.denominator;
}
bool operator==(double d, const Rational &rhs)
{
    return d == (double)rhs.numerator / rhs.denominator;
}
bool operator!=(double d, const Rational &rhs)
{
    return d != (double)rhs.numerator / rhs.denominator;
}
//以下计算Rational对象的正负数
Rational Rational::operator+() const
{
    return *this; //实为本身
}
Rational Rational::operator-() const
{
    return Rational(-this->numerator, this->denominator); //分子取反
}
//以下计算增量与减量
Rational &Rational::operator++()
{
    this->numerator += this->denominator; //分子增加
    return *this;
}
Rational Rational::operator++(int)
{
    Rational temp(*this);
    ++(*this); //重用前置自增运算
    return temp;
}
Rational &Rational::operator--()
{
    this->numerator -= this->denominator; //分子减少
    return *this;
}
Rational Rational::operator--(int)
{
    Rational temp(*this);
    --(*this); //重用前置自减运算
    return temp;
}
//以下为Rational类对象的转换运算符
Rational::operator int() const
{                                               //转换为int值
    return this->numerator / this->denominator; //int 值相除
}
Rational::operator double() const
{                                                       //转换为double值
    return double(this->numerator) / this->denominator; //double值相除
}
//以下实现流插入运算和流提取运算
std::ostream &operator<<(std::ostream &os,
                         const Rational &rhs)
{
    os << rhs.numerator << "/" << rhs.denominator;
    return os;
}
std::istream &operator>>(std::istream &is,
                         Rational &rhs)
{
    char dump;
    is >> rhs.numerator >> dump >> rhs.denominator;
    return is;
}