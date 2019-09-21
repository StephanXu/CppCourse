#include <memory>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<vector<int>> point{{0, 0}, {-1, -1}};
    for (auto item : point)
    {
        cout << item[0] << "," << item[1] << endl;
    }
    if (point[1][0] < 0)
    {
        point[0][0] += abs(point[1][0]);
        point[1][0] += abs(point[1][0]);
    }
    if (point[1][1] < 0)
    {
        point[0][1] += abs(point[1][1]);
        point[1][1] += abs(point[1][1]);
    }
    for (auto item : point)
    {
        cout << item[0] << "," << item[1] << endl;
    }
    std::sort(point.begin(), point.end(), [](const vector<int> lhs, const vector<int> rhs) {
        return lhs[1] < rhs[1];
    });

    for (auto item : point)
    {
        cout << item[0] << "," << item[1] << endl;
    }
}
