#include <iostream>
#include <vector>
#include <initializer_list>

class Polynomial
{
public:
    explicit Polynomial(std::initializer_list<double> coef)
    {
        m_Coefficients.assign(coef);
    }

private:
    std::vector<double> m_Coefficients;
    
};

int main()
{
    std::vector<int> a{1,2,3,4,5};
}