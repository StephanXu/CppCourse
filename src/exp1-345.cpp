/**
 * @file exp1-345.cpp
 * @author Xu Zihan (stephanxu@foxmail.com)
 * @brief Experiment 1. Item 3, 4, 5
 * @version 0.1
 * @date 2019-09-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <iostream>
#include <iomanip>
#include <memory>
#include <tuple>
#include <algorithm>
#include <vector>
#include <thread>

#include <cstring>
#include <cmath>

/**
 * @brief Shape base class
 * 
 */
class BaseShape
{
public:
    /**
     * @brief Construct a new Base Shape object
     * 
     * @param offsetX horizontal offset
     * @param offsetY vertical offset
     * @param background character to fill in background
     * @param foreground character to fill in foreground
     */
    explicit BaseShape(const int offsetX,
                       const int offsetY,
                       const char background,
                       const char foreground)
        : m_OffsetX(offsetX),
          m_OffsetY(offsetY),
          m_Background(background),
          m_Foreground(foreground)
    {
    }
    virtual int OffsetX() { return m_OffsetX; }
    virtual int OffsetY() { return m_OffsetY; }
    virtual char Background() { return m_Background; }
    virtual char Foreground() { return m_Foreground; }
    virtual void SetOffsetX(const int offsetX) { m_OffsetX = offsetX; }
    virtual void SetOffsetY(const int offsetY) { m_OffsetY = offsetY; }
    virtual void SetBackground(const char background)
    {
        m_Background = background;
    }
    virtual void SetForeground(const char foreground)
    {
        m_Foreground = foreground;
    }
    /**
     * @brief Render current shape to terminal
     * 
     */
    virtual void Render() = 0;

protected:
    unsigned int m_OffsetX{};
    unsigned int m_OffsetY{};
    char m_Background{};
    char m_Foreground{};
};

/**
 * @brief Rhombus
 * Generate rhombus and render to screen
 */
class Rhombus : public BaseShape
{
public:
    /**
     * @brief Construct a new Rhombus object
     * 
     * @param offsetX horizontal offset
     * @param offsetY vertical offset
     * @param background character to fill in background
     * @param foreground character to fill in foreground
     * @param diagonal Diagonal of Rhombus. It supposed to be an even number.
     */
    explicit Rhombus(const int offsetX,
                     const int offsetY,
                     const char background,
                     const char foreground,
                     const int diagonal,
                     const bool isTransparentBorder)
        : BaseShape(offsetX, offsetY, background, foreground),
          m_SemiDiagonal(diagonal / 2),
          m_IsTransparentBorder(isTransparentBorder)
    {
    }

    /**
     * @brief Construct a new Rhombus object
     * 
     * @param diagonal Diagonal of Rhombus. It supposed to be an even number.
     */
    explicit Rhombus(const int diagonal)
        : Rhombus(0, 0, '*', ' ', diagonal, false)
    {
    }

    explicit Rhombus()
        : Rhombus(28)
    {
    }

    void Render() override
    {
        std::shared_ptr<char> outputBuffer{new char[m_SemiDiagonal * 2 + 1]()};
        if (m_OffsetY)
        {
            std::cout << std::setw(m_OffsetY) << std::setfill('\n') << '\n';
        }
        for (int i{}; i < m_SemiDiagonal; ++i)
        {
            RenderHelper(i, outputBuffer);
        }
        for (int i{m_SemiDiagonal - 2}; i >= 0; --i)
        {
            RenderHelper(i, outputBuffer);
        }
    }

private:
    int m_SemiDiagonal{};
    bool m_IsTransparentBorder{};
    void RenderHelper(const int lineIndex,
                      const std::shared_ptr<char> &outputBuffer)
    {
        if (m_OffsetX)
        {
            std::cout << std::setw(m_OffsetX) << std::setfill(' ') << ' ';
        }
        memset(outputBuffer.get(), m_Background, m_SemiDiagonal * 2);
        memset(outputBuffer.get() + m_SemiDiagonal - lineIndex,
               m_Foreground,
               lineIndex * 2 + (m_IsTransparentBorder ? 0 : 1));
        std::cout << outputBuffer << std::endl;
    }
};

/**
 * @brief Rectangle
 * Generate rectangle or square and render to screen
 */
class Rectangle : public BaseShape
{
public:
    /**
     * @brief Construct a rectangle
     * 
     * @param offsetX horizontal offset
     * @param offsetY vertical offset
     * @param background character to fill in background
     * @param foreground character to fill in foreground
     * @param sideLength Side length of rectangle {rows, cols}
     */
    explicit Rectangle(const int offsetX,
                       const int offsetY,
                       const char background,
                       const char foreground,
                       const std::tuple<int, int> sideLength)
        : BaseShape(offsetX, offsetY, background, foreground),
          m_Size(sideLength)
    {
    }

