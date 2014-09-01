/* Title: 10815
 * 考察点：
 * 字符串的分割，注意题目中的陷阱，分隔符不一定是空格，其他非字母字符也是
 * qsort的使用
 * 字符串做为输入的使用istringstream: 初始化，做为输入流去输出到字符串中去
 * 可以用erase去删除一个字符串中的某个字符*/
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>
using namespace std;

string pre_handle(string &s);
bool is_in(string ss[], int num, string text);
int cmp(const void *p1, const void *p2);

int main()
{
    string words[100000];

    int index = 0;
    int num = 0;
    string line, input;
    while (!cin.eof()) {
        getline(cin, line);
        input = pre_handle(line);
        istringstream is(input);
        string temp;

        while (is >> temp) {
            if (!is_in(words, num, temp))
                words[num++] = temp;
        }
    }

    qsort(words, num, sizeof(string), cmp);

    for (int i = 0; i < num; i++) {
        cout << words[i] << endl;
    }
}

string pre_handle(string &s)
{
    string text(s.length(), ' ');

    int num = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] >= 'a' && s[i] <= 'z')
            text[num++] = s[i];
        else if (s[i] >= 'A' && s[i] <= 'Z')
            text[num++] = s[i] - 'A' + 'a';
        else if (s[i] == ' ')
            text[num++] = s[i];
        else
            text[num++] = ' ';
    }

    return text;
}

bool is_in(string ss[], int num, string text)
{
    for (int i = 0; i < num; i++) {
        if (!strcmp(ss[i].c_str(), text.c_str()))
            return 1;
    }

    return 0;
}

int cmp(const void *p1, const void *p2)
{
    return strcmp(*(char **)p1, *(char **)p2);
}
