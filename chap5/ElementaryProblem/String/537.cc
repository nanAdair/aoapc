/* Title: 537
 * 考察点：
 * 字符串查找
 * 字符串浮点数转double
 * cout的格式化输出 -- setprecision, setiosflags...*/
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void handle(string &s);
bool isdigit(char s);
bool isspot(char s);
double value(string &s, int index);

int main()
{
    int n;
    cin >> n;
    string temp;
    getline(cin, temp);

    for (int i = 0; i < n; i++) {
        string s;
        getline(cin, s);

        cout << "Problem #" << i + 1<< endl;
        handle(s);
        cout << endl;
    }
}

bool isdigit(char s)
{
    return s >= '0' && s <= '9';
}

bool isspot(char s)
{
    return s == '.';
}

double value(string &s, int index)
{
    double p = 0;
    double factor = 1.0;
    while (isdigit(s[index]) || isspot(s[index])) {
        if (isdigit(s[index])) {
            if ((int)factor >= 1)
                p = p * 10 + s[index] - '0';
            else {
                p = p + (s[index] - '0') * factor;
                factor /= 10;
            }
        }
        if (isspot(s[index])) {
            factor /= 10;
        }
        index++;
    }
    if (s[index] == 'm') 
        p /= 1000;
    if (s[index] == 'k')
        p *= 1000;
    if (s[index] == 'M')
        p *= 1000000;

    return p;
}

void handle(string &s)
{
    string virable[3] = {"P=", "U=", "I="};
    int flagP, flagU, flagI;
    flagP = flagU = flagI = 0;

    double p, u, i;
    p = u = i = 0;

    if (s.find(virable[0]) != string::npos) {
        int index = s.find(virable[0]) + 2;
        p = value(s, index);
        flagP = 1;
    }
    if (s.find(virable[1]) != string::npos) {
        int index = s.find(virable[1]) + 2;
        u = value(s, index);
        flagU = 1;
    }
    if (s.find(virable[2]) != string::npos) {
        int index = s.find(virable[2]) + 2;
        i = value(s, index);
        flagI = 1;
    }

    cout << setprecision(2) << setiosflags(ios::fixed);
    if (flagP && flagU) {
        cout << "I=" << p / u << "A" << endl;
        return;
    }

    if (flagP && flagI) {
        cout << "U=" << p / i << "V" << endl;
        return;
    }

    if (flagI && flagU) {
        cout << "P=" << i * u << "W" << endl;
        return;
    }
}
