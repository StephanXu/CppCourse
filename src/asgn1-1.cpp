#include <iostream>
#include <memory>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;

typedef struct Triangle
{
    double l[3];
} Triangle;

bool IsTriangleValid(const Triangle &Triangle)
{
    return Triangle.l[0] > 0 &&
           Triangle.l[1] > 0 &&
           Triangle.l[2] > 0 &&
           Triangle.l[0] + Triangle.l[1] > Triangle.l[2] &&
           Triangle.l[1] + Triangle.l[2] > Triangle.l[0] &&
           Triangle.l[2] + Triangle.l[0] > Triangle.l[1];
}

std::shared_ptr<Triangle> BuildTriangle()
{
    std::shared_ptr<Triangle> res{new Triangle};
    cout << "Please input side length:";
    cin >> res->l[0] >> res->l[1] >> res->l[2];
    if (!IsTriangleValid(*res))
    {
        return std::shared_ptr<Triangle>();
    }
    return res;
}

double CalcSquare(const Triangle &triangle)
{
    double p{(triangle.l[0] + triangle.l[1] + triangle.l[2]) / 2};
    return std::sqrt(p *
                     (p - triangle.l[0]) *
                     (p - triangle.l[1]) *
                     (p - triangle.l[2]));
}

int main()
{
    auto triangle{BuildTriangle()};
    if (!triangle)
    {
        std::cerr << "Invalid triangle" << endl;
        return 0;
    }
    cout << "Valid triangle" << endl;
    cout << "S = " << CalcSquare(*triangle) << endl;
    return 0;
}