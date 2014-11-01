#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define MAX 110
bool flag, circle, found;
//bool edge[MAX][MAX];
vector<int> edge[MAX];
bool visiting[MAX];
int energy[MAX];
int circle_num;

void dfs(int u, int value, int num);
int main()
{
    int n;
    while (cin >> n && n != -1) {
        //memset(edge, 0, sizeof(edge));
        memset(visiting, 0, sizeof(visiting));
        memset(energy, 0, sizeof(energy));

        for (int i = 1; i <= n; i++) {
            int e_val, door_num, number;
            cin >> e_val >> door_num;
            energy[i] = e_val;
            edge[i].clear();
            for (int j = 0; j < door_num; j++) {
                cin >> number;
                edge[i].push_back(number);
                //edge[i][number] = 1;
            }
        }

        found = circle = 0;
        circle_num = 0;
        dfs(1, 100, n);

        if (found)
            cout << "winnable" << endl;
        else
            cout << "hopeless" << endl;
    }
}

void dfs(int u, int value, int num)
{
    int new_value = value + energy[u];
    if (new_value <= 0 && !circle || found) {
        return;
    }

    if (u == num) {
        found = 1;
        return;
    }

    visiting[u] = 1;

    for (int i = 0; i < edge[u].size(); i++) {
       int v = edge[u][i];
        if (visiting[v]) {
            circle = 1;
            circle_num = u;
        }
    }
    //for (int v = 1; v <= num; v++) {
        //if (edge[u][v] == 1) {
            //if (visiting[v]) {
                //circle = 1;
                //circle_num = u;
            //}
        //}
    //}
    for (int i = 0; i < edge[u].size(); i++) {
       int v = edge[u][i];
        if (!visiting[v])
            dfs(v, new_value, num);
    }
    //for (int v = 1; v <= num; v++) {
        //if (edge[u][v] == 1 && !visiting[v])
            //dfs(v, new_value, num);
    //}
    visiting[u] = 0;
    if (u == circle_num)
        circle = 0;
}
