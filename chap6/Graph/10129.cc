/* Title: 10129
 * 考察点：与10054基本一样。
 * 注意对于点的入度出度的判断只是充分条件，不是充要条件的。
 * 另外注意mm一条数据这样的特殊数据的判断。*/
#include <iostream>
#include <cstring>
#include <stack>
#include <utility>
using namespace std;

#define MAX 26
int in_order[MAX], out_order[MAX];
int graph[MAX][MAX];
bool flag_in, flag_out;
stack<pair<int, int> > res;

void euler(int u);
bool test_euler(int &start);
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        memset(in_order, 0, sizeof(in_order));
        memset(out_order, 0, sizeof(out_order));
        memset(graph, 0, sizeof(graph));
        flag_in = flag_out = 0;

        for (int j = 0; j < m; j++) {
            string temp;
            cin >> temp;
            int in_num, out_num;
            in_num = temp[0] - 'a';
            out_num = temp[temp.length()-1] - 'a';
            in_order[in_num]++;
            out_order[out_num]++;
            graph[in_num][out_num]++;
        }

        int start;
        if (!test_euler(start)) {
            cout << "The door cannot be opened." << endl;
            continue;
        }

        while (!res.empty())
            res.pop();
        euler(start);
        if (res.size() == m)
            cout << "Ordering is possible." << endl;
        else
            cout << "The door cannot be opened." << endl;
    }
}

bool test_euler(int &start)
{
    for (int i = 0; i < MAX; i++) {
        if (in_order[i] == out_order[i])
            continue;
        else if (in_order[i] == out_order[i]-1) {
            if (!flag_in)
                flag_in = 1;
            else
                return false;
        }
        else if (in_order[i] == out_order[i]+1) {
            if (!flag_out) {
                start = i;
                flag_out = 1;
            }
            else
                return false;
        }
        else
            return false;
    }
    if (!flag_out) {
        for (int i = 0; i < MAX; i++)
            if (in_order[i] == out_order[i] && in_order[i])
                start = i;
    }
    return true;
}

void euler(int u)
{
    for (int v = 0; v < MAX; v++) {
        while (graph[u][v]) {
            graph[u][v]--;
            pair<int, int> temp(u, v);
            euler(v);
            res.push(temp);
        }
    }
}
