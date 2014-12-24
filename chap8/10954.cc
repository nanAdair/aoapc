/* Title: 10954
 * 考察点：贪心，用一个priority_queue, 将每次得到的结果放入队列中
 * 每次将队列头两个数相加即可，然后pop掉，直到队列为空。*/
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

int main()
{
    int n;
    while (cin >> n) {
        if (!n)
            break;
        priority_queue<int, vector<int>, greater<int> > numbers;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            numbers.push(a);
        }
        int res = 0;
        while (1) {
            int a, b;
            a = numbers.top();
            numbers.pop();
            b = numbers.top();
            numbers.pop();
            res += (a + b);
            if (numbers.empty())
                break;
            numbers.push(a + b);
        }

        cout << res << endl;
    }
}
