#include <cmath>
#include "common/xr.hpp"
using namespace std;
class point
{
private:
    double x, y;

public:
    point(double a, double b) : x(a), y(b)
    {
    }
    double getx() const
    {
        return x;
    }
    double gety() const
    {
        return y;
    }
};
class line
{
private:
    point start, eNd;

public:
    line(double a, double b, double c, double d) : start(a, b), eNd(c, d)
    {
    }
    line(const point &a, const point &b) : start(a), eNd(b)
    {
    }
    double length() const
    {
        double dx = start.getx() - eNd.getx();
        double dy = start.gety() - eNd.gety();
        return sqrt(dx * dx + dy * dy);
    }
    point midpoint() const
    {
        double x = (start.getx() + eNd.getx()) / 2;
        double y = (start.gety() + eNd.gety()) / 2;
        return point(x, y);
    }
};
int main()
{
    point a(1, 2), b(1, 4);
    line la(a, b);
    line lb(0, 1, 0, 5), lc(lb);

    xr(la.length());
    xr(lb.length());
    xr(lc.length());
    lc = line(la.midpoint(), lb.midpoint());
    xr(lc.length());
}
