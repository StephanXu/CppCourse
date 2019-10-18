#include "Complex.h"
#include "xr.hpp"
int main()
{
    xrv(Complex a(14, 2));              //测试构造函数
    xrv(Complex b(3,4));                //测试构造函数
    xrv(Complex c);                      //测试构造函数
    xrv(c=Add(a,b));xrv(c.Print());     //测试加法，赋值，复制和输出
    xrv(c=Sub(a,b));xrv(c.Print());     //测试减法，赋值，复制和输出
    xrv(c=Mul(a,b));xrv(c.Print());     //测试乘法，赋值，复制和输出
    xrv(c=Div(a,b));xrv(c.Print());     //测试除法，赋值，复制和输出
                                        //测试析构函数
}