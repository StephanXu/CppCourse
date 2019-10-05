#include <iostream>
#include <string>

template <typename T>
void MySwap(T &lhs, T &rhs)
{
    T tmp = lhs;
    lhs = rhs;
    rhs = tmp;
}

int main()
{
    int var1{3}, var2{6};
    double var3{1.2}, var4{3.5};
    std::string var5{"Hello"}, var6{"World"};
    std::cout << "Before:" << std::endl
              << var1 << "\t" << var2 << std::endl
              << var3 << "\t" << var4 << std::endl
              << var5 << "\t" << var6 << std::endl;
    MySwap(var1, var2);
    MySwap(var3, var4);
    MySwap(var5, var6);
    std::cout << "After:" << std::endl
              << var1 << "\t" << var2 << std::endl
              << var3 << "\t" << var4 << std::endl
              << var5 << "\t" << var6 << std::endl;
}