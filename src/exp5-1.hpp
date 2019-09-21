
#ifndef EXP5_1_HPP
#define EXP5_1_HPP

enum class LinePosRel
{
    Coincident,
    Parallel,
    Acrossing
};

class Point;
class Line;

/**
 * @brief Line
 * Represent a straight line by standard equation
 */
class Line
{
public:
    explicit Line(int a, int b, int c) : m_a(a), m_b(b), m_c(c)
    {
    }
    explicit Line() : Line(0, 0, 0)
    {
    }

    friend LinePosRel Position(const Line &a, const Line &b, Point &outPoint);

private:
    double m_a{}, m_b{}, m_c{};
};

/**
 * @brief Point
 * Represent a point
 */
class Point
{
public:
    explicit Point(int x, int y) : m_x(x), m_y(y)
    {
    }
    explicit Point() : Point(0, 0)
    {
    }

    friend LinePosRel Position(const Line &a, const Line &b, Point &outPoint);

    double X() { return m_x; }
    double Y() { return m_y; }

private:
    double m_x{}, m_y{};
};


#endif