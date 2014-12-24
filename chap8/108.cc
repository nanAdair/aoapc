/* Title: 108
 * 考察点：最大子序列的变形题目
 * 把相对于原点的一个方块做为一个单位去求和，然后减去加上对应的部分得到区域和*/
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define MAX 101
int number[MAX][MAX];

struct Point
{
    Point(int a, int b):
        x(a),
        y(b) {}
    int x, y;
};

int main()
{
    int num;
    while (cin >> num) {
        for (int i = 0; i < num; i++) 
            for (int j = 0; j < num; j++)
                cin >> number[i][j];
        int sum[MAX][MAX];
        memset(sum, 0, sizeof(sum));
        for (int i = 1; i <= num; i++) {
            for (int j = 1; j <= num; j++) {
                int tmp = 0;
                for (int p = 0; p < i; p++)
                    for (int q = 0; q < j; q++)
                        tmp += number[p][q];
                sum[i][j] = tmp;
            }
        }
        vector<Point> d;
        for (int i = 0; i < num; i++) {
            for (int j = 0; j < num; j++)
                d.push_back(Point(i, j));
        }

        int res = 0;
        for (int i = 0; i < d.size(); i++) {
            for (int j = 0; j < d.size(); j++) {
                int x1, x2, y1, y2;
                x1 = d[i].x < d[j].x ? d[i].x : d[j].x;
                x2 = d[i].x > d[j].x ? d[i].x : d[j].x;
                y1 = d[i].y < d[j].y ? d[i].y : d[j].y;
                y2 = d[i].y > d[j].y ? d[i].y : d[j].y;
                int subsum = sum[x2+1][y2+1] - sum[x1][y2+1] - sum[x2+1][y1] + sum[x1][y1];
                if (subsum > res)
                    res = subsum;
            }
        }
        cout << res << endl;
    }
}
