/* Title: 10098
 * 考察点：和146一样，只是输出全部排列而已*/
#include <iostream>
#include <algorithm>
using namespace std;

int find_next(string s);
void swap(string &s, int l, int r);
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        sort(s.begin(), s.end());
        cout << s << endl;
        int index;
        while (index = find_next(s)) {
            if (index == 0)
                break;

            char min_char = 'z' + 1;
            int min_index, j;
            for (j = index; j < s.size(); j++) {
                if (min_char > s[j] && s[j] > s[index-1]) {
                    min_char = s[j];
                    min_index = j;
                }
            }

            swap(s, index-1, min_index);
            sort(s.begin() + index, s.end());
            cout << s << endl;
        }
        cout << endl;
    }
}

int find_next(string s)
{
    int i = s.size() - 1;
    while (i > 0 && s[i-1] >= s[i])
        i--;
    return i;
}

void swap(string &s, int l, int r)
{
    char temp = s[l];
    s[l] = s[r];
    s[r] = temp;
}
