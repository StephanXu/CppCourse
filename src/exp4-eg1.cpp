#include <iostream>
#include <algorithm>
#include <functional>

void print_score(double d) { std::cout << d << "\t"; }
bool lower_than_60(double d) { return d < 60; }

int main()
{
    double s[] = {85, 76, 60, 54, 89, 90, 96, 45, 85, 85, 98};
    size_t n = sizeof(s) / sizeof(*s);

    std::cout << "all scores are: \n";
    std::for_each(s, s + n, print_score);

    double k = 85;
    size_t m = std::count(s, s + n, k);
    std::cout << "\nthere are " << m << " scores equal to "
              << k << std::endl;
    double *p = std::find(s, s + n, k);
    std::cout << "first " << k << " is at " << p - s << std::endl;
    p = std::search_n(s, s + n, 2, k);
    std::cout << "fist 2 consecutive scores of " << k
              << " is at " << p - s << std::endl;
    p = std::search_n(s, s + n, 2, k, std::greater<double>());
    std::cout << "fist 2 consecutive scores greater than " << k
              << " is at " << p - s << std::endl;

    m = std::count_if(s, s + n, lower_than_60);
    std::cout << "there are " << m << " scores failed to pass the exam.\n";
    p = std::find_if(s, s + n, lower_than_60);
    std::cout << "first score failed is at " << p - s << std::endl;

    p = std::min_element(s, s + n);
    std::cout << "score " << *p << " is the lowest." << std::endl;
    p = std::max_element(s, s + n);
    std::cout << "score " << *p << " is the highest." << std::endl;
}