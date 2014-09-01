/* Title: 10010
 * 考察点：
 * 字符串构造 -- 开空间，然后逐字符赋值*/
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

#define MAX 50
void find_pos(char [][MAX], string, int, int);
bool is_pos(char grid[][MAX], string s, int r, int c, int x, int y);
//string turn_low(string s);
void turn_low(string &s);
int main()
{
    int n, count = 0;
    cin >> n;
    for (int k = 0; k < n; k++) {
        int row, column;
        cin >> row >> column;
        
        char grid[MAX][MAX];
        for (int i = 0; i < row; i++) {
            string s;
            cin >> s;
            //s = turn_low(s);
            turn_low(s);
            for (int j = 0; j < column; j++)
                grid[i][j] = s[j];
        }

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++)
                cout << grid[i][j];
            cout << endl;
        }


        int number;
        cin >> number;
        for (int i = 0; i < number; i++) {
            string s;
            cin >> s;
            turn_low(s);
            find_pos(grid, s, row, column);
        }
        if (++count < n)
            cout << endl;
    }
}

/* 按引用传递对象 */
void turn_low(string &s)
{
    for (int i = 0; i < s.length(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] = s[i] - 'A' + 'a';
    }
}

//string turn_low(string s)
//{
    //string t(s);
    //for (int i = 0; i < s.length(); i++) {
        //if (s[i] >= 'A' && s[i] <= 'Z')
            //t[i] = t[i] - 'A' + 'a';
    //}

    //return t;
//}

void find_pos(char grid[][MAX], string s, int r, int c)
{
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (s[0] != grid[i][j])
                continue;
            if (is_pos(grid, s, r, c, i, j)) {
                cout << i + 1 << " " << j + 1 << endl;
                return;
            }
        }
    }
}

bool is_pos(char grid[][MAX], string s, int r, int c, int x, int y)
{
    int flag = 0;
    int leng = s.length();
    string t(leng, ' ');

    /* West */
    if (y + 1 >= leng) {
        for (int i = 0; i < leng; i++)
            t[i] = grid[x][y - i];
        if (!strcmp(s.c_str(), t.c_str()))
            return 1;
    }

    /* NorthWest */
    if ( y + 1 >= leng && x + 1 >= leng) {
        for (int i = 0; i < leng; i++)
            t[i] = grid[x - i][y - i];
        if (!strcmp(s.c_str(), t.c_str()))
            return 1;
    }

    /* North */
    if (x + 1 >= leng) {
        for (int i = 0; i < leng; i++)
            t[i] = grid[x - i][y];
        if (!strcmp(s.c_str(), t.c_str()))
            return 1;
    }

    /* NorthEast */
    if (x + 1 >= leng && c - y >= leng) {
        for (int i = 0; i < leng; i++)
            t[i] = grid[x + i][y + i];
        if (!strcmp(s.c_str(), t.c_str()))
            return 1;
    }

    /* East */
    if (c - y >= leng) {
        for (int i = 0; i < leng; i++)
            t[i] = grid[x][y + i];
        if (!strcmp(s.c_str(), t.c_str()))
            return 1;
    }

    /* SouthEast */
    if (r - x >= leng && c - y >= leng) {
        for (int i = 0; i < leng; i++)
            t[i] = grid[x + i][y + i];
        if (!strcmp(s.c_str(), t.c_str()))
            return 1;
    }

    /* South */
    if (r - x >= leng) {
        for (int i = 0; i < leng; i++)
            t[i] = grid[x + i][y];
        if (!strcmp(s.c_str(), t.c_str()))
            return 1;
    }

    /* SouthWest */
    if (r - x >= leng && y + 1 >= leng) {
        for (int i = 0; i < leng; i++)
            t[i] = grid[x + i][y - i];
        if (!strcmp(s.c_str(), t.c_str()))
            return 1;
    }

    return 0;
}
