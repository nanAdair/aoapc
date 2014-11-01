/* Title: 196
 * 考察点：深搜，简单字符串处理*/
#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <cstring>
#include <cstdlib>
using namespace std;

#define MAX 1001
string input[MAX][MAX];
int res[MAX][MAX];
bool update[MAX][MAX];

int cal(int i, int j);
void find_sons(const string &s, vector<pair<int, int> > &node);
void test_find_sons(int i, int j);
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int row, column;
        cin >> column >> row;
        memset(update, 0, sizeof(update));
        for (int j = 1; j <= row; j++) {
            for (int k = 1; k <= column; k++) {
                string temp;
                cin >> temp;
                if (temp[0] != '=') {
                    res[j][k] = atoi(temp.c_str());
                    update[j][k] = 1;
                }
                else
                    input[j][k] = temp;
            }
        }

        for (int j = 1; j <= row; j++) {
            for (int k = 1; k <= column; k++) {
                if (!update[j][k]) {
                    cal(j, k);
                }
            }
        }

        for (int j = 1; j <= row; j++) {
            for (int k = 1; k <= column; k++) {
                if (k == 1)
                    cout << res[j][k];
                else
                    cout << " " << res[j][k];
            }
            cout << endl;
        }
    }
}

int cal(int i, int j)
{
    vector<pair<int, int> > son;
    find_sons(input[i][j], son);

    int sum = 0;
    for (int k = 0; k < son.size(); k++) {
        int n, m;
        n = son[k].first;
        m = son[k].second;
        if (update[n][m])
            sum += res[n][m];
        else 
            sum += cal(n, m);
    }

    res[i][j] = sum;
    update[i][j] = 1;
    return sum;
}

void test_find_sons(int i, int j)
{
    vector<pair<int, int> > son;
    find_sons(input[i][j], son);

    int sum = 0;
    for (int k = 0; k < son.size(); k++) {
        int n, m;
        n = son[k].first;
        m = son[k].second;
        cout << n << " " << m << endl;
    }
}

// 处理字符串，生成子节点坐标
void find_sons(const string &s, vector<pair<int, int> > &node)
{
    int row, column;
    for (int i = 0; i < s.length(); i++) {
        int row, column;
        row = column = 0;
        if (s[i] == '=')
            continue;
        while (s[i] >= 'A' && s[i] <= 'Z') {
            column = column * 26 + s[i] - 'A' + 1;
            i++;
        }
        while (s[i] >= '0' && s[i] <= '9') {
            row = row * 10 + s[i] - '0';
            i++;
        }
        if (s[i] == '+' || i == s.length()) {
            pair<int, int> temp(row, column);
            node.push_back(temp);
        }
    }
}
