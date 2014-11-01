/* Title: 10557 
 * 考察点：求点到点的距离
 * 算法：dfs，判断是否出现了形成环的点，如果这个圈是正数，则判断从该点到目标点是否可
 * 达;同时dfs一路更新到目标点可能出现的值。只要中间出现<0，则截枝。*/
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define MAX 110

int energy[MAX];
int dis[MAX];
vector<int> v[MAX];
bool visited[MAX];
bool ok;

void dfs(int u, int val, int num);
void is_rechable(int s, int t, bool &flag);
int main()
{
    int n;
    while (cin >> n && n != -1) {
        for (int i = 1; i <= n; i++) {
            int e_val, door_num, number;
            cin >> e_val >> door_num;
            energy[i] = e_val;
            v[i].clear();
            for (int j = 0; j < door_num; j++) {
                cin >> number;
                v[i].push_back(number);
            }
        }

        ok = 0;
        memset(dis, 0, sizeof(dis));
        dfs(1, 100, n);

        if (ok)
            cout << "winnable" << endl;
        else
            cout << "hopeless" << endl;
    }
}

void dfs(int u, int val, int num)
{
    if (ok)
        return;
    if (u == num && val > 0) {
        ok = 1;
        return;
    }
    if (val <= 0)
        return;
    dis[u] = val;

    for (int i = 0; i < v[u].size(); i++) {
        int node = v[u][i];

        // 判断是否是成环点，只需要判断之前是否更新过此点的距离
        if (dis[node] != 0 && energy[node] + val > dis[node]) {
            memset(visited, 0, sizeof(visited));
            bool flag = 0;
            is_rechable(node, num, flag);
            if (flag) {
                ok = 1;
                return;
            }
        }
        if (dis[node] == 0)
            dfs(node, val + energy[node], num);
    }
}

void is_rechable(int s, int t, bool &flag)
{
    if (flag)
        return;
    visited[s] = 1;
    if (s == t) {
        flag = 1;
        return;
    }
    for (int i = 0; i < v[s].size(); i++) {
        if (!visited[v[s][i]])
            is_rechable(v[s][i], t, flag);
    }
}
