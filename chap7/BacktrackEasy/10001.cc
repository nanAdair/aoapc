/* Title: 10001
 * 考察点：题意不清楚，读了几遍还是看题解，翻了好几个帖子才知道题意
 * 第一个数字代表转换规则，第二个数不重要，第三个数是转换的目标
 * 题意是第三个数能不能通过这个转换规则由一个合法数转换一次得到
 * 第三个数的每一位的0,1都是通过转换规则，参考原数的相应位置转换得到的
 * 比如第三个数第0位是1,转换规则是3, 那么这个0位的一可能通过第一条或者第二条转换得到
 *
 * 一个小技巧是，对于一个循环数组可以补充左右两个数字来完成循环表示*/
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int change[8][3] = {{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1}, 
                    {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};
int identifier[8];
int target[35];
int res[35];
int N;
bool flag;

void dfs(int cur);
int main()
{
    string temp;
    int id;
    while (cin >> id >> N >> temp) {
        int i = 0;
        memset(identifier, 0, sizeof(identifier));
        // 注意用while时，不够位前面要补0的
        while (id) {
            identifier[i++] = id % 2;
            id /= 2;
        }
        //for (i = 0; i < 8; i++) {
            //identifier[i] = id % 2;
            //id /= 2;
        //}
        for (i = 0; i < temp.size(); i++) 
            target[i+1] = temp[i] - '0';

        flag = 0;
        for (i = 0; i < 8; i++) {
            if (identifier[i] == target[1]) {
                res[0] = change[i][0];
                res[1] = change[i][1];
                res[2] = change[i][2];
                res[N] = res[0];
                res[N+1] = res[1];
                dfs(2);
            }
        }

        if (flag)
            cout << "REACHABLE" << endl;
        else
            cout << "GARDEN OF EDEN" << endl;
    }
}

void dfs(int cur)
{
    if (cur == N-1 || cur == N) {
        for (int i = 0; i < 8; i++) {
            if (identifier[i] == target[cur] && 
                    res[cur-1] == change[i][0] &&
                    res[cur] == change[i][1] && 
                    res[cur+1] == change[i][2]) {
                if (cur == N-1)
                    dfs(cur+1);
                else
                    flag = 1;
            }
        }
        return;
    }
    for (int i = 0; i < 8; i++) {
        // identifier[i]确认规则
        // change[i][1]必须和res[cur]一致
        // change[i][0]必须和res[cur-1]一致
        // 然后可以填上res[cur+1] = change[i][2];
        if (identifier[i] == target[cur] && res[cur] == change[i][1] && res[cur-1] == change[i][0]) {
            res[cur+1] = change[i][2];
            dfs(cur+1);
        }
    }
}
