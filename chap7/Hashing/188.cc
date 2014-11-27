/* Title: 188
 * 考察点：题目已经给出了hash算法，要求求出可以满足perfect hash的一个值
 * 根据题目给出的算法遍历即可。注意学习题目给的hash算法*/
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

#define MAX 15
int flag[MAX];
int cal(const string &s);
bool perfect(const vector<int> &v, int &l, int &r, unsigned int c);
int main()
{
    string temp;
    while (getline(cin, temp)) {
        stringstream ss(temp);
        string words;
        vector<int> text;
        while (ss >> words) {
            int num = cal(words);
            if (find(text.begin(), text.end(), num) == text.end())
                text.push_back(num);
        }
        sort(text.begin(), text.end());

        unsigned int res = 0xffffffff;
        for (int i = 0; i < text.size(); i++) {
            unsigned int c = text[i];
            while (1) {
                for (int i = 0; i < text.size(); i++)
                    flag[i] = -1;
                int p, q;
                if (perfect(text, p, q, c))
                    break;
                // 计算下一个可能的C的算法。
                unsigned int l = (c/text[p] + 1) * text[p];
                unsigned int r = (c/text[q] + 1) * text[q];
                c = l < r ? l : r;
            }
            res = res < c ? res : c;
        }

    }
}

bool perfect(const vector<int> &v, int &l, int &r, unsigned int c)
{
    int n = v.size();
    for (int i = 0; i < n; i++) {
        int res = (c / v[i]) % n;
        if (flag[res] == -1)
            flag[res] = i;
        else {
            l = flag[res];
            r = i;
            return 0;
        }
    }
    return 1;
}

int cal(const string &s)
{
    int mul = 32;
    int res = 0;
    for (int i = 0; i < s.length(); i++) {
        int temp = s[i] - 'a' + 1;
        res = res * mul + temp;
    }
    return res;
}
