/* Title: 165
 * 算法：主要是确定要选取的值的上界
 * 首先1是一定要有的
 * stamp[x-1]+1 <= stamp[x] <= maxvalue[x-1]+1
 * 从保证连续的角度去考虑
 * 但是解法中，每次更新一个stamp[x]后都会重新计算所有的
 * occur情况，重复计算了许多。*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;

#define MAX 1000
bool occur[MAX];
int maxres, maxValue[MAX], stamp[MAX];
int h, k;

void find_res(int cur, vector<int> &res);
void renew(int cur, int num, int numberOfStamps);
int main()
{
    while (cin >> h >> k) {
        if (!h && !k)
            break;

        stamp[0] = 1;
        maxValue[0] = h;

        vector<int> res;
        maxres = -1;
        find_res(1, res);

        for (int i = 0; i < res.size(); i++)
            printf("%3d", res[i]);
        printf(" ->%3d\n", maxres);
    }
}

void find_res(int cur, vector<int> &res)
{
    if (cur == k) {
        if (maxValue[cur-1] > maxres) {
            maxres = maxValue[cur-1];
            vector<int> temp(stamp, stamp+k);
            res = temp;
        }
        return;
    }
    
    for (int i = stamp[cur-1]+1; i <= maxValue[cur-1]+1; i++) {
        stamp[cur] = i;

        memset(occur, 0, sizeof(occur));
        renew(0, 0, cur+1);
        int j = 1;
        while (occur[j])
            j++;
        maxValue[cur] = j-1;
        find_res(cur+1, res);
    }
}

void renew(int cur, int num, int numberOfStamps)
{
    if (num == h)
        return;
    for (int i = 0; i < numberOfStamps; i++) {
        cur += stamp[i];
        occur[cur] = 1;
        renew(cur, num+1, numberOfStamps);
        cur -= stamp[i];
    }
}
