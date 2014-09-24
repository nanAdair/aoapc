/* Title: 400
 * 考察点：就注意用break，不要用return*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <cstdio>
using namespace std;

int find_length(const vector<string> &file_name);
void output(const vector<string> &file_name, int n, int sum);
int main()
{
    int n;
    while (cin >> n) {
        vector<string> file_name;
        for (int i = 0; i < n; i++) {
            string temp;
            cin >> temp;
            file_name.push_back(temp);
        }

        sort(file_name.begin(), file_name.end());

        int max_length = find_length(file_name);

        output(file_name, max_length, n);
    }
}

int find_length(const vector<string> &file_name)
{
    int res = 0;
    for (vector<string>::const_iterator it = file_name.begin(); it != file_name.end(); it++) {
        if (it->length() > res)
            res = it->length();
    }

    return res;
}

void output(const vector<string> &file_name, int n, int sum)
{
    int columns = 62 / (n + 2);
    for (int i = 0; i < 60; i++)
        cout << "-";
    cout << endl;

    int rows = (sum + columns - 1) / columns;

    for (int i = 0; i < rows; i++) {
        int pos;
        for (int j = 0; j < columns; j++) {
            pos = i + j * rows;
            if (pos >= sum) {
                break;
            }
            if (j != columns - 1)
                cout << left << setw(n+2) << file_name[pos];
            else
                cout << left << setw(n) << file_name[pos];
        }
        cout << endl;
    }
}
