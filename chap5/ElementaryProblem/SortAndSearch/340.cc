/* Title: 340
 * 考察点：简单的算法题，就是两个数组的值比较
 * Strong的计算方法是两个数组index相同的值相同的个数
 * Weak的计算方法是去掉strong后，错位值相同的个数，每一位只能计算一次.这里把strong的
 * 设置为0即可。然后记得要保存原始的数组值*/
#include <iostream>
#include <cstring>
using namespace std;

#define MAX 1001

bool is_end(int [], int);
int find_strong(int [], int [], int);
int find_weak(int [], int [], int);
int main()
{
    int n, num;
    num = 1;
    while (cin >> n && n != 0) {
        int secret[MAX], guess[MAX], secretcopy[MAX];
        for (int i = 0; i < n; i++) {
            cin >> secret[i];
            secretcopy[i] = secret[i];
        }

        cout << "Game " << num << ":" << endl;
        while (1) {
            for (int i = 0; i < n; i++)
                cin >> guess[i];

            if (!is_end(guess, n))
                break;
            int strong, weak;
            strong = find_strong(secret, guess, n);
            weak = find_weak(secret, guess, n);

            cout << "    (" << strong << "," << weak << ")" << endl;
            for (int i = 0; i < n; i++)
                secret[i] = secretcopy[i];
        }
        num++;
    }
}

bool is_end(int s[], int n)
{
    for (int i = 0; i < n; i++)
        if (s[i] != 0)
            return 1;
    return 0;
}

int find_strong(int s[], int g[], int n)
{
    int res = 0;
    for (int i = 0; i < n; i++)
        if (s[i] == g[i]) {
            s[i] = g[i] = 0;
            res++;
        }
    return res;
}

int find_weak(int s[], int g[], int n)
{
    int sum1[10], sum2[10];
    memset(sum1, 0, 10 * sizeof(int));
    memset(sum2, 0, 10 * sizeof(int));

    for (int i = 0; i < n; i++) {
        sum1[s[i]]++;
        sum2[g[i]]++;
    }

    int res = 0;
    for (int i = 1; i < 10; i++) {
        res += sum1[i] > sum2[i] ? sum2[i] : sum1[i];
    }

    return res;
}
