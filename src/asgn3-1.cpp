#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>

class MyString
{
public:
    MyString(std::string str) { buf.assign(str.begin(), str.end()); }
    MyString(const char *str) { buf.assign(str, str + strlen(str)); }
    MyString() {}
    ~MyString() {}

    void append(const MyString &rhs)
    {
        buf.insert(buf.end(), rhs.buf.cbegin(), rhs.buf.cend());
    }

    MyString operator+(const MyString &rhs)
    {
        MyString tmp(*this);
        tmp.append(rhs);
        return tmp;
    }

    MyString &operator+=(const MyString &rhs)
    {
        append(rhs);
        return *this;
    }

    int Compare(const MyString &rhs) const
    {
        std::vector<char>::const_iterator itl = buf.begin(), itr = rhs.buf.begin();
        char delta = 0;
        for (delta = 0;
             delta != 0 && itl != buf.end() && itl != rhs.buf.end();
             itl++, itr++)
        {
            delta = *itl - *itr;
        }
        if (0 == delta && rhs.length() < length())
        {
            return *buf.rbegin();
        }
        else if (0 == delta && rhs.length() > length())
        {
            return 0 - *rhs.buf.rbegin();
        }
        return delta;
    }

    bool operator<(const MyString &rhs) const { return Compare(rhs) < 0; }
    bool operator>(const MyString &rhs) const { return Compare(rhs) > 0; }
    bool operator==(const MyString &rhs) const { return Compare(rhs) == 0; }

    friend std::ostream &operator<<(std::ostream &os, const MyString &rhs)
    {
        return os.write(rhs.buf.data(), rhs.buf.size());
    }
    friend std::istream &operator>>(std::istream &is, MyString &rhs)
    {
        std::istream::sentry _Ok(is);
        if (_Ok)
        {
            rhs.buf.clear();
            while (is.good())
            {
                char c = is.get();
                if (std::isspace(c, is.getloc()))
                    break;
                if (std::isdigit(c, is.getloc()))
                    rhs.buf.push_back(c);
            }
        }
        return is;
    }

    size_t length() const { return buf.size(); }
    size_t size() const { return buf.size(); }

private:
    std::vector<char> buf;
};

int main()
{
    // MyString str[4];
    // str[0] = "Here is a test for \"=\"";
    // str[1] += " and \"+=\"";
    // str[2] += str[1] + " and \"+\"";
    // std::cout << "input your text: ";
    // std::cin >> str[3];
}