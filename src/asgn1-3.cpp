#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
template <typename T>
T MyMax(T var1, T var2, T var3)
{
    return std::max(std::max(var1, var2), var3);
}

template <typename T>
T MyMax(T var1, T var2)
{
    return std::max(var1, var2);
}

int main()
{
    std::cout << "Input your numbers:";
    std::string input;
    std::getline(std::cin, input);
    std::stringstream ss(input);
    std::vector<double> numbers{std::istream_iterator<double>(ss),
                                std::istream_iterator<double>()};
    if (2 == numbers.size())
    {
        std::cout << "Result: " << MyMax(numbers[0], numbers[1]) << std::endl;
    }
    else if (3 == numbers.size())
    {
        std::cout << "Result: " << MyMax(numbers[0], numbers[1], numbers[2]) << std::endl;
    }
    else
    {
        std::cerr << "Invalid input" << std::endl;
    }
}