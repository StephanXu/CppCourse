#include <iostream>
class nchars
{ //封装要连续输出的数据
private:
    size_t n; //要重复输出的次数
    char ch;  //要输出的字符
public:
    nchars(size_t m, char c) : n(m), ch(c) {} //保存要连续输出的数据
    friend std::ostream &operator<<(std::ostream &os,
                                    const nchars &rhs)
    { //以下连续输出多个字符
        for (size_t i = 0; i != rhs.n; ++i)
            os << rhs.ch;
        return os;
    }
};
class diamond
{ //检出菱形图案的算子类型
private:
    size_t row; //该形中上三角的行数
    char cfill; //组成菱形的字符
public:
    diamond(size_t r, char c) : row(r), cfill(c) {} //菱形的组成数据
    friend std::ostream &operator<<(std::ostream &os,
                                    const diamond &rhs)
    {
        //以下实现菱形绘制
        for (size_t i = 1; i <= rhs.row; ++i)
        {                                      //第一步:绘制上三角
            os << nchars(rhs.row - i, ' ')     //先输出n-i个空格
               << nchars(2 * i - 1, rhs.cfill) //再输出2i-1个字符
               << std::endl;                   //最后换行
        }
        for (size_t i = 2; i <= rhs.row; ++i)
        {                                                  //第二步:绘制下三角
            os << nchars(i - 1, ' ')                       //先输出i-1个空格
               << nchars(2 * (rhs.row - i) + 1, rhs.cfill) //再输出2(n-i)+1个字符
               << std::endl;                               //最后换行
        }
        return os;
    }
};
int main()
{
    std::cout << diamond(14, '*') << std::endl; //定义操纵算子给制菱形
}
