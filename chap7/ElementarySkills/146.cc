/* Title: 146
 * 考察点：求字符串的后继
 * 注意考虑字符可以相同的情况，在交换后不能再逆序了，而要排序*/
#include <iostream>
#include <algorithm>
using namespace std;

void swap(string &s, int l, int r);
int main()
{
    string s;
    while (cin >> s) {
        if (s == "#")
            break;
        int i = s.size() - 1;
        while (i > 0 && s[i-1] >= s[i])
            i--;
        if (i == 0) {
            cout << "No Successor" << endl;
            continue;
        }

        char min_char = 'z'+1;
        int index, j;
        for (j = i; j < s.size(); j++) {
            // 字符可以相同，所以必须确保要至少大1
            if (min_char > s[j] && s[j] > s[i-1]) {
                min_char = s[j];
                index = j;
            }
        }

        swap(s, i-1, index);
        sort(s.begin() + i, s.end());

        cout << s << endl;
    }
}

void swap(string &s, int l, int r)
{
    char temp = s[l];
    s[l] = s[r];
    s[r] = temp;
}
