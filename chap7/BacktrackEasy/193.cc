/* Title: 193
 * 深搜TLE*/
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

bool visited[101], connected[101];
bool color[101];
vector<int> edges[101];
void renew(int &max_res, vector<bool> &res, int num_nodes);
//void dfs(int index, int &dyed, int &max_res, vector<bool> &res, int num_nodes, bool flag);
void dfs(int index, int &dyed, int &max_res, vector<bool> &res, int num_nodes, bool flag, int black);
int main()
{
    int num;
    cin >> num;
    for (int n = 0; n < num; n++) {
        int num_nodes, num_edges;
        cin >> num_nodes >> num_edges;
        for (int i = 0; i < 101; i++)
            edges[i].clear();

        for (int i = 0; i < num_edges; i++) {
            int a, b;
            cin >> a >> b;
            edges[a].push_back(b);
            edges[b].push_back(a);
        }

        int dyed = 0;
        int max_res = 0;
        vector<bool> res;
        res.clear();
        memset(visited, 0, sizeof(visited));
        memset(connected, 0, sizeof(connected));
        memset(color, 0, sizeof(color));
        for (int i = 1; i <= num_nodes; i++) {
            if (!connected[i]) {
                dfs(i, dyed, max_res, res, num_nodes, 0, 0);
            }
        }

        cout << max_res << endl;
        for (int i = 0; i < res.size(); i++) {
            if (res[i])
                cout << i+1 << " ";
        }
        cout << endl;
    }
}

void dfs(int index, int &dyed, int &max_res, vector<bool> &res, int num_nodes, bool flag, int black)
{
    if (black + (num_nodes-dyed) <= max_res)
        return;
    connected[index] = 1;

    color[index] = 0;
    visited[index] = 1;
    for (int i = 0; i < edges[index].size(); i++) {
        dyed += 1;
        if (dyed == num_nodes && black > max_res)  {
            max_res = black;
            renew(max_res, res, num_nodes);
            dyed -= 1;
            return;
        }
        if (!visited[edges[index][i]]) {
            dfs(edges[index][i], dyed, max_res, res, num_nodes, 0, black);
        }
    }
    for (int i = 0; i < edges[index].size(); i++) {
        int j = edges[index][i];
        if (visited[j] && color[j])
            flag = 1;
    }
    if (!flag) {
        color[index] = 1;
        visited[index] = 1;
        dyed += 1;
        if (dyed == num_nodes && black > max_res)  {
            max_res = black;
            renew(max_res, res, num_nodes);
            dyed -= 1;
            return;
        }
        for (int i = 0; i < edges[index].size(); i++) {
            if (!visited[edges[index][i]]) {
                dfs(edges[index][i], dyed, max_res, res, num_nodes, 1, black+1);
            }
        }
        dyed -= 1;
    }
    visited[index] = 0;
    color[index] = 0;
}

void renew(int &max_res, vector<bool> &res, int num_nodes)
{
    //int color_black = 0;
    //for (int i = 1; i <= num_nodes; i++)
        //if (color[i])
            //color_black++;
    //if (max_res < color_black) {
        //max_res = color_black;
        vector<bool> temp(color+1, color+num_nodes+1);
        res = temp;
    //}
}
