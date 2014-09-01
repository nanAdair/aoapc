/* Title: 10115
 * 考察点：
 * 字符串 erase(), insert()*/
#include <iostream>
#include <string>
using namespace std;

bool edit(string &s, const string &src, const string &target);
int main()
{
    int n;
    while (cin >> n) {
        if (n == 0)
            break;
        string src[10], target[10], temp, text;
        getline(cin, temp);
        for (int i = 0; i < n; i++) {
            getline(cin, src[i]);
            getline(cin, target[i]);
        }
        getline(cin, text);

        for (int i = 0; i < n; i++) {
            while (edit(text, src[i], target[i]))
                ;
        }

        cout << text << endl;
    }
}

bool edit(string &s, const string &src, const string &target)
{
    int pos = s.find(src);
    if (pos == string::npos)
        return 0;
    s.erase(s.begin() + pos, s.begin() + pos + src.length());
    s.insert(pos, target);
    return 1;
}
