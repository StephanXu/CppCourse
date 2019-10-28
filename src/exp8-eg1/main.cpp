#include "Rational.h"
#include "xr.hpp"
int main()
{
    Rational r1(30, 9), r2(8.125), r;
    xr(r1);
    xr(r2);
    xr(r);

    xr(r1 + r2);
    xr(r1 - r2);
    xr(r1 * r2);
    xr(r1 / r2);

    r = 0;
    xr(r += r1);
    xr(r -= r1);
    xr(r *= r1);
    xr(r /= r1);

    xr(r1 > r2);
    xr(r1 >= r2);
    xr(r1 < r2);
    xr(r1 <= r2);
    xr(r1 == r2);
    xr(r1 != r2);

    int n = 3;
    xr(n + r2);
    xr(n - r2);
    xr(n * r2);
    xr(n / r2);
    xr(n += r2);
    xr(n -= r2);
    xr(n *= r2);
    xr(n /= r2);

    xr(n > r2);
    xr(n >= r2);
    xr(n < r2);
    xr(n <= r2);
    xr(n == r2);
    xr(n != r2);

    double d = 3.14;
    xr(d + r1);
    xr(d - r1);
    xr(d * r1);
    xr(d / r1);
    xr(d += r1);
    xr(d -= r1);
    xr(d *= r1);
    xr(d /= r1);

    xr(d > r1);
    xr(d >= r1);
    xr(d < r1);
    xr(d <= r1);
    xr(d == r1);
    xr(d != r1);

    xr(+r1);
    xr(-r1);
    xr(++r2);
    xr(r2++);
    xr(--r2);
    xr(r2--);

    xr(int(r2));
    xr(double(r2));
}