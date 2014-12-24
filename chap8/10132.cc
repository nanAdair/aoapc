/* Title: 10132
 * 考察点：用最短的和最长的构成串，然后去验证每一个字符串是否能找到另一半*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

void init(map<string, int> &m, const vector<string> &snippets);
bool comp(const string &s1, const string &s2);
bool is_res(map<string, int> &m, const string res, int number);
int main()
{
    int num;
    cin >> num;
    string temp;
    getline(cin, temp);
    getline(cin, temp);
    for (int n = 0; n < num; n++) {
        vector<string> snippets;
        while (getline(cin, temp)) {
            if (temp[0] != '0' && temp[0] != '1')
                break;
            snippets.push_back(temp);
        }

        sort(snippets.begin(), snippets.end(), comp);
        int min_length, max_length;
        min_length = snippets[0].length();
        max_length = snippets[snippets.size()-1].length();

        vector<string> l, r;
        for (int i = 0; i < snippets.size(); i++) {
            if (snippets[i].length() == min_length)
                l.push_back(snippets[i]);
            if (snippets[i].length() == max_length)
                r.push_back(snippets[i]);
        }

        bool flag = 0;
        map<string, int> visit;
        string res;
        for (int i = 0; i < l.size(); i++) {
            if (flag)
                break;
            for (int j = 0; j < r.size(); j++) {
                res = l[i] + r[j];
                init(visit, snippets);
                if (is_res(visit, res, snippets.size())) {
                    flag = 1;
                    break;
                }
                res = r[j] + l[i];
                init(visit, snippets);
                if (is_res(visit, res, snippets.size())) {
                    flag = 1;
                    break;
                }
            }
        }
        cout << res << endl;
        if (n != num-1)
            cout << endl;
    }
}

bool is_res(map<string, int> &m, const string res, int number)
{
    int n = 0;
    for (map<string, int>::iterator it = m.begin(); it != m.end(); it++) {
        if (it->second == 0)
            continue;
        bool flag = 0;
        string sub1 = it->first;
        string left(res.begin(), res.begin()+sub1.size());
        string right(res.begin()+sub1.size(), res.end());
        if (sub1 == left) {
            if (m.find(right) != m.end() && m[right] != 0) {
                if (left == right && m[left] < 2)
                    flag = 0;
                else
                    flag = 1;
            }
        }
        if (flag) {
            n++;
            m[left] -= 1;
            m[right] -= 1;
        }
        if (flag && m[left] > 0)
            it--;
    }
    if (2 * n == number)
        return 1;
    else 
        return 0;
}

bool comp(const string &s1, const string &s2)
{
    return s1.length() < s2.length();
}

void init(map<string, int> &m, const vector<string> &snippets) 
{
    m.clear();
    for (int i = 0; i < snippets.size(); i++) {
        if (m.find(snippets[i]) == m.end())
            m[snippets[i]] = 1;
        else
            m[snippets[i]] += 1;
    }
}
