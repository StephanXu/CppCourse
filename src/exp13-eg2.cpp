#include <fstream>
#include <sstream> //for ostringstream
#include <string>
#include <iomanip>
#include "common/verify.hpp"
std::string int2str(int n, int w = 2)
{                                    //把整数转提成字符率
    std::ostringstream oss;          //定义字符事输出流对象
    oss << "#" << std::setfill('0'); //前导,以0填充
    oss << std::setw(w) << n;        //占位宽度为w
    return oss.str();                //返回格式化后的字符串
}
int main()
{
    std::string srcfile("../src/exp13-eg2.cpp");         //源数据所在的文件
    std::string dstfile("lined_exp13-eg2.cpp"); //目标数据的文件
    std::ifstream ifs(srcfile.c_str());      //定义文件输入流对象
    verify(ifs);
    std::ofstream ofs(dstfile.c_str()); //定义文件输出流对象
    verify(ofs);
    int num = 0;        //行数计数
    std::string buffer; //存放每行内容
    while (std::getline(ifs, buffer))
    {                                          //读取文件的一行
        ++num;                                 //增加行数
        buffer = int2str(num) + "\t" + buffer; //格式化行号,并放置在行前
        ofs << buffer << std::endl;            //向文件输出带行号的内容
        std::cout << buffer << std::endl;      //同时在屏幕上显示
    }
    ofs.close(); //关闭文件流
    ifs.close(); //关闭文件流
}