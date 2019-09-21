/**
 * @file exp3-7.cpp
 * @author Xu Zihan (stephanxu@foxmail.com)
 * @brief Experiment 3. Item 7.
 * @version 0.1
 * @date 2019-09-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <iostream>
#include <vector>
#include <initializer_list>
#include <sstream>
#include <string>
#include <iterator>

#include <cmath>
/**
 * @brief Polynomial
 * 
 */
class Polynomial
{
public:
    /**
     * @brief Construct a new Polynomial object
     * 
     * @param coef 1-D array of array of series coefficients ordered from low 
     * to high degree.
     */
    explicit Polynomial(std::initializer_list<double> coef)
    {
        m_Coefficients.assign(coef);
    }

    /**
     * @brief Construct a new Polynomial object
     * 
     * @param coef 1-D array of array of series coefficients ordered from low 
     * to high degree.
     */
    Polynomial(std::vector<double> coef)
        : m_Coefficients(coef)
    {
    }

    Polynomial(const Polynomial &polynomial)
    {
        m_Coefficients = polynomial.m_Coefficients;
    }

    Polynomial(const Polynomial &&polynomial)
    {
        m_Coefficients = std::move(polynomial.m_Coefficients);
    }

    Polynomial operator=(const Polynomial &polynomial)
    {
        return Polynomial(polynomial);
    }

    /**
     * @brief Get value with exactly x-value
     * 
     * @param xValue x value
     * @return double result
     */
    double operator()(double xValue)
    {
        return Calculate(xValue);
    }

    /**
     * @brief Derivation
     * 
     * @return Polynomial Result 
     */
    Polynomial Derivation()
    {
        Polynomial result(*this);
        if (1 == result.m_Coefficients.size())
        {
            result.m_Coefficients[0] = 0;
            return result;
        }
        for (size_t i{0}; i != result.m_Coefficients.size(); ++i)
        {
            result.m_Coefficients[i] *= result.m_Coefficients.size() - 1 - i;
        }
        result.m_Coefficients.pop_back();
        return result;
    }

    std::string ToString()
    {
        std::stringstream ss{};
        ss << "(";
        for (const auto &item : m_Coefficients)
        {
            ss << item << ",";
        }
        ss << ")";
        return ss.str();
    }

private:
    std::vector<double> m_Coefficients;

    double Calculate(double xValue)
    {
        double sum{};
        for (size_t i{}; i != m_Coefficients.size(); ++i)
        {
            sum += m_Coefficients[i] *
                   std::pow(xValue, m_Coefficients.size() - 1 - i);
        }
        return sum;
    }
};

/**
 * @brief Newton iteration method
 * 
 * @param poly Polynomial 
 * @param seed A seed to start iteration
 * @param similarFactor Minimum error threshold
 * @return double result
 */
double NewtonIteration(Polynomial &poly,
                       double seed = 0,
                       double similarFactor = 1e-8)
{
    Polynomial dpoly{poly.Derivation()};
    double result{seed};
    while (true)
    {
        double newResult = result - poly(result) / dpoly(result);
        if (abs(result - newResult) <= 1e-8)
        {
            return newResult;
        }
        result = newResult;
    }
}

int main()
{
    std::cout << "Please input your polynomial:";
    std::string input;
    std::getline(std::cin, input);
    std::stringstream ss(input);
    std::vector<double> coef{std::istream_iterator<double>(ss),
                             std::istream_iterator<double>()};
    Polynomial poly(coef);
    while (true)
    {
        std::cout << "Seed: ";
        double seed{};
        std::cin >> seed;
        std::cout << "Result: " << NewtonIteration(poly, seed) << std::endl;
    }
}