    /**
     * @brief Construct a square
     * 
     * @param offsetX horizontal offset
     * @param offsetY vertical offset
     * @param background character to fill in background
     * @param foreground character to fill in foreground
     * @param sideLength Side length of square
     */
    explicit Rectangle(const int offsetX,
                       const int offsetY,
                       const char background,
                       const char foreground,
                       const int sideLength)
        : BaseShape(offsetX, offsetY, background, foreground),
          m_Size({sideLength, sideLength})
    {
    }

    /**
     * @brief Construct a rectangle
     * 
     * @param sideLength Side length of rectangle {rows, cols}
     */
    explicit Rectangle(const std::tuple<int, int> sideLength)
        : Rectangle(0, 0, ' ', '*', sideLength)
    {
    }

    /**
     * @brief Construct a square
     * 
     * @param sideLength Side length of square
     */
    explicit Rectangle(const int sideLength)
        : Rectangle(0, 0, ' ', '*', sideLength)
    {
    }

    explicit Rectangle()
        : Rectangle(0)
    {
    }

    void Render() override
    {
        if (m_OffsetY)
        {
            std::cout << std::setw(m_OffsetY) << std::setfill('\n') << '\n';
        }
        for (int y{}; y < std::get<0>(m_Size); ++y)
        {
            if (m_OffsetX)
            {
                std::cout << std::setw(m_OffsetX)
                          << std::setfill(' ')
                          << ' ';
            }
            std::cout << std::setw(std::get<1>(m_Size))
                      << std::setfill(m_Foreground)
                      << m_Foreground
                      << std::endl;
        }
    }

private:
    std::tuple<int, int> m_Size;
};

/**
 * @brief Line
 * Generate a line and render to screen
 */
class Line : public BaseShape
{
public:
    /**
     * @brief Construct a line
     * 
     * @param offsetX horizontal offset
     * @param offsetY vertical offset
     * @param background character to fill in background
     * @param foreground character to fill in foreground
     * @param length Length of line
     * @param angle Angle to rotate
     */
    explicit Line(const int offsetX,
                  const int offsetY,
                  const char background,
                  const char foreground,
                  const int length,
                  const double angle)
        : BaseShape(offsetX, offsetY, background, foreground),
          m_Length(length),
          m_Angle(angle)
    {
    }

    typedef std::vector<int> Point;

    void Render() override
    {
        Point vec{m_Length, 0};
        vec = std::move(Rotate(vec, m_Angle));
        // Convert to screen system coordinate system
        std::vector<Point> point{{0, 0}, {vec[0], -vec[1]}};
        if (point[1][0] < 0)
        {
            point[0][0] += abs(point[1][0]);
            point[1][0] += abs(point[1][0]);
        }
        if (point[1][1] < 0)
        {
            point[0][1] += abs(point[1][1]);
            point[1][1] += abs(point[1][1]);
        }
        auto pointCompareProc{
            [](const Point &lhs, const Point &rhs) {
                return lhs[1] < rhs[1] ||
                       ((lhs[1] == rhs[1]) && (lhs[0] < rhs[0]));
            }}; //< In order to print. (top to down, left to right)
        std::sort(point.begin(), point.end(), pointCompareProc);

        if (m_OffsetY)
        {
            std::cout << std::setw(m_OffsetY) << std::setfill('\n') << '\n';
        }
        double slope{};
        int pointsIdx{};
        int xMax{std::max(point[0][0], point[1][0])};
        std::vector<Point> drawPoints = std::move(Bresenham(point[0], point[1]));
        std::sort(drawPoints.begin(), drawPoints.end(), pointCompareProc);
        for (int y{}; y <= point[1][1] && pointsIdx < drawPoints.size(); ++y)
        {
            if (m_OffsetX)
            {
                std::cout << std::setw(m_OffsetX)
                          << std::setfill(' ')
                          << ' ';
            }
            for (int x{}; x <= xMax && pointsIdx < drawPoints.size(); ++x)
            {
                if (y == drawPoints[pointsIdx][1] && x == drawPoints[pointsIdx][0])
                {
                    pointsIdx++;
                    std::cout << m_Foreground;
                }
                else
                {
                    std::cout << m_Background;
                }
            }
            std::cout << std::endl;
        }
    }

private:
    int m_Length{};
    double m_Angle{};

    /**
     * @brief Rotate a 2d vector
     * 
     * @param refVector A vector to be rotated
     * @param angle Angle to rotate
     * @return Point Rotated vector
     */
    Point Rotate(Point &refVector, const double angle)
    {
        Point outVector(2);
        const double rotateMatrix[2][2]{{cos(angle), -sin(angle)},
                                        {sin(angle), cos(angle)}};
        outVector[0] = rotateMatrix[0][0] * refVector[0] +
                       rotateMatrix[0][1] * refVector[1];
        outVector[1] = rotateMatrix[1][0] * refVector[0] +
                       rotateMatrix[1][1] * refVector[1];
        return outVector;
    }

