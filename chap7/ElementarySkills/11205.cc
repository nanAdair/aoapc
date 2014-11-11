/* Title:11205
 * 考察点：固定位数二进制排列。用位操作会更节省空间，但是顺序操作而不是按位赋值0去深
 * 搜，有些不方便
 * 注意这里深搜的话实际是使时间增加了，因为剪枝方法太弱，有很多状态重复出现*/
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int base[16];
int number[101][16];
int min_res;
int flag[50000];

bool test_case(int led, int num, int zero_number);
void con(int led, int num, int pos, int zero_number);
void print_base(int led);
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int p, q;
        cin >> p >> q;
        for (int j = 0; j < p; j++)
            base[j] = 1;

        for (int j = 0; j < q; j++) {
            for (int k = 0; k < p; k++)
                cin >> number[j][k];
        }

        min_res = 15;
        con(p, q, 0, 0);
        cout << min_res << endl;
    }
}

void con(int led, int num, int pos, int zero_number)
{
    int max_number = pow(2, led-zero_number-1) - 1;
    if (max_number < num)
        return;

    for (int i = pos; i < led; i++) {
        // 注意这里要加一句判断，否则可能是前面已经设置0了，会导致zero_number出错
        if (base[i] == 0)
            continue;
        base[i] = 0;
        //print_base(led);
        //cout << "zero number is " << zero_number+1 << endl;
        if (test_case(led, num, zero_number+1))
            con(led, num, pos+1, zero_number+1);
        base[i] = 1;
    }
}

void print_base(int led)
{
    for (int i = 0; i < led; i++)
        cout << base[i] << " ";
    cout << endl;
}

bool test_case(int led, int num, int zero_number)
{
    memset(flag, 0, sizeof(flag));
    for (int i = 0; i < num; i++) {
        int index = 0;
        for (int j = 0; j < led; j++) {
            index = index * 2 + base[j] * number[i][j];
        }
        if (flag[index])
            return 0;
        flag[index] = 1;
    }

    int res = led - zero_number;
    min_res = min_res < res ? min_res : res;
    return 1;
}
