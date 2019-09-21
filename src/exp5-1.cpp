#include <iostream>

enum class LinePosRel
{
    Coincident,
    Parallel,
    Acrossing
};

class Point;
class Line;

class Line
{
public:
    explicit Line(int a, int b, int c) : m_a(a), m_b(b), m_c(c)
    {
    }
    explicit Line() : Line(0, 0, 0)
    {
    }

    friend LinePosRel Position(const Line &a, const Line &b, Point &p);

private:
    double m_a{}, m_b{}, m_c{};
};

class Point
{
public:
    explicit Point(int x, int y) : m_x(x), m_y(y)
    {
    }
    explicit Point() : Point(0, 0)
    {
    }

    friend LinePosRel Position(const Line &a, const Line &b, Point &p);

private:
    double m_x{}, m_y{};
};

LinePosRel Position(const Line &a, const Line &b, Point &outP)
{
    if (0 == a.m_b && 0 == b.m_b)
    {
        return LinePosRel::Parallel;
    }
    if ((0 == a.m_b && 0 != b.m_b) ||
        (0 != a.m_b && 0 == b.m_b) ||
        (a.m_a / a.m_b != b.m_a / b.m_b))
    {
        return LinePosRel::Acrossing;
    }
    return LinePosRel::Parallel;
}

int main()
{
}