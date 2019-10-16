#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

enum class GenderEnum
{
    Male,
    Female
};

class Worker
{
public:
    Worker(const std::string id,
           const std::string name,
           const int age,
           const GenderEnum gender,
           const double salary)
        : m_Id(id), m_Name(name), m_Age(age), m_Gender(gender), m_Salary(salary)
    {
    }
    Worker(const Worker &worker)
        : Worker(worker.m_Id, worker.m_Name, worker.m_Age,
                 worker.m_Gender, worker.m_Salary)
    {
    }
    Worker &operator=(const Worker &rhs)
    {
        m_Id = rhs.m_Id;
        m_Name = rhs.m_Name;
        m_Age = rhs.m_Age;
        m_Gender = rhs.m_Gender;
        m_Salary = rhs.m_Salary;
        return *this;
    }
    void Print(std::ostream &os = std::cout)
    {
        os << m_Id << "\t" << m_Name << "\t" << m_Age << "\t"
           << (m_Gender ==
                       GenderEnum::Male
                   ? "Male"
                   : "Female")
           << "\t" << m_Salary;
    }
    std::string Id() const { return m_Id; };
    std::string Name() const { return m_Name; };
    int Age() const { return m_Age; };
    GenderEnum Gender() const { return m_Gender; }
    double Salary() const { return m_Salary; }

private:
    std::string m_Id;
    std::string m_Name;
    int m_Age;
    GenderEnum m_Gender;
    double m_Salary;
};

int main()
{
    std::vector<Worker> workers;
    std::cout << "Employee's information:" << std::endl;
    workers.emplace_back("00001", "John", 27, GenderEnum::Male, 12.9);
    workers.emplace_back("00002", "Alice", 25, GenderEnum::Female, 16.6);
    workers.emplace_back("00003", "Bob", 25, GenderEnum::Male, 15.3);
    workers.emplace_back("00004", "Lisa", 25, GenderEnum::Female, 17.2);
    std::cout << "id\tname\tage\tgender\tsalary(K)" << std::endl;
    for (auto &&employee : workers)
    {
        employee.Print();
        std::cout << std::endl;
    }

    std::cout << "Sort by salary:" << std::endl;
    std::sort(workers.begin(), workers.end(),
              [](const Worker &lhs, const Worker &rhs) {
                  return lhs.Salary() > rhs.Salary();
              });
    std::cout << "id\tname\tage\tgender\tsalary(K)" << std::endl;
    for (auto &&employee : workers)
    {
        employee.Print();
        std::cout << std::endl;
    }

    std::cout << "Highest salary:\t"
              << workers.begin()->Name() << std::endl;
    std::cout << "Lowest salary:\t"
              << std::prev(workers.end())->Name() << std::endl;
    double memAvrSalary{}, womenAvrSalary{};
    int memCount{}, womenCount{};
    for (auto &&employee : workers)
    {
        if (employee.Gender() == GenderEnum::Male)
        {
            memAvrSalary += employee.Salary();
            ++memCount;
        }
        else
        {
            womenAvrSalary += employee.Salary();
            ++womenCount;
        }
    }
    std::cout << "Average salary:\t"
              << (memAvrSalary + womenAvrSalary) / (memCount + womenCount)
              << std::endl;
    std::cout << "Average male salary:\t"
              << memAvrSalary / memCount << std::endl;
    std::cout << "Average female salary:\t"
              << womenAvrSalary / womenCount << std::endl;
}