/* Title: 10391
 * 考察点：判断一个字符串是否是两个单词的组合
 * 一种是把所有字符串组合情况求出，O(N*2)*O(logn)
 * 或者是判断一个字符串的子串O(N)*O(logn)*lengh(string) */
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    set<string> dict;
    string words;
    vector<string> sw;
    while (cin >> words) {
        sw.push_back(words);
        dict.insert(words);
    }

    sort(sw.begin(), sw.end());
    vector<string> res;
    for (vector<string>::iterator it = sw.begin(); it != sw.end(); it++) {
        string whole = *it;
        for (string::iterator sit = whole.begin(); sit != whole.end()-1; sit++) {
            string sub_first(whole.begin(), sit+1);
            string sub_second(sit+1, whole.end());
            if (dict.find(sub_first) != dict.end() && dict.find(sub_second) != dict.end()) {
                res.push_back(whole);
                break;
            }
        }
    }

    sort(res.begin(), res.end());
    for (int i = 0; i < res.size(); i++)
        cout << res[i] << endl;
}
