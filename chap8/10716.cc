/* Title: 10716
 * 考察点：贪心，交换相邻字符生成回文串
 * 只要把最两边的字符匹配即可，然后递归进行*/
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

bool is_palindrome(string t) 
{
    int number[26];
    memset(number, 0, sizeof(number));
    for (int i = 0; i < t.size(); i++) {
        if (t[i] >= 'A' && t[i] <= 'Z')
            t[i] = t[i] - 'A' + 'a';
        number[t[i] - 'a'] += 1;
    }
    int odd = 0;
    for (int i = 0; i < 26; i++) 
        if (number[i] % 2)
            odd++;
    return odd < 2;
}

int solve(string t)
{
    int l, r;
    l = 0;
    r = t.size() - 1;
    int cnt = 0;
    while (l < r) {
        for (int i = 0; (l + i) < r; i++) {
            if (t[l+i] == t[r]) {
                for (int j = l+i; j > l; j--) {
                    if (t[j] == t[j-1])
                        continue;
                    swap(t[j], t[j-1]);
                    cnt += 1;
                }
                break;
            }
            else if (t[r-i] == t[l]) {
                for (int j = r-i; j < r; j++) {
                    if (t[j] == t[j+1])
                        continue;
                    swap(t[j], t[j+1]);
                cnt += 1;
                }
                break;
            }
        }
        if (t[l] == t[r]) {
            l++;
            r--;
        }
    }
    return cnt;
}
int main()
{
    int num;
    cin >> num;
    for (int n = 0; n < num; n++) {
        string tmp;
        cin >> tmp;
        if (!is_palindrome(tmp)) {
            cout << "Impossible" << endl;
            continue;
        }
        int res = solve(tmp);
        cout << res << endl;
    }
}
