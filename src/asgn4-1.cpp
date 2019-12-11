#include <iostream>
#include <string>
#include <vector>

enum GenderType
{
    Male,
    Female
};

class Person
{
public:
    explicit Person(std::string name, GenderType gender, unsigned int age)
        : m_Name(name),
          m_Gender(gender),
          m_Age(age)
    {
    }

    std::string Name() { return m_Name; }
    GenderType Gender() { return m_Gender; }
    unsigned int Age() { return m_Age; }

    virtual void DoSomething() = 0;

private:
    std::string m_Name;
    GenderType m_Gender;
    unsigned int m_Age;
};

class Teacher : public Person
{
public:
    explicit Teacher(std::string name,
                     GenderType gender,
                     unsigned int age,
                     unsigned int id,
                     std::string college)
        : Person(name, gender, age), m_Id(id), m_College(college)
    {
    }
    unsigned int Id() { return m_Id; }
    std::string College() { return m_College; }

    void DoSomething()
    {
        std::cout << "Id:" << Id()
                  << "  Type: Teacher  " << Name()
                  << " from class: " << College();
    }

private:
    unsigned int m_Id;
    std::string m_College;
};

class Student : public Person
{
public:
    explicit Student(std::string name,
                     GenderType gender,
                     unsigned int age,
                     unsigned int id,
                     std::string stuClass)
        : Person(name, gender, age), m_Id(id), m_Class(stuClass)
    {
    }

    void DoSomething()
    {
        std::cout << "Id:" << Id()
                  << "  Type: Student  "
                  << Name() << " from college: " << Class();
    }

    unsigned int Id() { return m_Id; }
    std::string Class() { return m_Class; }

private:
    unsigned int m_Id;
    std::string m_Class;
};

int main()
{
    std::vector<Person *> persons;
    persons.push_back(new Teacher("Jessica", Female, 30, 10001, "Computer Science"));
    persons.push_back(new Teacher("Feifei Lee", Female, 35, 10002, "Computer Science"));
    persons.push_back(new Teacher("Mike", Male, 32, 20001, "Architect"));
    persons.push_back(new Student("Tom", Male, 20, 40001, "SJ001"));
    persons.push_back(new Student("Elizabeth", Female, 19, 40002, "SJ001"));

    for (std::vector<Person *>::iterator it = persons.begin();
         it != persons.end();
         ++it)
    {
        (*it)->DoSomething();
        std::cout << std::endl;
    }

    for (std::vector<Person *>::iterator it = persons.begin();
         it != persons.end();
         ++it)

    {
        delete *it;
    }
}