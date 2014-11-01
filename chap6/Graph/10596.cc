/* Title: 10596
 * 考察点：和10129一样都是判断是否存在欧拉回路，但是题目略坑
 * 只要在后面给出的路径是欧拉回路即可，不用把所有点走一遍*/
#include <iostream>
#include <stack>
#include <utility>
#include <cstring>
using namespace std;

#define MAX 250

int graph[MAX][MAX];
int visited[MAX];
int order[MAX];

void euler(int u);
bool test_euler(int num);
int main()
{
    int n, r;
    while (cin >> n >> r) {
        memset(graph, 0, sizeof(graph));
        memset(visited, 0, sizeof(visited));
        memset(order, 0, sizeof(order));

        for (int i = 0; i < r; i++) {
            int p, q;
            cin >> p >> q;
            graph[p][q] = graph[q][p] = 1;
            order[p]++;
            order[q]++;
        }
        if (r == 0) {
            cout << "Not Possible" << endl;
            continue;
        }

        if(!test_euler(n)) {
            cout << "Not Possible" << endl;
            continue;
        }

        memset(visited, 0, sizeof(visited));
        euler(0);

        bool flag = 1;
        int i;
        for (i = 0; i < n; i++) {
            // 注意这里要判断交叉口i有没有路可达
            if (!visited[i] && order[i]) {
                flag = 0;
                break;
            }
        }
        if (flag)
            cout << "Possible" << endl;
        else
            cout << "Not Possible" << endl;

    }
}

bool test_euler(int num)
{
    for (int i = 0; i < num; i++) {
        if (order[i] % 2)
            return 0;
    }
    return 1;
}

void euler(int u)
{
    visited[u] = 1;
    for (int v = 0; v < MAX; v++) {
        if (!visited[v] && graph[u][v]) 
            euler(v);
    }
}
