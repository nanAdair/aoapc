#include <iostream>
#include <sstream>
#include <cctype>
using namespace std;

#define MAX 82

char maze[MAX][MAX];
int si, sj;

void dfs(int i, int j);
bool is_end(const string &s);
int main()
{
    int num;
    cin >> num;
    string temp;
    getline(cin, temp);

    for (int k = 0; k < num; k++) {
        for (int i = 0; i < MAX; i++)
            for (int j = 0; j < MAX; j++)
                maze[i][j] = 0;

        int row = 1;
        int column = 1;
        while (1) {
            getline(cin, temp);
            char c;
            column = 1;
            for (int i = 0; i < temp.length(); i++) {
                c = temp[i];
                maze[row][column] = c;
                if (c == '*') {
                    si = row;
                    sj = column;
                }
                column++;
            }
            row++;
            if (is_end(temp))
                break;
        }

        for (int i = 1; i < MAX; i++)
            for (int j = 1; j < MAX; j++)
                if (maze[i][j] == '*')
                    dfs(i, j);

        for (int i = 1; i < row; i++) {
            cout << maze[i]+1 << endl;
        }
    }
}

bool is_end(const string &s)
{
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != '_')
            return 0;
    }
    return 1;
}

void dfs(int i, int j)
{
    if (isprint(maze[i][j]) && maze[i][j] != ' ' && maze[i][j] != '*')
        return;

    maze[i][j] = '#';
    dfs(i-1, j);
    dfs(i+1, j);
    dfs(i, j-1);
    dfs(i, j+1);
}
