/* Title: 10720
 * 考察点：havel hakimi定理
 * 把序列的所有点从大到小排列，然后把队列头的点和后面的构成边
 * 更新所有点的度数，然后重新排序
 * 最后所有点的度数为0是代表这个序列可以构成图*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int main()
{
    int num;
    while (cin >> num && num) {
        vector<int> number;
        for (int n = 0; n < num; n++) {
            int temp;
            cin >> temp;
            number.push_back(temp);
        }
        sort(number.begin(), number.end(), greater<int>());

        bool flag = 1;
        while (number[0]) {
            int i = 0;
            for (int j = i+1; number[i] && j < num; j++) {
                if (number[j]) {
                    number[j] -= 1;
                    number[i] -= 1;
                }
            }
            if (number[i]) {
                flag = 0;
                break;
            }
            sort(number.begin(), number.end(), greater<int>());
        }
        if (flag)
            cout << "Possible" << endl;
        else
            cout << "Not possible" << endl;
    }
}
