/* Title: 123
 * 考察点：map检索，vector去保存排序结果*/
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

class Titles
{
public:
    string title;
    string index;
    int pos;
    int order;
};

void preprocess(string &s);
void constructTitle(vector<Titles> &t, const string &s, const map<string, int> &m, int order);
string processTitle(const string &s, int pos, int n);
string processIndex(string &s);
bool cmp(const Titles &s1, const Titles &s2);
int main()
{
    map<string, int> ignore;
    string words;
    while (getline(cin, words) && words != "::") {
        ignore[words] = 1;
    }

    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        preprocess(line);
        lines.push_back(line);
    }

    vector<Titles> content;
    for (vector<string>::iterator it = lines.begin(); it != lines.end(); it++)
        constructTitle(content, *it, ignore, it - lines.begin());

    sort(content.begin(), content.end(), cmp);
    for (vector<Titles>::iterator it = content.begin(); it != content.end(); it++)
        cout << it->title << endl;
}

void preprocess(string &s)
{
    for (string::iterator it = s.begin(); it != s.end(); it++)
        if (*it >= 'A' && *it <= 'Z')
            *it = *it - 'A' + 'a';
}

void constructTitle(vector<Titles> &t, const string &s, const map<string, int> &m, int order)
{
    int pos = 0;
    stringstream ss(s);
    string word;

    while (ss >> word) {
        if (m.find(word) != m.end()) {
            pos += word.length() + 1;
            continue;
        }

        Titles temp;
        temp.title = processTitle(s, pos, word.length());
        temp.index = processIndex(word);
        temp.pos = pos;
        temp.order = order;
        t.push_back(temp);

        pos += word.length() + 1;
    }
}

string processTitle(const string &s, int pos, int n)
{
    string res;
    for (int i = 0; i < s.length(); i++) {
        if (i >= pos && i < pos + n)
            res.push_back(s[i] - 'a' + 'A');
        else
            res.push_back(s[i]);
    }
    return res;
}

string processIndex(string &s)
{
    string res;
    for (string::iterator it = s.begin(); it != s.end(); it++)
        res.push_back(*it - 'a' + 'A');
    return res;
}

bool cmp(const Titles &s1, const Titles &s2)
{
    if (s1.index != s2.index)
        return s1.index < s2.index;
    if (s1.order != s2.order)
        return s1.order < s2.order;
    if (s1.pos != s2.pos)
        return s1.pos < s2.pos;
    return 1;
}
