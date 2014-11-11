/* Title: 729
 * 考察点：简单的hamming距离枚举
 * 注意按位与的返回不是1,而是具体所在位的值*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

string binary_code(int n, int length);
int hamming_distance(int n, int length);
void output(const vector<int> &res, int length);
int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int N, H;
        cin >> N >> H;

        vector<int> res;
        for (int j = 1; j < (1 << N); j++)
            if(hamming_distance(j, N) == H)
                res.push_back(j);

        output(res, N);
        if (i != n-1)
            cout << endl;
    }
}

int hamming_distance(int n, int length)
{
    int one_number = 0;
    for (int i = 0; i < length; i++) {
        if (n & (1 << i))
            one_number++;
    }

    return one_number;
}

string binary_code(int n, int length)
{
    string s = "";
    for (int i = 0; i < length; i++) {
        int flag = n & 1 << (length - i - 1);
        char c;
        if (flag)
            c = '1';
        else
            c = '0';
        s.push_back(c);
    }
    return s;
}

void output(const vector<int> &res, int length)
{
    for (vector<int>::const_iterator it = res.begin(); it != res.end(); it++) {
        cout << binary_code(*it, length) << endl;
    }
}
