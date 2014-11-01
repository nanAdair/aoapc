/* Title: 10054
 * 考察点：欧拉回路，dfs加栈记录*/
#include <iostream>
#include <cstring>
#include <stack>
#include <utility>
using namespace std;

#define MAX 51

int edge[MAX][MAX];
stack<pair<int, int> > res;

void euler(int u);
bool test_edge(int &begin_colr);
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        memset(edge, 0, sizeof(edge));
        for (int j = 0; j < m; j++) {
            int p, q;
            cin >> p >> q;
            edge[p][q]++;
            edge[q][p]++;
        }

        cout << "Case #" << i+1 << endl;
        int begin_color = 0;
        if (!test_edge(begin_color)) {
            cout << "some beads may be lost" << endl;
            if (i != n-1)
                cout << endl;
            continue;
        }

        while (!res.empty())
            res.pop();
        euler(begin_color);

        while (!res.empty()) {
            pair<int, int> temp = res.top();
            cout << temp.first << " " << temp.second << endl;
            res.pop();
        }
        if (i != n-1)
            cout << endl;
    }
}

void euler(int u)
{
    for (int v = 1; v < MAX; v++) {
        while (edge[u][v]) {
            pair<int, int> temp(u, v);
            edge[u][v]--;
            edge[v][u]--;

            euler(v);

            res.push(temp);
        }
    }
}

bool test_edge(int &begin_color)
{
    for (int i = 1; i < MAX; i++) {
        int sum = 0;
        for (int j = 1; j < MAX; j++) {
            sum += edge[i][j];
        }
        if (sum && !begin_color)
            begin_color = i;
        if (sum % 2)
            return false;
    }

    return true;
}
