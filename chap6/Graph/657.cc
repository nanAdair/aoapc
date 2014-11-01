/* Title: 657 
 * 考察点：还是dfs
 * 只是多了一个标记过程，dfs标记过后再套一个dfs*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX 52

int label[MAX][MAX];
bool visited_label[MAX][MAX];
bool visited_search[MAX][MAX];
int background[MAX][MAX];

void dfs_label(int i, int j, int to_label);
void dfs_search(int i, int j);
int main()
{
    int m, n;
    cin >> n >> m;

    int round = 1;
    while (m && n) {
        for (int i = 0; i < MAX; i++)
            for (int j = 0; j < MAX; j++)
                label[i][j] = visited_label[i][j] = visited_search[i][j] = background[i][j] = 0;

        char c;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> c;
                if (c == '*')
                    background[i][j] = 1;
                else if (c == 'X')
                    background[i][j] = 2;
            }
        }

        int count = 1;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (background[i][j] != 0 && !visited_label[i][j]) {
                    dfs_label(i, j, count);
                    count++;
                }
            }
        }

        vector<int> dice;
        int find_label = 1;
        while (find_label < count) {
            int num = 0;
            for (int i = 1; i <=m; i++) {
                for (int j = 1; j<= n; j++) {
                    if (label[i][j] == find_label && !visited_search[i][j] && background[i][j] == 2) {
                        dfs_search(i, j);
                        num++;
                    }
                }
            }
            dice.push_back(num);
            find_label++;
        }

        sort(dice.begin(), dice.end());
        cout << "Throw " << round << endl;
        cout << dice[0];
        for (int i = 1; i < dice.size(); i++)
            cout << " " << dice[i];
        cout << endl << endl;
        cin >> n >> m;
        round++;
    }
}

void dfs_label(int i, int j, int to_label)
{
    if (visited_label[i][j] || background[i][j] == 0)
        return;
    visited_label[i][j] = 1;
    label[i][j] = to_label;

    dfs_label(i-1, j, to_label);
    dfs_label(i+1, j, to_label);
    dfs_label(i, j-1, to_label);
    dfs_label(i, j+1, to_label);
}

void dfs_search(int i, int j)
{
    if (visited_search[i][j] || background[i][j] != 2)
        return;
    visited_search[i][j] = 1;

    dfs_search(i-1, j);
    dfs_search(i+1, j);
    dfs_search(i, j-1);
    dfs_search(i, j+1);
}
