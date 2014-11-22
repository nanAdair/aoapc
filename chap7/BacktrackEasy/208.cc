/* Title: 208
 * 考察点：深搜剪枝
 * 直接暴搜TLE，即使是用vector来保存边关系不用数组也会超时
 * 所以因为目标确定了，比较直接的就是想到对于不能达到目标的点就剪掉
 * 所以先用一个深搜，以目标结点为初始，标记所有可达目标的点
 * 然后用这个剪枝就可以很快过了*/
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAX 22
vector<vector<int> > res;
bool visited[MAX];
bool route[MAX];

void dfs(int cur, int target, vector<int> &path, vector<int> connected[]);
bool cmp(const vector<int> &v1, const vector<int> &v2);
void output(int target, int count);
void find_connected(int target, vector<int> connected[]);
int main()
{
    int dest;
    int count = 1;
    while (cin >> dest) {
        int n, m;
        vector<int> connected[MAX];
        while (cin >> n >> m) {
            if (!n && !m)
                break;
            connected[n].push_back(m);
            connected[m].push_back(n);
        }

        memset(route, 0, sizeof(route));
        memset(visited, 0, sizeof(visited));
        visited[dest] = 1;
        route[dest] = 1;
        find_connected(dest, connected);

        res.clear();
        memset(visited, 0, sizeof(visited));

        visited[1] = 1;
        vector<int> path;
        path.push_back(1);
        dfs(1, dest, path, connected);

        sort(res.begin(), res.end(), cmp);

        output(dest, count);
        count++;
    }
}

void output(int target, int count)
{
    cout << "CASE " << count << ":" << endl; 
    for (int i = 0; i < res.size(); i++) {
        for (int j = 0; j < res[i].size(); j++) {
            if (j == 0)
                cout << res[i][j];
            else
                cout << " " << res[i][j];
        }
            cout << endl;
    }

    cout << "There are " << res.size() << " routes from the firestation to streetcorner " << target << "." << endl; 
}

bool cmp(const vector<int> &v1, const vector<int> &v2)
{
    int s1, s2;
    s1 = v1.size();
    s2 = v2.size();

    for (int i = 0; i < s1 && i < s2; i++) {
        if (v1[i] == v2[i])
            continue;
        else 
            return v1[i] < v2[i];
    }
    return s1 < s2;
}

void dfs(int cur, int target, vector<int> &path, vector<int> connected[])
{
    if (cur == target) {
        res.push_back(path);
        return;
    }
    for (int j = 0; j < connected[cur].size(); j++) {
        int i = connected[cur][j];
        if (!visited[i] && route[i]) {
            visited[i] = 1;
            path.push_back(i);
            dfs(i, target, path, connected);
            visited[i] = 0;
            path.erase(path.end()-1);
        }
    }
}

void find_connected(int target, vector<int> connected[])
{
    for (int i = 0; i < connected[target].size(); i++) {
        int j = connected[target][i];
        if (!visited[j]) {
            route[j] = 1;
            visited[j] = 1;
            find_connected(j, connected);
        }
    }
}
