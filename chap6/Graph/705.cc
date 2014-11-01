/* Title: 705
 * 考察点：几何转换+bfs/dfs
 * 这道题完全没有思路，看了题解以后知道怎么转换后然后写出来的
 * 写的是bfs不过dfs可以写得更简单些
 * 另外memset对二维数组可以直接像对一维的那样初始化*/
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

#define MAX 77
bool maze[MAX*3][MAX*3];
bool visited[MAX*3][MAX*3];

int bfs(int i, int j, bool &flag, int h, int w);
int main()
{
    int w, h;
    int round = 1;
    while (cin >> w >> h && w && h) {
        memset(maze, 0, sizeof(maze));
        memset(visited, 0, sizeof(visited));
        for (int i = 0; i <= w*3+1; i++)
            maze[0][i] = maze[h*3+1][i] = 1;
        for (int i = 0; i <= h*3+1; i++)
            maze[i][0] = maze[i][w*3+1] = 1;

        char c;
        for (int i = 1; i <= h; i++) {
            for (int j = 1; j <= w; j++) {
                cin >> c;
                if (c == '\\') {
                    maze[i*3-2][j*3-2] = maze[i*3-1][j*3-1] = maze[i*3][j*3] = 1;
                }
                else
                    maze[i*3-2][j*3] = maze[i*3-1][j*3-1] = maze[i*3][j*3-2] = 1;
            }
        }

        int num, max;
        max = 0;
        int count = 0;
        for (int i = 1; i <= h*3; i++) {
            for (int j = 1; j <= w*3; j++) {
                if (maze[i][j] == 0 && !visited[i][j]) {
                    bool flag = 1;
                    num = bfs(i, j, flag, h, w);
                    if (flag) {
                        max = max > num ? max : num;
                        count++;
                    }
                }
            }
        }
        cout << "Maze #" << round << ":" << endl;
        if (count)
            cout << count << " Cycles; the longest has length " << max/3 << "." << endl << endl;
        else
            cout << "There are no cycles." << endl << endl;
        round++;
    }
}

class Node
{
public:
    Node() {}
    Node(int i, int j):
        a(i),
        b(j) {}

    int a;
    int b;
};

int bfs(int i, int j, bool &flag, int h, int w)
{
    queue<Node> path;
    path.push(Node(i, j));
    visited[i][j] = 1;

    int res = 0;
    while (!path.empty()) {
        Node temp = path.front();
        int x = temp.a;
        int y = temp.b;

        if (flag && (x-1 == 0 || x+1 == h*3+1 || y-1 == 0 || y+1 == w*3+1))
            flag = 0;

        if (!visited[x-1][y] && !maze[x-1][y]) {
            visited[x-1][y] = 1;
            path.push(Node(x-1, y));
        }
        if (!visited[x+1][y] && !maze[x+1][y]) {
            visited[x+1][y] = 1;
            path.push(Node(x+1, y));
        }
        if (!visited[x][y-1] && !maze[x][y-1]) {
            visited[x][y-1] = 1;
            path.push(Node(x, y-1));
        }
        if (!visited[x][y+1] && !maze[x][y+1]) {
            visited[x][y+1] = 1;
            path.push(Node(x, y+1));
        }

        path.pop();
        res++;
    }

    return res;
}
