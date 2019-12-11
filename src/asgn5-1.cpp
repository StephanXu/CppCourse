#include <iostream>
#include <fstream>
#include <vector>

class Student
{
public:
    Student() {}
    Student(std::string name, unsigned int age, unsigned int grade)
        : m_Name(name), m_Age(age), m_Grade(grade) {}
    friend std::istream &operator>>(std::istream &is, Student &student)
    {
        is >> student.m_Name;
        is >> student.m_Age;
        is >> student.m_Grade;
    }
    friend std::ostream &operator<<(std::ostream &os, const Student &student)
    {
        os << student.Name() << " ";
        os << student.Age() << " ";
        os << student.Grade() << " ";
    }

    std::string Name() const { return m_Name; }
    unsigned int Age() const { return m_Age; }
    unsigned int Grade() const { return m_Grade; }

private:
    std::string m_Name;
    unsigned int m_Age;
    unsigned int m_Grade;
};

template <typename T>
bool DefaultCompare(T &lhs, T &rhs)
{
    return lhs < rhs;
}

template <typename T, class CompareProc = bool(T &, T &)>
void CustomSort(std::vector<T> &arr, CompareProc compare = DefaultCompare<T>)
{
    for (typename std::vector<T>::iterator it = arr.begin();
         it != arr.end();
         it++)
    {
        for (typename std::vector<T>::iterator i = it;
             i != arr.end();
             i++)
        {
            if (compare(*i, *it))
            {
                std::swap(*it, *i);
            }
        }
    }
}

bool CompareStudentScore(const Student *lhs, const Student *rhs)
{
    return lhs->Grade() > rhs->Grade();
}

int main()
{
    std::vector<Student *> students;
    std::ifstream f("student.txt", std::ios::in);
    std::ofstream of("student_ordered.txt", std::ios::out);
    if (!f.is_open())
    {
        std::cerr << "Load students fail." << std::endl;
        return 0;
    }
    if (!of.is_open())
    {
        std::cerr << "Open output file fail." << std::endl;
        return 0;
    }
    Student _s;
    while (f >> _s)
    {
        std::cout << "Load: " << students.size() << "\t" << _s << std::endl;
        students.push_back(new Student(_s));
    }
    CustomSort(students, CompareStudentScore);
    for (std::vector<Student *>::iterator it = students.begin();
         it != students.end();
         ++it)

    {
        std::cout << "Output: " << std::distance(students.begin(), it)
                  << "\t" << **it << std::endl;
        of << **it << std::endl;
        delete *it;
    }
}