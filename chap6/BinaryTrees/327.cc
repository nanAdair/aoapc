#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int process(string s, int value[], bool flag[]);
string remove_blank(string s);
int main()
{
    string expression;
    while (getline(cin, expression)) {
        int value[26];
        bool flag[26];
        for (int i = 0; i < 26; i++) {
            flag[i] = 0;
            value[i] = i + 1;
        }

        int res = process(remove_blank(expression), value, flag);
        cout << "Expression: " << expression << endl;
        cout << "    value = " << res << endl;
        for (int i = 0; i < 26; i++) {
            if (flag[i] == 1)
                cout << "    " << (char)(i + 'a') << " = " << value[i] << endl;
        }
    }
}

int process(string s, int value[], bool flag[])
{
    bool addfirst, minusfirst;
    addfirst = minusfirst = 0;
    int sum = 0;
    int sign = 1;

    int length = s.length();
    for (int i = 0; i < length; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            flag[s[i] - 'a'] = 1;
            /* 如果有前置操作符就不会有后缀，处理后返回即可 */
            if (addfirst == 1 || minusfirst == 1) {
            if (addfirst == 1) {
                value[s[i] - 'a'] += 1;
                addfirst = 0;
            }
            else if (minusfirst == 1) {
                value[s[i] - 'a'] -= 1;
                minusfirst = 0;
            }
            sum += value[s[i] - 'a'] * sign;
            continue;
            }

            /* 否则先检测下是否会有后缀，没有直接加减 
             * 这里注意范围*/
            if (i == length - 1 || (s[i+1] != s[i+2])) {
                sum += value[s[i] - 'a'] * sign;
                continue;
            }

            /* 处理后缀加 */
            if (s[i+1] == '+' && s[i+2] == '+') {
                sum += value[s[i] - 'a'] * sign;
                value[s[i] - 'a'] += 1;
                i += 2;
                continue;
            }
            /* 处理后缀减 */
            if (s[i+1] == '-' && s[i+2] == '-') {
                sum += value[s[i] - 'a'] * sign;
                value[s[i] - 'a'] -= 1;
                i += 2;
                continue;
            }
        }
        else if (s[i] == '+') {
            if (s[i+1] != '+')
                sign = 1;
            else {
                i += 1;
                addfirst = 1;
            }
        }
        else {
            if (s[i+1] != '-')
                sign = -1;
            else {
                i += 1;
                minusfirst = 1;
            }
        }
    }
    return sum;
}

string remove_blank(string s)
{
    stringstream expression(s);
    string res = "";
    char c;

    while (expression >> c)
        res.push_back(c);

    return res;
}
