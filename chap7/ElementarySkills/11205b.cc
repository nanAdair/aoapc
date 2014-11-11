/* Title: 11205
 * 考察点：深搜超时了，暴力可以过*/
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

bool flag[50000];
bool number[101][16];
int min_res;

void findres(int led, int num);
void test_case(int s, int n, int num);
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int p, q;
        cin >> p >> q;
        for (int j = 0; j < q; j++) {
            for (int k = 0; k < p; k++)
                cin >> number[j][k];
        }

        min_res = 15;
        findres(p+1, q);
        cout << min_res << endl;
    }
}

void findres(int led, int num)
{
    for (int i = (1 << led) - 1; i > 0; i--) {
        test_case(i, led-1, num);
    }
}

void test_case(int s, int n, int num)
{
    vector<bool> base;
    int zero_number = 0;
    for (int i = 0; i < n; i++) {
        bool temp = s & (1 << (n - i));
        if (!temp)
            zero_number++;
        base.push_back(temp);
    }

    memset(flag, 0, sizeof(flag));
    for (int i = 0; i < num; i++) {
        int index = 0;
        for (int j = 0; j < base.size(); j++)
            index = index * 2 + base[j] * number[i][j];
        if (flag[index])
            return;
        flag[index] = 1;
    }

    int res = n - zero_number;
    min_res = min_res < res ? min_res : res;
}
