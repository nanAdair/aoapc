/* Title: 216
 * 考察点：简单的排列构造，可以简单用已有的最短距离剪枝
 * 注意深搜的时候之前造成的一系列影响，全都要设置回去*/
#include <iostream>
#include <utility>
#include <vector>
#include <stack>
#include <cmath>
#include <cstring>
#include <iomanip>
using namespace std;

#define MAX 8
#define DD 0x7fffffff
double distanc[MAX][MAX];
stack<int> res;
bool visited[MAX];
double min_length;

void find_min(int depth, int n, double dis, stack<int> &store);
void output(vector<pair<int, int> > &vec, int num, int round);
int main()
{
    int n;
    int round = 1;
    while (cin >> n && n) {
        vector<pair<int, int> > nodes;
        pair<int, int> temp;
        for (int i = 0; i < n; i++) {
            cin >> temp.first >> temp.second;
            nodes.push_back(temp);
        }
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                double d = sqrt(pow(nodes[i].first - nodes[j].first, 2) + pow(nodes[i].second - nodes[j].second, 2));
                distanc[i][j] = distanc[j][i] = d + 16;
            }
        }

        memset(visited, 0, sizeof(visited));
        min_length = DD;
        stack<int> store;
        for (int i = 0; i < n; i++) {
            store.push(i);
            visited[i] = 1;
            find_min(1, n, 0, store);
            visited[i] = 0;
            store.pop();
        }

        vector<pair<int, int> > vec;
        while (!res.empty()) {
            int now = res.top();
            vec.push_back(nodes[now]);
            res.pop();
        }

        output(vec, n, round);
        round++;
    }
}

void output(vector<pair<int, int> > &vec, int num, int round)
{
    cout << fixed << setprecision(2);
    cout << "**********************************************************" << endl;
    cout << "Network #" << round << endl;
    for (int i = 0; i < num-1; i++) {
        cout << "Cable requirement to connect ";
        cout << "(" << vec[i].first << "," << vec[i].second << ")";
        cout << " to ";
        cout << "(" << vec[i+1].first << "," << vec[i+1].second << ")";
        cout << " is ";
        cout << sqrt(pow(vec[i].first - vec[i+1].first, 2) + pow(vec[i].second - vec[i+1].second, 2)) + 16;
        cout << " feet.";
        cout << endl;
    }
    cout << "Number of feet of cable required is " << min_length << "." << endl;
}

void find_min(int depth, int n, double dis, stack<int> &store)
{
    if (depth == n) {
        if (dis < min_length) {
            min_length = dis;
            res = store;
            return;
        }
    }
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int last = store.top();
            dis += distanc[last][i];
            if (dis < min_length) {
                store.push(i);
                visited[i] = 1;
                find_min(depth+1, n, dis, store);
                store.pop();
                visited[i] = 0;
            }
            dis -= distanc[last][i];
        }
    }
}
