/**
 * @file exp3-1.cpp
 * @author Xu Zihan (stephanxu@foxmail.com)
 * @brief Experiment 3. Item 1(P133)
 * @version 0.1
 * @date 2019-09-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

#include <cmath>
#include <cstring>

/**
 * @brief Calculate a polynomial
 * Calculate a string polynomial
 */
class ExpressionCalculate
{
public:
    /**
     * @brief Construct a new Polynomial Calculate object
     * 
     * @param expression expression to calculate
     */
    explicit ExpressionCalculate(std::string expression);
    explicit ExpressionCalculate();
    ~ExpressionCalculate();

    /**
     * @brief Set the Expression object
     * 
     * @param expression expression to calculate
     */
    void SetExpression(std::string expression);

    /**
     * @brief Calculate expression
     * This function calculate the expression with all variables(if have).
     * @return double result
     */
    double Calculate();

    /**
     * @brief Declare a variable in expression
     * 
     * @param symbol Variable symbol(eg. x)
     * @param val Initial value(0 by default)
     */
    void RegisterVariable(char symbol, double val = 0);

    /**
     * @brief Set a Variable's value
     * 
     * @param symbol The symbol of variable.
     * @param val Value to set.
     */
    void SetVariable(char symbol, double val);

private:
    double MathFunction(double x, char op[], int *iop);

    double CalculateValueHelper(const char *expr, char **addr);

    std::string m_Expression{};
    const char m_Tab{0x9};
    std::map<char, double> m_Variables;
};

ExpressionCalculate::ExpressionCalculate(std::string expression)
{
    SetExpression(expression);
}

ExpressionCalculate::ExpressionCalculate()
    : ExpressionCalculate("")
{
}

ExpressionCalculate::~ExpressionCalculate()
{
}

double ExpressionCalculate::MathFunction(double x, char op[], int *iop)
{
    while (op[*iop - 1] < 32) //< Ignore the parentheses of the function
    {
        switch (op[*iop - 1])
        {
        case 7:
            x = sin(x);
            (*iop)--;
            break;
        case 8:
            x = cos(x);
            (*iop)--;
            break;
        case 9:
            x = tan(x);
            (*iop)--;
            break;
        case 10:
            x = sqrt(x);
            (*iop)--;
            break;
        case 11:
            x = asin(x);
            (*iop)--;
            break;
        case 12:
            x = acos(x);
            (*iop)--;
            break;
        case 13:
            x = atan(x);
            (*iop)--;
            break;
        case 14:
            x = log10(x);
            (*iop)--;
            break;
        case 15:
            x = log(x);
            (*iop)--;
            break;
        case 16:
            x = exp(x);
            (*iop)--;
            break;
        case 17:
            x = ceil(x);
            (*iop)--;
            break;
        case 18:
            x = floor(x);
            (*iop)--;
            break;
        }
    }
    return x;
}

