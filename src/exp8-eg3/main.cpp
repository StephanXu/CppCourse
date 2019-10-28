#include "MyTime.h"
#include "xr.hpp"

int main()
{
    Time s, t, r;
    std::cout << "Please enter 2 times:(hh:mm::ss)";
    std::cin >> s >> t;
    xr(s);
    xr(t);
    r = ++s;
    xr(r);
    xr(s);
    r = s++;
    xr(r);
    xr(s);
    r = --t;
    xr(r);
    xr(t);
    r = t--;
    xr(r);
    xr(t);
    xr(s);
    xr(t);
    r = s + (t - s);
    xr(r == t);
    r = s + (s - t);
    xr(r == t);
}