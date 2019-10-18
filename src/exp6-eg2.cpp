#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <numeric>
class Student
{
private:
    char name[80];
    double score;

public:
    Student(char *sn = "", double ds = 0)
    {
        strcpy(name, sn);
        score = ds;
    }
    Student(const Student &s)
    {
        if (this != &s)
        {
            strcpy(name, s.name);
            score = s.score;
        }
    }
    Student &operator=(const Student &rhs)
    {
        if (this != &rhs)
        {
            strcpy(name, rhs.name);
            score = rhs.score;
        }
        return *this;
    }
    double GetScore() const { return score; }
    void Print() { std::cout << name << ":\t" << score << "\n"; }
};
bool compByScore(const Student &a, const Student &b)
{
    return a.GetScore() < b.GetScore();
}
double addScore(double d, const Student &s)
{
    return d + s.GetScore();
}
int main()
{
    const size_t N = 4;
    Student s[N];
    s[0] = Student("Tom", 85);
    s[1] = Student("Jerry", 90);
    s[2] = Student("Goofy", 70);
    s[3] = Student("Mickey", 85);
    std::cout << "before sort:\n";
    std::for_each(s, s + N, std::mem_fun_ref(&Student::Print));
    std::sort(s, s + N, compByScore);
    std::cout << "after sort:\n"; //以下输出排序结果
    std::for_each(s, s + N, std::mem_fun_ref(&Student::Print));
    double avg = std::accumulate(s, s + N, double(0), addScore) / N;
    std::cout << "average score is " << avg << std::endl;
}