double ExpressionCalculate::CalculateValueHelper(const char *expr,
                                                 char **addr)
{
    static int recursiveDepth; //< Recursive depth
    static const std::vector<std::string> funcNames{
        "sin", "cos", "tan", "sqrt",
        "arcsin", "arccos", "arctan", "lg",
        "ln", "exp", "ceil", "floor"};
    double numericStack[10] = {0.0}; //< numeric stack
    char operatorStack[10] = {'+'};  //< operators stack
    char c{}, *rexp{}, *pp{}, *pf{};
    int ist{1}, iop{1};
    bool isNumericLast{false};

    if (!recursiveDepth)
    {
        pp = pf = const_cast<char *>(expr);
        do
        {
            c = *pp++;
            if (c != ' ' && c != m_Tab)
                *pf++ = c;
        } while (c != '\0');
    }
    pp = const_cast<char *>(expr);
    if ((c = *pp) == '-' || c == '+')
    {
        operatorStack[0] = c;
        pp++;
    }
    isNumericLast = false;
    while ((c = *pp) != '\0')
    {
        if (c == '(')
        { //< Match open parenthesis
            recursiveDepth++;
            numericStack[ist++] = CalculateValueHelper(++pp, addr);
            recursiveDepth--;
            numericStack[ist - 1] = MathFunction(numericStack[ist - 1],
                                                 operatorStack,
                                                 &iop);
            pp = *addr;
            isNumericLast = true;
            if (*pp == '(' || isalpha(*pp) && strncmp(pp, "Pi", 2))
            {
                /**
                 * When we matched a open paren or function name at the right
                 * of close paren, applying multiply in default.
                 */
                operatorStack[iop++] = '*';
                isNumericLast = false;
                c = operatorStack[--iop];
                goto operate;
            }
        }
        else if (c == ')')
        { //< Match close parenthesis
            pp++;
            break;
        }
        else if (isalpha(c))
        {
            std::map<char, double>::iterator it;
            if (!strncmp(pp, "Pi", 2))
            {
                if (isNumericLast)
                {
                    throw std::invalid_argument(
                        "Close paren at the left of pi");
                }
                numericStack[ist++] = 3.14159265358979323846264338328;
                numericStack[ist - 1] = MathFunction(numericStack[ist - 1],
                                                     operatorStack,
                                                     &iop);
                pp += 2;
                isNumericLast = true;
                if (!strncmp(pp, "Pi", 2))
                {
                    throw std::invalid_argument("Two continuous pi");
                }
                if (*pp == '(')
                {
                    throw std::invalid_argument(
                        "Close paren at the right of pi");
                }
            }
            else if ((it = m_Variables.find(c)) != m_Variables.end())
            {
                numericStack[ist++] = it->second;
                numericStack[ist - 1] = MathFunction(numericStack[ist - 1],
                                                     operatorStack,
                                                     &iop);
                pp++;
                isNumericLast = true;
            }
            else
            {
                int i{};
                pf = nullptr;
                for (auto &&function : funcNames)
                {
                    if (!strncmp(pp, function.c_str(), function.size()))
                    {
                        pf = const_cast<char *>(function.c_str());
                        break;
                    }
                    ++i;
                }
                auto it = m_Variables.find(c);
                if (pf)
                {
                    operatorStack[iop++] = 07 + i;
                    pp += strlen(pf);
                }
                else if (it != m_Variables.end())
                {
                    operatorStack[iop++] = it->first;
                    pp++;
                }
                else
                {
                    throw std::invalid_argument(
                        "Unknown function name or variables.");
                }
            }
        }
        else if (c == '+' || c == '-' || c == '*' ||
                 c == '/' || c == '%' || c == '^')
        {
            char cc;
            if (!isNumericLast)
            {
                throw std::invalid_argument("Two continuous operator");
            }
            pp++;
            if (c == '+' || c == '-')
            {
                do
                {
                    cc = operatorStack[--iop];
                    --ist;
                    switch (cc)
                    {
                    case '+':
                        numericStack[ist - 1] += numericStack[ist];
                        break;
                    case '-':
                        numericStack[ist - 1] -= numericStack[ist];
                        break;
                    case '*':
                        numericStack[ist - 1] *= numericStack[ist];
                        break;
                    case '/':
                        numericStack[ist - 1] /= numericStack[ist];
                        break;
                    case '%':
                        numericStack[ist - 1] = fmod(numericStack[ist - 1],
                                                     numericStack[ist]);
                        break;
                    case '^':
                        numericStack[ist - 1] = pow(numericStack[ist - 1],
                                                    numericStack[ist]);
                        break;
                    }
                } while (iop);
                operatorStack[iop++] = c;
            }
            else if (c == '*' || c == '/' || c == '%')
            {
            operate:
                cc = operatorStack[iop - 1];
                if (cc == '+' || cc == '-')
                {
                    operatorStack[iop++] = c;
                }
                else
                {
                    --ist;
                    operatorStack[iop - 1] = c;
                    switch (cc)
                    {
                    case '*':
                        numericStack[ist - 1] *= numericStack[ist];
                        break;
                    case '/':
                        numericStack[ist - 1] /= numericStack[ist];
                        break;
                    case '%':
                        numericStack[ist - 1] = fmod(numericStack[ist - 1],
                                                     numericStack[ist]);
                        break;
                    case '^':
                        numericStack[ist - 1] = pow(numericStack[ist - 1],
                                                    numericStack[ist]);
                        break;
                    }
                }
            }
            else
            {
                cc = operatorStack[iop - 1];
                if (cc == '^')
                {
                    throw std::invalid_argument("Two continuous power sign");
                }
                operatorStack[iop++] = c;
            }
            isNumericLast = false;
        }
        else
        {
            if (isNumericLast)
            {
                throw std::invalid_argument("Two continuous numeric");
            }
            numericStack[ist++] = strtod(pp, &rexp);
            numericStack[ist - 1] = MathFunction(numericStack[ist - 1],
                                                 operatorStack, &iop);
            if (pp == rexp)
            {
                throw std::invalid_argument("Invalid charactor");
            }
            pp = rexp;
            isNumericLast = true;
            if (*pp == '(' || isalpha(*pp))
            {
                operatorStack[iop++] = '*';
                isNumericLast = false;
                c = operatorStack[--iop];
                goto operate;
            }
        }
    }
    *addr = pp;
    if (iop >= ist)
    {
        throw std::invalid_argument("Invalid expression");
    }
    while (iop)
    {
        --ist;
        switch (operatorStack[--iop])
        {
        case '+':
            numericStack[ist - 1] += numericStack[ist];
            break;
        case '-':
            numericStack[ist - 1] -= numericStack[ist];
            break;
        case '*':
            numericStack[ist - 1] *= numericStack[ist];
            break;
        case '/':
            numericStack[ist - 1] /= numericStack[ist];
            break;
        case '%':
            numericStack[ist - 1] = fmod(numericStack[ist - 1],
                                         numericStack[ist]);
            break;
        case '^':
            numericStack[ist - 1] = pow(numericStack[ist - 1],
                                        numericStack[ist]);
            break;
        }
    }
    return numericStack[0];
}

void ExpressionCalculate::SetExpression(std::string expression)
{
    m_Expression = expression;
}

double ExpressionCalculate::Calculate()
{
    char *endss;
    return CalculateValueHelper(m_Expression.c_str(), &endss);
}

void ExpressionCalculate::RegisterVariable(char symbol, double val)
{
    if (m_Variables.find(symbol) != m_Variables.end())
        return;
    m_Variables.insert(std::pair<char, double>(symbol, val));
}

void ExpressionCalculate::SetVariable(char symbol, double val)
{
    m_Variables[symbol] = val;
}

int main()
{
    std::string expression{};
    std::cout << "Please input expression to calculate:" << std::endl
              << "Expr:";
    std::cin >> expression;
    try
    {
        ExpressionCalculate poly(expression);
        auto result = poly.Calculate();
        std::cout << "Result:" << result << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error:" << e.what() << '\n';
    }
}