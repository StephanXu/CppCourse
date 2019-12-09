#include <memory>
#include <iostream>
#include <cmath>

using namespace std;

class Triangle
{
public:
    static std::unique_ptr<Triangle> MakeTriangle()
    {
        std::unique_ptr<Triangle> res{new Triangle};
        cout << "Please input side length:";
        cin >> res->l[0] >> res->l[1] >> res->l[2];
        if (!IsValid(*res))
        {
            throw std::invalid_argument("invalid triangle");
        }
        return res;
    }

    static bool IsValid(const Triangle &Triangle)
    {
        return Triangle.l[0] > 0 &&
               Triangle.l[1] > 0 &&
               Triangle.l[2] > 0 &&
               Triangle.l[0] + Triangle.l[1] > Triangle.l[2] &&
               Triangle.l[1] + Triangle.l[2] > Triangle.l[0] &&
               Triangle.l[2] + Triangle.l[0] > Triangle.l[1];
    }

    bool IsValid()
    {
        return IsValid(*this);
    }

    static double CalcSquare(const Triangle &triangle)
    {
        double p{(triangle.l[0] + triangle.l[1] + triangle.l[2]) / 2};
        return std::sqrt(p *
                         (p - triangle.l[0]) *
                         (p - triangle.l[1]) *
                         (p - triangle.l[2]));
    }

    double CalcSquare()
    {
        return CalcSquare(*this);
    }

private:
    Triangle() : l({0}) {}
    Triangle(double l1, double l2, double l3) : l({l1, l2, l3}) {}
    double l[3];
};

int main()
{
    try
    {
        std::unique_ptr<Triangle> triangle = Triangle::MakeTriangle();
        std::cout << "Area: " << triangle->CalcSquare() << std::endl;
    }
    catch (std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
    }
}