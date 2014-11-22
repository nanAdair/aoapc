/* Title: 193
 * 考察点：还是深搜，这里因为其他连接点可以直接确定要染色的点的颜色了
 * 一直TLE是因为该return的地方没有return
 * 深搜TLE*/
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

bool color[110];
vector<int> edges[110];
int num_nodes, num_edges;
int max_res;

void dfs(int num, int black, vector<bool> &res);
int main()
{
    int num;
    cin >> num;
    for (int n = 0; n < num; n++) {
        cin >> num_nodes >> num_edges;
        for (int i = 0; i < 110; i++)
            edges[i].clear();

        for (int i = 0; i < num_edges; i++) {
            int a, b;
            cin >> a >> b;
            edges[a].push_back(b);
            edges[b].push_back(a);
        }

        vector<bool> res;
        max_res = 0;
        dfs(1, 0, res);

        cout << max_res << endl;
        int count = 0;
        for (int i = 0; i < res.size(); i++) {
            if (res[i]) {
                if (++count == max_res)
                    cout << i << endl;
                else
                    cout << i << " ";
            }
        }
    }
}

void dfs(int num, int black, vector<bool> &res)
{
    if (num > num_nodes) {
        if (black > max_res) {
            max_res = black;
            vector<bool> temp(color, color+num_nodes+1);
            res = temp;
        }
            return;
    }
    for (int i = 0; i < edges[num].size(); i++) {
        int j = edges[num][i];
        if (color[j]) {
            dfs(num+1, black, res);
            return;
        }
    }
    color[num] = 1;
    dfs(num+1, black+1, res);
    color[num] = 0;
    dfs(num+1, black, res);
}
