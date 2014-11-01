/* Title: 572
 * 考察点：最简单的dfs。
 * 注意可以自己在矩阵外每条边各加一条，这样边界判断就简单许多了，自成边界*/
#include <iostream>
using namespace std;
#define MAX 102

bool visited[MAX][MAX];
bool oil[MAX][MAX];

void dfs(int i, int j);
int main()
{
    int n, m;
    cin >> m >> n;
    while (m && n) {
        for (int i = 0; i < MAX; i++)
            for (int j = 0; j < MAX; j++)
                visited[i][j] = oil[i][j] = 0;

        int count = 0;
        for (int i = 1; i <= m; i++) {
            char c;
            for (int j = 1; j <=n; j++) {
                cin >> c;
                if (c == '@')
                    oil[i][j] = 1;
            }
        }

        for (int i = 1; i <=m; i++) {
            for (int j = 1; j <= n; j++) {
                if (!visited[i][j] && oil[i][j]) {
                    count++;
                    dfs(i, j);
                }
            }
        }

        cout << count << endl;
        cin >> m >> n;
    }
}

void dfs(int i, int j)
{
    if (visited[i][j] || !oil[i][j])
        return;
    visited[i][j] = 1;

    dfs(i-1, j-1); dfs(i-1, j); dfs(i-1, j+1);
    dfs(i,   j-1);              dfs(i,   j+1);
    dfs(i+1, j-1); dfs(i+1, j); dfs(i+1, j+1);
}
