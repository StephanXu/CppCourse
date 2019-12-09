#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

class Point
{
public:
    Point(int x, int y) : x(x), y(y){};
    Point(const Point &point)
    {
        x = point.x;
        y = point.y;
    }
    Point() : x(0), y(0){};

    static double Distance(const Point p1, const Point p2)
    {
        return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                         (p1.y - p2.y) * (p1.y - p2.y));
    }

    int X() const { return x; }
    int Y() const { return y; }

    std::string ToString() const
    {
        std::stringstream ss;
        ss << "(" << x << ", " << y << ")";
        return ss.str();
    }

private:
    int x, y;
};

int main()
{
    Point p1(0, 0), p2(3, 4);
    std::cout << "p1: " << p1.ToString() << std::endl;
    std::cout << "p2: " << p2.ToString() << std::endl;
    std::cout << "Distance: " << Point::Distance(p1, p2) << std::endl;
}