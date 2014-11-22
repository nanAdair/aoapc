/* Title: 539
 * 考察点：简单的深搜，以前是用点来判断是否访问过，这个是用边
 * 要注意是无向边*/
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define MAX 25
vector<int> paths[MAX];
bool visited[MAX][MAX];
void find_max(int num, int &max_length, int cur);
int main()
{
    int n, m;
    while (cin >> n >> m && n) {
        for (int i = 0; i < MAX; i++)
            paths[i].clear();
        memset(visited, 0, sizeof(visited));
        for (int i = 0; i < m; i++) {
            int p, q;
            cin >> p >> q;
            paths[p].push_back(q);
            paths[q].push_back(p);
        }
        int max_length = 0;
        for (int i = 0; i < n; i++)
            find_max(i, max_length, 0);
        cout << max_length << endl;
    }
}

void find_max(int num, int &max_length, int cur)
{
    for (int i = 0; i < paths[num].size(); i++) {
        if (visited[num][paths[num][i]])
            continue;
        cur += 1;
        max_length = max_length > cur ? max_length : cur;
        visited[num][paths[num][i]] = 1;
        visited[paths[num][i]][num] = 1;
        find_max(paths[num][i], max_length, cur);
        visited[num][paths[num][i]] = 0;
        visited[paths[num][i]][num] = 0;
        cur -= 1;
    }
}
