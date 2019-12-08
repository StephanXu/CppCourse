#include <string>
#include "common/xr.hpp"
class Person
{ //人员类作为基类
private:
    int pid;          //身份证号
    std::string name; //姓名
    int age;          //年龄
public:
    Person(int id = 0, const char *str = "", int a = 0)
        : pid(id), name(str), age(a) //初始化数据成员
    {
    }
    virtual void Print() const //暂时保留注释
    {
        std::cout << pid << ":" << name << ":" << age << "\t";
    }
    virtual void DoSomething() const //暂时保留注释
    {
        std::cout << "I am a person,I need doing something.\n";
    }
};

class Student : public Person
{ //学生类作为派生类
private:
    double score; //成绩
public:
    Student(int id = 0, const char *str = "", int a = 0, double s = 0)
        : Person(id, str, a), score(s) //初始化基类成员和自己的数据成员
    {
    }
    void Print() const
    {                    //输出Student类的信息
        Person::Print(); //调用基类的函数
        std::cout << "score:" << score << std::endl;
    }
    void DoSomething() const
    { //说明对象的工作
        std::cout << "I am a student,I need studying.\n";
    }
};

class Worker : public Person
{ //派生类:员工类
private:
    double salary; //工资
public:
    Worker(int id = 0, const char *str = "", int a = 0, double s = 0)
        : Person(id, str, a), salary(s) //初始化基类成员和自己的数据成员
    {
    }
    void Print() const
    {                    //输出Worker类的信息
        Person::Print(); //调用基类的函数
        std::cout << "salary:" << salary << std::endl;
    }
    void Dosomething() const
    { //说明对象的工作
        std::cout << "I am a worker,I need working.\n";
    }
};

void testByObj(Person p)
{ //以值形式的对象作为参数
    p.Print();
    p.DoSomething();
}
void testByPtr(Person *p)
{ //以对象指针作为参数
    p->Print();
    p->DoSomething();
}
void testByRef(Person &p)
{ //以对象引用作为参数
    p.Print();
    p.DoSomething();
}

int main()
{
    Person p(200801, "Tom", 20);
    Student s(200802, "Jerry", 22, 85);
    Worker w(200803, "Mickey", 24, 2000);
    xrv(testByObj(p));
    xrv(testByObj(s));
    xrv(testByObj(w));

    xrv(testByPtr(&p));
    xrv(testByPtr(&s));
    xrv(testByPtr(&w));

    xrv(testByRef(p));
    xrv(testByRef(s));
    xrv(testByRef(w));
}