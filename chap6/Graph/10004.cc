/* Title: 10004
 * 考察点：二部图匹配。很简单的bfs
 * 用map把边的关系存起来，然后bfs查看每个顶点的联通顶点是否染上相同色即可
 * map可以直接放vector的对象，会拷贝*/
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <cstring>
using namespace std;

int main()
{
    int n;

    while (cin >> n && n) {
        int m;
        bool flag = 1;
        map<int, vector<int> > edge;
        int color[200];
        memset(color, -1, sizeof(color));

        cin >> m;
        for (int i = 0; i < m; i++) {
            int n1, n2;
            cin >> n1 >> n2;
            if (edge.find(n1) == edge.end()) {
                vector<int> temp;
                temp.push_back(n2);
                edge[n1] = temp;
            }
            else
                edge[n1].push_back(n2);
            if (edge.find(n2) == edge.end()) {
                vector<int> temp;
                temp.push_back(n1);
                edge[n2] = temp;
            }
            else
                edge[n2].push_back(n1);
        }

        queue<int> graph;
        color[0] = 1;
        graph.push(0);

        while (!graph.empty()) {
            int to_dye = graph.front();
            vector<int> temp = edge[to_dye];

            for (vector<int>::iterator it = temp.begin(); it != temp.end(); it++) {
                if (color[*it] == -1) {
                    color[*it] = color[to_dye] ? 0 : 1;
                    graph.push(*it);
                }
                else {
                    if (color[*it] == color[to_dye]) {
                        flag = 0;
                        break;
                    }
                    else
                        continue;
                }
            }
            if (!flag)
                break;
            graph.pop();
        }

        if (flag)
            cout << "BICOLORABLE." << endl;
        else
            cout << "NOT BICOLORABLE." << endl;
    }
}
