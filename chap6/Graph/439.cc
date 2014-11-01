/* Title: 439
 * 考察点：最简单的bfs。与572基本相同
 * 注意边界判断的方法，不用在调用时判断而是自己做判断*/
#include <iostream>
#include <string>
#include <queue>
using namespace std;

#define MAX 8
bool visited[MAX][MAX];

int si, sj, ei, ej;
int depth;

class pos
{
public:
    pos() {}
    pos(int a, int b, int c):
        i(a),
        j(b),
        d(c) {}

    int i;
    int j;
    int d;
};

bool scope(int i, int j);
void bfs(int a, int b, int c);
int main()
{
    string start, end;
    while (cin >> start >> end) {
        si = start[1] - '1';
        sj = start[0] - 'a';
        ei = end[1] - '1';
        ej = end[0] - 'a';

        for (int i = 0; i < MAX; i++)
            for (int j = 0; j < MAX; j++)
                visited[i][j] = 0;

        depth = 0;
        bfs(si, sj, 0);

        cout << "To get from " << start << " to " << end << " takes " << depth << " knight moves." << endl;
    }
}

void bfs(int a, int b, int c)
{
    queue<pos> chessboard;
    pos element = pos(a, b, c);
    chessboard.push(element);

    while (!chessboard.empty()) {
        pos temp = chessboard.front();
        int i, j, d;
        i = temp.i;
        j = temp.j;
        d = temp.d;
        if (!scope(i, j) || visited[i][j]) {
            chessboard.pop();
            continue;
        }
        if (i == ei && j == ej) {
            depth = d;
            break;
        }

        visited[i][j] = 1;
        chessboard.push(pos(i-1, j-2, d+1)); chessboard.push(pos(i-2, j-1, d+1));
        chessboard.push(pos(i-1, j+2, d+1)); chessboard.push(pos(i-2, j+1, d+1));
        chessboard.push(pos(i+1, j-2, d+1)); chessboard.push(pos(i+2, j-1, d+1));
        chessboard.push(pos(i+1, j+2, d+1)); chessboard.push(pos(i+2, j+1, d+1));
    }
}

bool scope(int i, int j)
{
    if (i < 0 || i >= MAX || j < 0 || j >= MAX)
        return 0;
    return 1;
}
