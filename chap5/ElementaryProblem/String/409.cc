/* Title: 409
 * 考察点：
 * 字符串匹配，要看清楚题中字串的定义，分割的*/
#include <iostream>
#include <string>
using namespace std;

void setmem(int *a, int value, int num);
void turn_low(string &s);
bool is_valid(string &s, int pos);

int main()
{
    int k, e, num;
    num = 0;
    while (cin >> k >> e) {
        string keywords[20], excuses[20], backup[20], temp;
        for (int i = 0; i < k; i++)
            cin >> keywords[i];
        getline(cin, temp);

        for (int i = 0; i < e; i++) {
            getline(cin, excuses[i]);
            backup[i] = excuses[i];
            turn_low(excuses[i]);
        }

        int max, index[20];
        max = 0;
        setmem(index, -1, 20);

        for (int i = 0; i < e; i++) {
            int count = 0;
            for (int j = 0; j < k; j++) {
                int pos = 0;
                while (excuses[i].find(keywords[j], pos) != string::npos) {
                    int temp = excuses[i].find(keywords[j], pos);
                    if (is_valid(excuses[i], temp - 1) && is_valid(excuses[i], temp + keywords[j].length()))
                        count++;
                    pos += temp + keywords[j].length();
                }
            }

            if (count > max) {
                max = count;
                setmem(index, -1, 20);
                index[0] = i;
            }
            else if (count == max) {
                int k = 0;
                while (index[k] != -1)
                    k++;
                index[k] = i;
            }
        }

        cout << "Excuse Set #" << ++num << endl;
        int k = 0;
        while (index[k] != -1) {
            cout << backup[index[k]] << endl;
            k++;
        }
        cout << endl;
    }
}

void setmem(int *a, int value, int num)
{
    for (int i = 0; i < num; i++)
        a[i] = value;
}

void turn_low(string &s)
{
    for (int i = 0; i < s.length(); i++) {
        if (s[i] <= 'Z' && s[i] >= 'A')
            s[i] = s[i] - 'A' + 'a';
    }
}

bool is_valid(string &s, int pos)
{
    if (pos < 0 || pos >= s.length())
        return 1;
    if ((s[pos] >= 'a' && s[pos] <= 'z') || (s[pos] >= 'A' && s[pos] <= 'Z'))
        return 0;
    return 1;
}
