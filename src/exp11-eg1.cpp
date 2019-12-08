#include <iostream>
#include <string>
class Person
{                     //基类:人员类
protected:            //注意权限
    std::string name; //姓名
    int age;          //年龄
public:
    Person(char *n, int a) : name(n), age(a) {} //构造函数
    void PrintPerson(std::ostream &os = std::cout) const
    {
        os << name << "\t" << age << "\n";
    }
};
class Student : public Person
{                 //从Person类继承
protected:        // 注意权限
    double score; // 增加新的属性 : 分数
public:
    Student(char *n, int a, double s) //派生类的构造函数
        : Person(n, a), score(s)      //调用基类的构造函数
    {
    }
    void PrintStudent(std::ostream &os = std::cout) const
    {
        os << name << "\t" << age << "\t"
           << score << std::endl;
    }
};
class Undergraduate : public Student
{ //从Student类继承
private:
    std::string speciality; //增加新的属性:专业
public:
    Undergraduate(char *n, int a, double s, char *sp)
        : Student(n, a, s), speciality(sp) //调用直接基类的构造函数
    {
    }
    void PrintUndergraduate(std::ostream &os = std::cout) const
    {
        os << name << "\t" << age << "\t"
           << score << "\t" << speciality << std::endl;
    };
};
int main()
{
    Person Tom("Tom", 20); //构造基类的对象
    Tom.PrintPerson();
    Student Jerry("Jerry", 18, 90); //构造派生类的对象
    Jerry.PrintStudent();
    Undergraduate Mickey("Mickey", 22, 85, "MBA"); //构造派生类的对象
    Mickey.PrintUndergraduate();
}