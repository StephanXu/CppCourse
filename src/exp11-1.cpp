#include <iostream>
#include <string>
#include "common/xr.hpp"
using namespace std;
class Employee
{
public:
    Employee(string _name, string _ID) : name(_name), ID(_ID) {}
    string getName()
    {
        return name;
    }
    string getID()
    {
        return ID;
    }
    void setName(const string &_name)
    {
        name = _name;
    }
    void setID(const string &_ID)
    {
        ID = _ID;
    }

private:
    string name;
    string ID;
};

class HourlyWorker : public Employee
{
public:
    HourlyWorker(string _name, string _ID, double _wage, double _hours) : Employee(_name, _ID), wage(_wage), hours(_hours) {}
    double getWage()
    {
        return wage;
    }
    double getHours()
    {
        return hours;
    }
    void setWage(const double &_wage)
    {
        wage = _wage;
    }
    void setHours(const double &_hours)
    {
        hours = _hours;
    }
    double getSalary()
    {
        return wage*hours;
    }
private:
    double wage, hours;
};

class Manager : public Employee
{
public:
    Manager(string _name, string _ID, double _salary) : Employee(_name, _ID), salary(_salary) {}
    double getSalary()
    {
        return salary;
    }
    void setSalary(const double &_salary)

    {
        salary = _salary;
    }

private:
    double salary;
};

int main()
{
    Manager m("Alice", "0", 15500);
    HourlyWorker h("Bob", "1", 20, 40);
    xr(m.getSalary());
    xr(h.getSalary());
}