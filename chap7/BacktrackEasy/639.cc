/* Title: 639
 * 对应每个格子为数组的下标，因为是4×4,时间最大是16的16次方
 * 不过因为每层剪枝，最后时间没有爆
 * 其实会有很多重复状态出现的，后面遇到再想好了*/
#include <iostream>
using namespace std;

bool visited[16];
bool chess[16];

bool can_place(int i, int n);
void find_max(int count, int &max_count, int n);
int main()
{
    int n;
    while (cin >> n && n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                char c;
                cin >> c;
                if (c == '.')
                    chess[n*i+j] = 1;
                else
                    chess[n*i+j] = 0;
            }
        }

        int max_count = 0;
        find_max(0, max_count, n);
        cout << max_count << endl;
    }
}

void find_max(int count, int &max_count, int n)
{
    for (int i = 0; i < n*n; i++) {
        if (!visited[i] && chess[i]) {
            if (can_place(i, n)) {
                count++;
                visited[i] = 1;
                max_count = max_count > count ? max_count : count;
                find_max(count, max_count, n);
                count--;
                visited[i] = 0;
            }
        }
    }
}
/* 这里判断复杂了，从这个结点往4个方向搜索，只要遇到X就停止
 * 只要遇到.就返回false即可
 * */
bool can_place(int i, int n)
{
    int x, y;
    x = i / n;
    y = i % n;
    for (int j = 0; j < n; j++) {
        int same_row = x * n + j;
        if (same_row == i)
            continue;
        if (visited[same_row]) {
            bool flag = 0;
            if (same_row > i) {
                for (int k = i+1; k < same_row; k++) {
                    if (!chess[k])
                        flag = 1;
                }
            }
            else {
                for (int k = same_row+1; k < i; k++) {
                    if (!chess[k])
                        flag = 1;
                }
            }
            if (!flag)
                return 0;
        }
    }

    for (int j = 0; j < n; j++) {
        int same_column = n * j + y;
        if (same_column == i)
            continue;
        if (visited[same_column]) {
            bool flag = 0;
            if (same_column > i) {
                for (int k = i+n; k < same_column; k+=n) {
                    if (!chess[k])
                        flag = 1;
                }
            }
            else {
                for (int k = same_column+n; k < i; k+=n) {
                    if (!chess[k])
                        flag = 1;
                }
            }
            if (!flag)
                return 0;
        }
    }
    return 1;
}
