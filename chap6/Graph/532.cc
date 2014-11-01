/* Title: 532
 * 考察点：同439 bfs*/
#include <iostream>
#include <queue>
using namespace std;

#define MAX 32

class pos
{
public:
    pos() {}
    pos(int a, int b, int c, int d):
        x(a),
        y(b),
        z(c),
        dd(d) {}
    int x;
    int y;
    int z;
    int dd;
};

bool visited[MAX][MAX][MAX], maze[MAX][MAX][MAX];
int sx, sy, sz, ex, ey, ez;
int depth;

void bfs(int a, int b, int c);
int main()
{
    int m, n, r;
    cin >> m >> n >> r;

    while (m && n && r) {
        for (int i = 0; i < MAX; i++)
            for (int j = 0; j < MAX; j++)
                for (int k = 0; k < MAX; k++)
                    visited[i][j][k] = maze[i][j][k] = 0;

        char c;
        for (int i = 1; i <=m; i++) {
            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= r; k++) {
                    cin >> c;
                    if (c == 'S') {
                        sx = i;
                        sy = j;
                        sz = k;
                        maze[i][j][k] = 1;
                    }
                    else if (c == '.')
                        maze[i][j][k] = 1;
                    else if (c == 'E') {
                        ex = i;
                        ey = j;
                        ez = k;
                        maze[i][j][k] = 1;
                    }
                }
            }
        }

        depth = 0;
        bfs(sx, sy, sz);
        if (depth == 0)
            cout << "Trapped!" << endl;
        else {
            cout << "Escaped in " << depth << " minute(s)." << endl;
        }
        cin >> m >> n >> r;
    }
}

void bfs(int a, int b, int c)
{
    queue<pos> flour;
    pos element = pos(a, b, c, 0);
    flour.push(element);

    while (!flour.empty()) {
        pos temp = flour.front();
        int i, j, k, d;
        i = temp.x;
        j = temp.y;
        k = temp.z;
        d = temp.dd;
        if (maze[i][j][k] == 0 || visited[i][j][k]) {
            flour.pop();
            continue;
        }
        if (i == ex && j == ey && k == ez) {
            depth = d;
            break;
        }

        visited[i][j][k] = 1;
        flour.push(pos(i+1, j, k, d+1)); flour.push(pos(i-1, j, k, d+1));
        flour.push(pos(i, j+1, k, d+1)); flour.push(pos(i, j-1, k, d+1));
        flour.push(pos(i, j, k+1, d+1)); flour.push(pos(i, j, k-1, d+1));
    }
}
