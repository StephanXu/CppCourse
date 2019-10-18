#include <cassert>
#include "Complex.h"
Complex::Complex(double r, double i)
{
    real = r;
    imag = i;
}
Complex ::Complex(const Complex &c)
{
    real = c.real;
    imag = c.imag;
}

Complex::~Complex()
{
}
Complex &Complex::operator=(const Complex &rhs)
{
    real = rhs.real;
    imag = rhs.imag;
    return *this;
}
void Complex ::Print(std ::ostream &os) const
{
    os << real << std::showpos << imag << "i" << std::noshowpos << std ::endl;
}
Complex Add(const Complex &a, const Complex &b)
{
    Complex c;
    c.SetReal(a.GetReal() + b.GetReal());
    c.SetImag(a.GetImag() + b.GetImag());
    return c;
}
Complex Sub(const Complex &a, const Complex &b)
{
    Complex c;
    c.SetReal(a.GetReal() - b.GetReal());
    c.SetImag(a.GetImag() - b.GetImag());
    return c;
}
Complex Mul(const Complex &a, const Complex &b)
{
    Complex c;
    c.SetReal(a.GetReal() * b.GetReal() - a.GetImag() * b.GetImag());
    c.SetImag(a.GetReal() * b.GetImag() + a.GetImag() * b.GetReal());
    return c;
}
Complex Div(const Complex &a, const Complex &b)
{
    double m = b.GetReal() * b.GetReal() + b.GetImag() * b.GetImag();
    assert(m != 0);
    Complex c;
    double r = a.GetReal() * b.GetReal() + a.GetImag() * b.GetImag();
    double i = a.GetImag() * b.GetReal() - a.GetReal() * b.GetImag();
    c.SetReal(r /= m);
    c.SetImag(i /= m);
    return c;
}