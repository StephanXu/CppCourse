#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
class Point
{
public:
    Point(int x, int y) : x(x), y(y){};
    Point(const Point &point) = default;
    Point() : Point(0, 0){};

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

enum class Relation
{
    OnRect,
    InRect,
    OutRect
};

std::string RelationToString(const Relation relation)
{
    if (Relation::OnRect == relation)
    {
        return "On rect";
    }
    else if (Relation::InRect == relation)
    {
        return "In rect";
    }
    return "Out rect";
}

class Rectanlge
{
public:
    Rectanlge(const Point &&p1, const Point &&p2)
    {
        p[0] = p1;
        p[1] = p2;
    }
    Rectanlge(int x1, int y1, int x2, int y2)
        : Rectanlge(Point(x1, y1), Point(x2, y2))
    {
    }

    double Square() const
    {
        return std::abs((p[0].X() - p[1].X()) * (p[0].Y() - p[1].Y()));
    }

    Point Center() const
    {
        return Point((p[1].X() + p[0].X()) / 2, (p[1].Y() + p[0].Y()) / 2);
    }

    Relation PointRelation(const Point point) const
    {
        if (point.X() > p[0].X() && point.X() < p[1].X() &&
            point.Y() > p[0].Y() && point.Y() < p[1].Y())
        {
            return Relation::InRect;
        }
        else if (point.X() < p[0].X() || point.X() > p[1].X() ||
                 point.Y() < p[0].Y() || point.Y() > p[1].Y())
        {
            return Relation::OutRect;
        }
        return Relation::OnRect;
    }

    std::string ToString() const
    {
        return "{" + p[0].ToString() + ", " + p[1].ToString() + "}";
    }

private:
    Point p[2];
};

int main()
{
    std::cout << "Create a rectangle: ";

    int input[4];
    std::cin >> input[0] >> input[1] >> input[2] >> input[3];
    Rectanlge rectangle{input[0], input[1], input[2], input[3]};
    std::cout << "\tThe rectangle: " << rectangle.ToString() << std::endl;

    std::cout << "Create a point: ";
    std::cin >> input[0] >> input[1];
    Point p1{input[0], input[1]};
    std::cout << "\tThe point: " << p1.ToString() << std::endl;

    std::cout << "Create another point: ";
    std::cin >> input[0] >> input[1];
    Point p2{input[0], input[1]};
    std::cout << "\tThe point: " << p2.ToString() << std::endl;

    std::cout << std::endl;

    std::cout << "Distance between points: "
              << Point::Distance(p1, p2) << std::endl;

    std::cout << "Rectangle area: " << rectangle.Square() << std::endl;
    std::cout << "Rectangle center: "
              << rectangle.Center().ToString() << std::endl;
    std::cout << "The relation between points and rectangle: " << std::endl;
    std::cout << "\tp1: "
              << RelationToString(rectangle.PointRelation(p1)) << std::endl;
    std::cout << "\tp2: "
              << RelationToString(rectangle.PointRelation(p2)) << std::endl;
}

/**
 * Test

Create a rectangle: 2 3 5 6
        The rectangle: {(2, 3), (5, 6)}
Create a point: 1 2
        The point: (1, 2)
Create another point: 3 4
        The point: (3, 4)

Distance between points: 2.82843
Rectangle area: 9
Rectangle center: (3, 4)
The relation between points and rectangle: 
p1: Out rect
p2: In rect

 */