/* Title: 401
 * 考察点：
 * 回文串的判断 -- 两端向中间逐字符比对
 * 已知变化规则，提前打表*/
#include <iostream>
#include <string>
using namespace std;

bool is_palindrome(string);
bool is_mirror(string);

int main()
{
    string s;
    while (cin >> s) {
        int flagp, flagm;
        flagp = is_palindrome(s);
        flagm = is_mirror(s);

        cout << s << " -- ";
        if (flagp && flagm)
            cout << "is a mirrored palindrome." << endl;
        else if (!flagp && flagm)
            cout << "is a mirrored string." << endl;
        else if (flagp && !flagm)
            cout << "is a regular palindrome." << endl;
        else
            cout << "is not a palindrome." << endl;
        cout << endl;
    }
}

bool is_palindrome(string s)
{
    for (int i = 0, j = s.length() - 1; i <= j; i++, j--) {
        if (s[i] != s[j])
            return 0;
    }
    return 1;
}

bool is_mirror(string s)
{
    string character("ABCDEFGHIJKLMNOPQRSTUVWXYZ123456789");
    string reverse("A   3  H L JM O   2TUVWXY51SE Z  8 ");

    for (int i = 0, j = s.length() - 1; i <= j; i++, j--) {
        int pos1 = character.find(s[i]);
        int pos2 = reverse.find(s[j]);

        if (pos1 != pos2)
            return 0;
    }
    return 1;
}
