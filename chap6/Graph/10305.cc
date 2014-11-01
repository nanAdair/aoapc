/* Title: 10305
 * 考察点：拓扑排序的简单实现*/
#include <iostream>
#include <stack>
#include <cstring>
using namespace std;

#define MAX 101

bool edge[MAX][MAX];
int visited[MAX];

bool toposort(stack<int> &res, int num);
bool dfs(int u, stack<int> &res, int num);
int main()
{
    int n, m;
    while (cin >> n >> m) {
        if (!n && !m)
            break;
        stack<int> res;
        memset(edge, 0, sizeof(edge));
        memset(visited, 0, sizeof(visited));

        for (int i = 0; i < m; i++) {
            int p, q;
            cin >> p >> q;
            edge[p][q] = 1;
        }

        toposort(res, n);

        int count = 0;
        while (!res.empty()) {
            cout << res.top();
            count++;
            if (count < n)
                cout << " ";
            res.pop();
        }
        cout << endl;
    }
}

bool toposort(stack<int> &res, int num)
{
    for (int i = 1; i <= num; i++) {
        if (!visited[i]) {
            if(!dfs(i, res, num))
                return false;
        }
    }

    return true;
}

bool dfs(int u, stack<int> &res, int num)
{
    visited[u] = -1;
    for (int i = 1; i <= num; i++) {
        if (edge[u][i]) {
            if (visited[i] < 0)
                return false;
            else if (!visited[i]) {
                if(!dfs(i, res, num))
                    return false;
            }
        }
    }
    visited[u] = 1;
    res.push(u);

    return true;
}
