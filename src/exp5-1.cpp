/**
 * @file exp5-1.cpp
 * @author Xu Zihan (stephanxu@foxmail.com)
 * @brief Experiment 5. Item 1(P145)
 * @version 0.1
 * @date 2019-09-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <iostream>
#include "exp5-1.hpp"

/**
 * @brief Get relation between two staight lines
 * 
 * @param a line 1
 * @param b line 2
 * @param outPoint Across point(if have)
 * @return LinePosRel Relation
 */
LinePosRel Position(const Line &a, const Line &b, Point &outPoint)
{
    if (0 == a.m_a && 0 == a.m_b && 0 == b.m_a && 0 == b.m_b)
    {
        throw std::invalid_argument("Invalid line");
    }
    if (0 == a.m_b && 0 == b.m_b)
    {
        return LinePosRel::Parallel;
    }
    if ((0 == a.m_b && 0 != b.m_b) ||
        (0 != a.m_b && 0 == b.m_b) ||
        (a.m_a / a.m_b != b.m_a / b.m_b))
    {
        outPoint = Point((-a.m_c * b.m_b - a.m_b * (-b.m_c)) /
                             (a.m_a * b.m_b - a.m_b * b.m_a),
                         (a.m_a * (-b.m_c) - (-a.m_c) * b.m_a) /
                             (a.m_a * b.m_b - a.m_b * b.m_a));
        return LinePosRel::Acrossing;
    }
    if ((0 == a.m_a * b.m_a && a.m_a != b.m_a) ||
        (0 == a.m_b * b.m_b && a.m_b != b.m_b) ||
        (0 == a.m_c * b.m_c && a.m_c != b.m_c) ||
        (a.m_a / b.m_a != a.m_b / b.m_b) ||
        (a.m_b / b.m_b != a.m_c / b.m_c) ||
        (a.m_a / b.m_a != a.m_c / b.m_c))
    {
        return LinePosRel::Parallel;
    }
    return LinePosRel::Coincident;
}

int main()
{
    double a{}, b{}, c{};
    std::cout << "Please input a b c of 'line1': ";
    std::cin >> a >> b >> c;
    Line l1(a, b, c);
    std::cout << "Please input a b c of 'line2': ";
    std::cin >> a >> b >> c;
    Line l2(a, b, c);
    Point p{};
    try
    {
        LinePosRel rel{Position(l1, l2, p)};
        switch (rel)
        {
        case LinePosRel::Acrossing:
            std::cout << "Relation: Acrossing" << std::endl
                      << "Point: (" << p.X() << ", "
                      << p.Y() << ")" << std::endl;
            break;
        case LinePosRel::Coincident:
            std::cout << "Relation: Coincident" << std::endl;
            break;
        case LinePosRel::Parallel:
            std::cout << "Relation: Parallel" << std::endl;
            break;
        default:
            break;
        }
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}