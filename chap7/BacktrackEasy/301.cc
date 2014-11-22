/* Title: 301
 * 考察点：简单深搜，剪枝
 * 注意一定要保证递归前和递归后的context一致
 * 组合问题可以不用visited数组来判断，直接用当前的下一个数来进行递归即可*/
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int station[8];
class Order
{
public:
    Order() {}
    Order(int a, int b, int c):
        start(a), term(b), pass(c) {};

    int start;
    int term;
    int pass;
};
vector<Order> test_case;

void find_max(int &max_res, int depth, int num, int limit, int cur_res);
int main()
{
    int n, B, num_orders;
    while (cin >> n >> B >> num_orders) {
        if (!n && !B && !num_orders)
            break;
        test_case.clear();
        for (int i = 0; i < num_orders; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            test_case.push_back(Order(a, b, c));
        }

        int max_res = 0;
        memset(station, 0, sizeof(station));
        find_max(max_res, 0, num_orders, n, 0);

        cout << max_res << endl;
    }
}

void find_max(int &max_res, int depth, int num, int limit, int cur_res)
{
    if (depth == num)
        return;
    for (int i = depth; i < num; i++) {
        Order now = test_case[i];
        int j;
        bool flag = 1;
        for (j = now.start; j < now.term; j++) {
            station[j] += now.pass;
            if (station[j] > limit)
                flag = 0;
        }
        if (flag) {
            cur_res += (now.term - now.start) * now.pass;
            max_res = max_res > cur_res ? max_res : cur_res;
            // 这里的参数是i+1
            find_max(max_res, i+1, num, limit, cur_res);
            cur_res -= (now.term - now.start) * now.pass;
        }
        for (j = now.start; j < now.term; j++)
            station[j] -= now.pass;
    }
}
