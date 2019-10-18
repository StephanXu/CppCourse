#include "Date.h"
#include "xr.hpp"
int main()
{
    Date d(2008, 8, 8);                 //生成一个日期对象
    xrv(d.Print());                     //输出
    xrv(d.Date2Days());                 //计算相对基准的天数

    d = Date::Days2Date(d.Date2Days()); //把上面的天教再转换为日期
    xrv(d.Print());                     //应该仍为2008 - 8 - 8
    
    d = Date::Days2Date(2000);          //从基准经过2000天
    xrv(d.Print());
}