/* Title: 10167
 * 考察点：枚举二维坐标点在一条线的左边还是右边
 * 用ax+by>0 or <0来分类*/
#include <iostream>
using namespace std;

#define MAX 101
int main()
{
    int n;
    while (cin >> n && n) {
        int x[MAX], y[MAX];
        for (int i = 0; i < 2*n; i++) {
            int a, b;
            cin >> a >> b;
            x[i] = a;
            y[i] = b;
        }

        int flag = 0;
        int i, j;
        for (i = -500; i <= 500; i++) {
            for (j = -500; j <= 500; j++) {
                int positive, negtive;
                int flagk = 1;
                positive = negtive = 0;
                for (int k = 0; k < 2*n; k++) {
                    int res = i * x[k] + j * y[k];
                    if (res > 0)
                        positive++;
                    else if (res < 0)
                        negtive++;
                    else {
                        flagk = 0;
                        break;
                    }
                }
                if (!flagk)
                    continue;
                if (positive == negtive) {
                    flag = 1;
                }
                if (flag)
                    break;
            }
            if (flag)
                break;
        }
        cout << i << " " << j << endl;
    }
}
