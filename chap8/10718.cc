/* Title: 10718
 * 考察点：贪心加位运算
 * 如果n是某一位是1, 那么m就可以不为1, 判断它如果是1的话，和是否小于等于下界，
 * 因为如果小于等于的话，后面所有加起来也没有这一位加的多，说明后面的所有数都在下界下
 * ，所以这一位必须是1。
 * 如果n的某一位是0,那么m最好是1，此时判断如果是1的话会不会超过上界，不会就可以加上*/
#include <iostream>
using namespace std;

#define N 32

int main()
{
    long long n, l, u;
    while (cin >> n >> l >> u) {
        long long res, m;
        m = 0;
        for (int i = 31; i >= 0; i--) {
            if (n & (1ll << i)) {
                if ((m | (1ll << i)) <= l) {
                    m |= (1ll << i);
                }
            }
            else {
                if ((m | (1ll << i)) <= u) {
                    m |= (1ll << i);
                }
            }
        }
        cout << m << endl;
    }
}
