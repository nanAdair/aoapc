/* Title: 10706
 * 考察点：顺序递增的数字组成的字符串中找到某一位的数字
 * 首先打表将1..k组成的子串长度以及前k个子串合起来的总长度求出来
 * 然后，根据要找的位置，首先确定这个位置在哪个子串中即leng[l] <= pos < leng[l+1]
 * 找到这个l后，说明pos在1..l（刚好等于l最后一个字符）或者1..l+1的子串中
 * 然后根据subsequence[l] <= pos2 < subsequence[l+1]找到这个位置是属于那个数字的
 * 然后找该数字的第n位即可*/

#include <iostream>
#include <vector>
using namespace std;

const unsigned int limit = 2147483647;

vector<unsigned int> subsequence;
vector<unsigned int> leng;

int num_length(unsigned int num)
{
    int i = 0;
    while (num) {
        num /= 10;
        i++;
    }
    return i;
}

void make_table()
{
    subsequence.push_back(0);
    leng.push_back(0);

    unsigned int i = 0;
    while(leng[i] < limit) {
        i++;
        int last_length, to_add;
        last_length = subsequence[subsequence.size()-1];
        to_add = num_length(i);
        subsequence.push_back(last_length+to_add);

        last_length = leng[leng.size()-1];
        to_add = subsequence[subsequence.size()-1];
        leng.push_back(last_length+to_add);
    }
}

int find_sec(int pos);
int find_sec2(int pos);
int res(int number, int pos);
int main()
{
    make_table();

    int num;
    cin >> num;
    for (int n = 0; n < num; n++) {
        int pos;
        cin >> pos;

        // 找到位置是在1..k的具体某个子串中
        int sec = find_sec(pos);
        int rest = pos - leng[sec];
        if (!rest) {
            cout << sec % 10 << endl;
            continue;
        }

        // 找到位置是在某个数字k中
        int sec2 = find_sec2(rest);
        int rest2 = rest - subsequence[sec2];
        if (!rest2) {
            cout << sec2 % 10 << endl;
            continue;
        }

        // 找到这个数字的某位置的数字
        cout << res(sec2+1, rest2) << endl;
    }
}

int res(int number, int pos)
{
    int sum = num_length(number);
    int base = 1;
    for (int i = 0; i < sum - pos; i++)
        base *= 10;
    return number / base % 10;
}

int find_sec2(int pos)
{
    int l, r, m;
    l = 0; r = subsequence.size();
    while (r - l > 1) {
        m = l + (r - l) / 2;
        if (subsequence[m] > pos)
            r = m;
        else
            l = m;
    }

    return l;
}

int find_sec(int pos)
{
    int l, r, m;
    l = 0; r = leng.size();
    while (r - l > 1) {
        m = l + (r - l ) / 2;
        if (leng[m] > pos)
            r = m;
        else
            l = m;
    }

    return l;
}
