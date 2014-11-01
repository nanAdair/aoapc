/* Title: 10047
 * 考察点：优先队列+bfs
 * 算法思路：
 *  一开始想通过dfs来找出所有可达路径里面最小的，此时每个点只通过一次，然后再以最后的
 *  终点为标志走够使得颜色回到绿色的步数和时间。后来才发现其实最短的时间会出现在中间
 *  某一步重复走。然后就计划是把路径记下来，遍历这条路上面每一个点，让他们走补充的那
 *  几步，然后找到最短时间。应该也是有问题的，因为最短时间和最短步数不一定一致
 *  后来看了题解，用bfs来找最短路径，同时因为是要求时间的，要用关于时间的优先队列来保
 *  存。其实开始就想着用bfs来做的，但是开始觉得bfs可以找到一下子找到路径上的最短并不
 *  一定是时间上最短，就放弃这个想法。没有考虑到可以用优先队列，且优先队列的index是按
 *  照时间来排序的。同时注意此题中对于一个点是否visited的判断，不再是简单的二维，而是
 *  加入了方向和颜色的信息*/

#include <iostream>
#include <cstring>
#include <queue>
#include <cstdlib>
using namespace std;

#define MAX 27
bool graph[MAX][MAX];
int sx, sy, tx, ty;
int direct[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
bool visited[MAX][MAX][4][5];

class pos
{
public:
    pos() {}
    pos(int a, int b, int c, int d, int e):
        x(a),
        y(b),
        direction(c),
        time(d),
        color(e) {}

    int x;
    int y;
    int direction;
    int time;
    int color;

    friend bool operator<(const pos &a, const pos &b);
};

/* 这里要是最小的在最前 */
bool operator<(const pos &a, const pos &b)
{
    return a.time > b.time;
}

int bfs();
int main()
{
    int n, m;
    int count = 1;
    while (cin >> n >> m) {
        if (!n || !m)
            break;
        char c;
        memset(graph, 0, sizeof(graph));
        memset(visited, 0, sizeof(visited));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> c;
                if (c == '.' || c == 'S' || c == 'T')
                    graph[i][j] = 1;
                if (c == 'S') {
                    sx = i;
                    sy = j;
                }
                if (c == 'T') {
                    tx = i;
                    ty = j;
                }
            }
        }

        int length;
        length = bfs();
        if (count > 1)
            cout << endl;
        cout << "Case #" << count << endl;
        if (length == 0)
            cout << "destination not reachable" << endl;
        else
            cout << "minimum time = " << length << " sec" << endl;
        count++;
    }
}

int bfs()
{
    priority_queue<pos> path;
    path.push(pos(sx, sy, 0, 0, 0));

    while (!path.empty()) {
        pos temp = path.top();
        int nx, ny, nd, nc, nt;
        nx = temp.x;
        ny = temp.y;
        nd = temp.direction;
        nc = temp.color;
        nt = temp.time;
        if (temp.x == tx && temp.y == ty && temp.color == 0)
            return temp.time;
        if (visited[nx][ny][nd][nc] || !graph[nx][ny]) {
            path.pop();
            continue;
        }
        visited[nx][ny][nd][nc] = 1;

        for (int k = 0; k < 4; k++) {
            int mx, my, md, mc, mt;
            mt = nt + 1;
            if (nd == k)
                mt = mt;
            else if (abs(nd - k) % 2)
                mt = mt+1;
            else
                mt = mt+2;
            mx = nx + direct[k][0];
            my = ny + direct[k][1];
            md = k;
            mc = (nc + 1) % 5;
            if (!visited[mx][my][md][mc])
                path.push(pos(mx, my, md, mt, mc));
        }
        path.pop();
    }

    return 0;
}

//int bfs()
//{
    //queue<pos> path;
    //path.push(pos(sx, sy, 0));
    //int time = 0;

    //while (!path.empty()) {
        //pos temp = path.front();
        //visited[temp.x][temp.y] = 1;

        
    //}
//}

//void dfs(int i, int j, int direction, int time, int depth)
//{
    //if (i == tx && j == ty && depth % 5 == 0) {
        //if (time < min_time) {
            //min_time = time;
            //cout << time << endl;
        //}
        //return;
    //}
    //if (visited[i][j][direction][depth % 5] || !graph[i][j])
        //return;
    //visited[i][j][direction][depth % 5] = 1;

    //for (int k = 0; k < 4; k++) {
        //int time_add;
        //if (direction == k)
            //time_add = 0;
        //else if (abs(direction - k) % 2)
            //time_add = 1;
        //else
            //time_add = 2;
        //dfs(i+direct[k][0], j+direct[k][1], k, time+time_add+1, depth+1);
    //}
    //visited[i][j][direction][depth % 5] = 0;
//}
