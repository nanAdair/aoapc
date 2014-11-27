/* Title: 10591
 * 考察点：简单计算*/
#include <iostream>
#include <cstring>
using namespace std;

#define MAX 1000
int cal(int n);
int main()
{
    int num;
    cin >> num;
    for (int n = 1; n <= num; n++) {
        int number, dup;
        cin >> number;
        dup = number;
        bool flag[MAX];
        memset(flag, 0, sizeof(flag));
        if (number < MAX)
            flag[number] = 1;
        bool happy = 0;
        do {
            number = cal(number);
            if (number == 1) {
                happy = 1;
                break;
            }
            if (flag[number])
                break;
            flag[number] = 1;
        } while(1);

        cout << "Case #" << n << ": " << dup << " is ";
        if (happy)
            cout << "a Happy ";
        else
            cout << "an Unhappy ";
        cout << "number." << endl;
    }
}

int cal(int n)
{
    int res = 0;
    while (n) {
        int l = n % 10;
        res += l*l;
        n /= 10;
    }
    return res;
}
