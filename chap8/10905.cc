/* Title: 10905
 * 考察点：对数字进行排序，注意如果是按前缀大小来排序的话
 * 要考虑123123和123这种情况
 * 这里用到一个小trick，字符串的长度一定，只是组合方式不同，所以直接比较组合后的结果*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool comp(const string &s1, const string &s2);
int main()
{
    int n;
    while (cin >> n && n) {
        vector<string> number;
        string temp;
        for (int i = 0; i < n; i++) {
            cin >> temp;
            number.push_back(temp);
        }


        sort(number.begin(), number.end(), comp);
        if (number[0] == "0") {
            cout << 0 << endl;
            continue;
        }
        for (int i = 0; i < number.size(); i++)
            cout << number[i];
        cout << endl;

    }
}

bool comp(const string &s1, const string &s2)
{
    return s1+s2 > s2+s1;
}
