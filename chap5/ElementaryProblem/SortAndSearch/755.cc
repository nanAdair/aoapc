/* Title: 755
 * 考察点：
 * 注意数组最后一个数据，考虑清楚边界情况*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string process(string &s);
void output(vector<string> &phone);
const char table[] = "2223334445556667777888999";
int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        vector<string> phone;
        int num;
        cin >> num;
        for (int j = 0; j < num; j++) {
            string temp, number;
            cin >> temp;
            number = process(temp);
            phone.push_back(number);
        }

        sort(phone.begin(), phone.end());
        output(phone);
        if (i != n - 1)
            cout << endl;
    }
}

string process(string &s)
{
    string res;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '-')
            continue;
        if (s[i] >= 'A' && s[i] <= 'Z')
            res.push_back(table[s[i] - 'A']);
        else
            res.push_back(s[i]);
    }

    res.insert(3, "-");
    return res;
}

void output(vector<string> &phone)
{
    string last = phone[0];
    int sum = 1;
    int flag = 0;

    for (int i = 1; i < phone.size(); i++) {
        if (phone[i] == last) {
            sum++;
            if (i == phone.size() - 1)
                cout << last << " " << sum << endl;
            flag = 1;
        }
        else {
            if (sum == 1) {
                last = phone[i];
                continue;
            }
            flag = 1;
            cout << last << " " << sum << endl;

            last = phone[i];
            sum = 1;
        }
    }

    if (flag == 0)
        cout << "No duplicates." << endl;
}
