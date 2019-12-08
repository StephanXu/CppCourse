#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "common/xr.hpp"
using namespace std;

const double PI = acos(-1.0);

class Shape
{
public:
    virtual string NameOfType()
    {
        return "Shape";
    }
    virtual void Draw()
    {
        cout << this->NameOfType() << " Drawed!" << endl;
    }
    virtual double Area() = 0;
    virtual double Perimeter() = 0;
};

class Circle : public Shape
{
private:
    double r;

public:
    Circle(double _r) : r(_r) {}
    double Area()
    {
        return r * r * PI;
    }
    double Perimeter()
    {
        return 2 * r * PI;
    }
    string NameOfType()
    {
        return "Circle";
    }
};

class Square : public Shape
{
private:
    double d;

public:
    Square(double _d) : d(_d){};
    double Area()
    {
        return d * d;
    }
    double Perimeter()
    {
        return 4 * d;
    }
    string NameOfType()
    {
        return "Square";
    }
};

class Rectangle : public Shape
{
private:
    double a, b;

public:
    Rectangle(double _a, double _b) : a(_a), b(_b) {}
    double Area()
    {
        return a * b;
    }
    double Perimeter()
    {
        return 2 * (a + b);
    }
    string NameOfType()
    {
        return "Rectangle";
    }
};

class Trapezoid : public Shape
{
private:
    double a, b, h, c;
    double getC()
    {
        double t = b - a;
        return sqrt(pow(h, 2) + pow(t, 2));
    }

public:
    Trapezoid(double _a, double _b, double _h) : a(min(_a, _b)), b(max(_a, _b)), h(_h)
    {
        c = getC();
    }
    double Area()
    {
        return (a + b) * h / 2;
    }
    double Perimeter()
    {
        return a + b + h + c;
    }
    string NameOfType()
    {
        return "Trapezoid";
    }
};
class Triangle : public Shape
{
private:
    double a, b, c;
    double getP()
    {
        return Perimeter() / 2;
    }

public:
    Triangle(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}
    double Area()
    {
        double p = getP();
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
    double Perimeter()
    {
        return a + b + c;
    }
    string NameOfType()
    {
        return "Triangle";
    }
};

int main()
{
    vector<Shape *> c;
    c.push_back(new Circle(6.5));
    c.push_back(new Rectangle(2.3, 3.2));
    c.push_back(new Square(3.5));
    c.push_back(new Triangle(3, 4, 5));
    c.push_back(new Trapezoid(2, 3, sqrt(2)));
    for (auto &&it : c)
    {
        xr(it->NameOfType());
        xrv(it->Draw());
        xr(it->Area());
        xr(it->Perimeter());
        cout << endl;
    }
}