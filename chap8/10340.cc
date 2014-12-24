/* Title: 10340
 * 考察点：字符串字符匹配*/
#include <iostream>
#include <string>
using namespace std;

char to_litter(char c);
int main()
{
    string s, t;
    while (cin >> s >> t) {
        int i, j;
        i = j = 0;
        while (1) {
            if (i == s.size() || j == t.size())
                break;
            if (s[i]== t[j]){
                i++;
                j++;
            }
            else
                j++;
        }
        if (i < s.size())
            cout << "No" << endl;
        else {
            cout << "Yes"  << endl;
        }
    }
}
