/* Title: 673
 * 考察点：最简单的栈操作*/
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    string temp;
    getline(cin, temp);
    for (int i = 0; i < n; i++) {
        char c;
        stack<char> strlist;
        bool flag = 1;
        getline(cin, temp);
        stringstream ss(temp);
        while (ss >> c) {
            if (c == '(' || c == '[')
                strlist.push(c);
            else {
                if (strlist.empty()) {
                    flag = 0;
                    break;
                }
                if (c == ')') {
                    if (strlist.top() == '(')
                        strlist.pop();
                    else {
                        flag = 0;
                        break;
                    }
                }
                if (c == ']') {
                    if (strlist.top() == '[')
                        strlist.pop();
                    else {
                        flag = 0;
                        break;
                    }
                }
            }
        }

        if (flag && strlist.empty())
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }

}
