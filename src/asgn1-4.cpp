#include <iostream>
#include <array>

template <typename T>
int MyFind(T *array, T pat, int n)
{
    for (int i{}; i < n; ++i)
    {
        if (pat == array[i])
        {
            return i;
        }
    }
    return -1;
}

template <typename T>
int Statistic(T *array, size_t size, T pat)
{
    int res{};
    for (int i{}; i < size; ++i)
    {
        if (pat == array[i])
        {
            ++res;
        }
    }
    return res;
}

int main()
{
    int data1[]{3, 5, 7, 10, 23, 7};
    double data2[]{5.4, 9.3, 10.5, 42.2, 55.8, 5.4};
    std::cout << "Data1: ";
    for (auto item : data1)
        std::cout << item << " ";
    std::cout << std::endl;
    int pos = MyFind(data1, 7, 6);
    std::cout << "\tWant: 7" << std::endl;
    std::cout << "\tPos: " << pos << std::endl;
    if (-1 != pos)
        std::cout << "\tFrequency: " << Statistic(data1, 6, 7) << std::endl;
    else
        std::cout << "\tNot found" << std::endl;

    std::cout << "Data2: ";
    for (auto item : data2)
        std::cout << item << " ";
    std::cout << std::endl;
    pos = MyFind(data2, 10.5, 6);
    std::cout << "\tWant: 10.5" << std::endl;
    std::cout << "\tPos: " << pos << std::endl;
    if (-1 != pos)
        std::cout << "\tFrequency: " << Statistic(data2, 6, 10.5) << std::endl;
    else
        std::cout << "\tNot found" << std::endl;
}