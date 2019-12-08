#include <string>
#include "common/xr.hpp"

template <typename T>
void myswap(T &a, T &b)
{
    T t(a);
    a = b, b = t;
}

template <typename T>
void sort3(T &a, T &b, T &c)
{
    if (a < b)
        myswap(a, b);
    if (a < c)
        myswap(a, c);
    if (b < c)
        myswap(b, c);
}

template <typename T>
void print(const T &t)
{
    std::cout << t << std::endl;
}

class Student
{
private:
    int sid;
    std::string name;
    double score;

public:
    Student(int id, const char *str, double s) : sid(id), name(str), score(s)
    {
    }
    Student(const Student &s)
    {
        if (this != &s)
        {
            sid = s.sid;
            name = s.name;
            score = s.score;
        }
    }
    Student &operator=(const Student &rhs)
    {
        if (this != &rhs)
        {
            sid = rhs.sid;
            name = rhs.name;
            score = rhs.score;
        }
        return *this;
    }
    bool operator<(const Student &rhs) const
    {
        return score < rhs.score;
    }
    friend std::ostream &operator<<(std::ostream &os,
                                    const Student &rhs)
    {
        os << rhs.sid << "\t" << rhs.name << "\t" << rhs.score;
        return os;
    }
};

int main()
{
    Student a(200803, "Tom", 85);
    Student b(200802, "Jerry", 90);
    Student c(200801, "Goofy", 70);
    sort3(a, b, c);
    print(a);
    print(b);
    print(c);
}