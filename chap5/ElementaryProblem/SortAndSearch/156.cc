/* Title: 156
 * 考察点：vector的使用
 * qsort对vector string，类似与string数组，只是第一参数用vector[0]的地址
 * qsort对string，用强制类型转换*/
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <algorithm>
using namespace std;

bool is_in(vector<string> &target, string words, vector<string> &erased);
bool ensemble(string s, string t);
string process(string s);
int cmp(const void *p1, const void *p2);
int cmp2(const void *p1, const void *p2);
bool cmp3(string p1, string p2);

int main()
{
    vector<string> res;
    vector<string> erased;
    string temp;

    while (getline(cin, temp) && strcmp(temp.c_str(), "#") != 0) {
        stringstream ss(temp);
        string words;
        
        while (ss >> words) {
            if (res.empty())
                res.push_back(words);
            else {
                if (!is_in(res, words, erased))
                    res.push_back(words);
            }
        }
    }

    //qsort(&res[0], res.size(), sizeof(string), cmp);
    //sort(res.begin(), res.end());
    sort(res.begin(), res.end(), cmp3);

    for (vector<string>::iterator it = res.begin(); it != res.end(); it++)
        cout << *it << endl;
}

bool is_in(vector<string> &target, string words, vector<string> &erased)
{
    for (vector<string>::iterator it = target.begin(); it != target.end(); it++) {
        if (ensemble(*it, words)) {
            erased.push_back(*it);
            target.erase(it);
            return 1;
        }
    }

    for (vector<string>::iterator it = erased.begin(); it != erased.end(); it++) {
        if (ensemble(*it, words))
            return 1;
    }
    return 0;
}

bool ensemble(string s, string t)
{
    string s1 = process(s);
    string t1 = process(t);

    return !strcmp(s1.c_str(), t1.c_str());
}

string process(string s)
{
    string s1;
    for (string::iterator it = s.begin(); it != s.end(); it++) {
        if (*it >= 'A' && *it <= 'Z')
            s1.push_back(*it - 'A' + 'a');
        else
            s1.push_back(*it);
    }
    qsort((void *)s1.c_str(), s1.size(), sizeof(char), cmp2);

    return s1;
}

int cmp(const void *p1, const void *p2)
{
    return strcmp(*(char **)p1, *(char **)p2);
}

int cmp2(const void *p1, const void *p2)
{
    return *(char *)p1 - *(char *)p2;
}

bool cmp3(string p1, string p2)
{
    return p1 < p2;
}
