#ifndef COMPLEX_CLASS
#define COMPLEX_CLASS

#include <iostream>
class Complex
{
private:
    double real, imag;

public:
    Complex(double r = 0, double i = 0);
    Complex(const Complex &c);
    ~Complex();
    Complex &operator=(const Complex &rhs);

    void SetReal(double r) { real = r; }
    void SetImag(double i) { imag = i; }
    double GetReal() const { return real; }
    double GetImag() const { return imag; }
    void Print(std::ostream &os = std::cout) const;
};
Complex Add(const Complex &a, const Complex &b);
Complex Sub(const Complex &a, const Complex &b);
Complex Mul(const Complex &a, const Complex &b);
Complex Div(const Complex &a, const Complex &b);

#endif // COMPLEX_CLASS