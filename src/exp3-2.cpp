/**
 * @file exp3-2.cpp
 * @author Xu Zihan (stephanxu@foxmail.com)
 * @brief Experiment 3. Item 2(P133)
 * @version 0.1
 * @date 2019-09-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <iostream>
#include <memory>

int main()
{
    std::cout << "Input your array size:";
    size_t size{};
    size_t overNumberArraySize{};
    std::cin >> size;
    /* Get input */
    std::unique_ptr<int> data{new int[size]};
    std::cout << "Input your array:";
    for (int i{}; i != size; ++i)
    {
        std::cin >> data.get()[i];
        if (0 == data.get()[i] % 2)
        {
            ++overNumberArraySize;
        }
    }
    /* Generate new array */
    std::unique_ptr<int> overData{new int[overNumberArraySize]};
    int overDataIdx{};
    for (int i{}; i != size; ++i)
    {
        if (0 == data.get()[i] % 2)
        {
            overData.get()[overDataIdx++] = data.get()[i];
        }
    }
    /* Output result */
    std::cout << "Result:";
    for (int i{}; i != overNumberArraySize; ++i)
    {
        std::cout << overData.get()[i] << " ";
    }
    std::cout << std::endl;
}