    /**
     * @brief Rasterize a straight line
     * 
     * @param x0 
     * @param y0 
     * @param x1 
     * @param y1 
     * @return std::vector<Point> Rasterized coordinates
     */
    std::vector<Point> Bresenham(int x0, int y0, int x1, int y1)
    {
        std::vector<Point> dest;
        int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
        int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
        int err = (dx > dy ? dx : -dy) / 2;
        while (dest.emplace_back(Point({x0, y0})), x0 != x1 || y0 != y1)
        {
            int e2 = err;
            if (e2 > -dx)
            {
                err -= dy;
                x0 += sx;
            }
            if (e2 < dy)
            {
                err += dx;
                y0 += sy;
            }
        }
        return dest;
    }

    std::vector<Point> Bresenham(Point p1, Point p2)
    {
        return std::move(Bresenham(p1[0], p1[1], p2[0], p2[1]));
    }
};

/**
 * @brief Triangle
 * Generate a triangle and reder to screen
 */
class Triangle : public BaseShape
{
public:
    /**
     * @brief Construct a triangle
     * 
     * @param offsetX horizontal offset
     * @param offsetY vertical offset
     * @param background character to fill in background
     * @param foreground character to fill in foreground
     * @param sideLength side length
     */
    explicit Triangle(const int offsetX,
                      const int offsetY,
                      const char background,
                      const char foreground,
                      const int sideLength)
        : BaseShape(offsetX, offsetY, background, foreground),
          m_SideLength(sideLength)
    {
    }

    void Render() override
    {
        std::shared_ptr<char> outputBuffer{new char[m_SideLength + 1]()};
        if (m_OffsetY)
        {
            std::cout << std::setw(m_OffsetY) << std::setfill('\n') << '\n';
        }
        for (int i{}; i < (m_SideLength + 1) / 2; ++i)
        {
            RenderHelper(i, outputBuffer);
        }
    }

private:
    int m_SideLength;

    void RenderHelper(const int lineIndex,
                      const std::shared_ptr<char> &outputBuffer)
    {
        if (m_OffsetX)
        {
            std::cout << std::setw(m_OffsetX) << std::setfill(' ') << ' ';
        }
        memset(outputBuffer.get(), m_Background, m_SideLength);
        memset(outputBuffer.get() + m_SideLength / 2 - lineIndex,
               m_Foreground,
               lineIndex * 2 + 1);
        std::cout << outputBuffer << std::endl;
    }
};

int main()
{
    int offsetX{}, offsetY{};
    int demoIndex{};
    std::cout << "Choose a shape in Demo:" << std::endl
              << "\t1. Rhombus" << std::endl
              << "\t2. Rectangle" << std::endl
              << "\t3. Square" << std::endl
              << "\t4. Rotated line" << std::endl
              << "\t5. Rotated line(with animation)" << std::endl
              << "\t6. Triangle" << std::endl;
    std::cin >> demoIndex;
    std::cout<<"Customize shape"<<std::endl;
    std::cout << "\tPlease input offset(eg. 5 6):";
    std::cin >> offsetX >> offsetY;
    switch (demoIndex)
    {
    case 1:
    {
        int diagonal{};
        bool isSolid{false};
        char choice{};
        std::cout << "\tDiagonal(eg. 14): ";
        std::cin >> diagonal;
        std::cout << "\tSolid?(Y/n)：";
        std::cin >> choice;
        isSolid = !(choice == 'n' || choice == 'N');
        Rhombus rhombus{offsetX,
                        offsetY,
                        isSolid ? ' ' : '*',
                        isSolid ? '*' : ' ',
                        diagonal,
                        !isSolid};
        rhombus.Render();
        break;
    }
    case 2:
    {
        int sideLengthX{}, sideLengthY{};
        std::cout << "\tSide length(eg. 3 15): ";
        std::cin >> sideLengthY >> sideLengthX;
        Rectangle rectangle{offsetX,
                            offsetY,
                            ' ',
                            '*',
                            {sideLengthY, sideLengthX}};
        rectangle.Render();
        break;
    }
    case 3:
    {
        int sideLength{};
        std::cout << "\tSide length(eg. 15): ";
        std::cin >> sideLength;
        Rectangle rectangle{offsetX,
                            offsetY,
                            ' ',
                            '*',
                            sideLength};
        rectangle.Render();
        break;
    }
    case 4:
    {
        int length{};
        double angle{};
        std::cout << "\tLength(eg. 15): ";
        std::cin >> length;
        std::cout << "\tAngle(eg. 45): ";
        std::cin >> angle;
        angle = angle / 180 * 3.14;
        Line line{offsetX, offsetY, ' ', '*', 30, angle};
        line.Render();
        break;
    }
    case 5:
    {
        int length{};
        double angle{};
        std::cout << "\tLength(eg. 15): ";
        std::cin >> length;
        double count{};
        for (;;)
        {
            double angle{count++ / 10};
            Line line{offsetX, offsetY, ' ', '*', 30, angle};
            line.Render();
            std::this_thread::sleep_for(std::chrono::milliseconds(60));
            system("clear");
        }
    }
    case 6:
    {
        int sideLength{};
        std::cout << "\tSide Length(eg. 15): ";
        std::cin >> sideLength;
        Triangle triangle{offsetX, offsetY, ' ', '*', sideLength};
        triangle.Render();
        break;
    }
    default:
        break;
    }
}