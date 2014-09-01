/* Title: 10361
 * 考察点：
 * 字符串处理，顺序扫一遍即可，遇到分隔符就跳下一个
 * 注意cin和getline混用时，cin不会处理前面输入流中的回车符*/
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

#define MAX 101
int main()
{
    int n;
    cin >> n;
    string temp;
    getline(cin, temp);

    for (int i = 0; i < n; i++) {
        string l1, l2;
        getline(cin, l1);
        getline(cin, l2);

        char s[5][MAX];

        int j, index;
        j = index = 0;
        for (int k = 0; k < l1.length(); k++) {
            if (l1[k] != '<' && l1[k] != '>')
                s[j][index++] = l1[k];
            else {
                s[j++][index] = '\0';
                index = 0;
            }
        }
        s[j][index] = '\0';
        
        for (int k = 0; k < 5; k++)
            cout << s[k];
        cout << endl;

        index = 0;
        while (l2[index++] != '.')
            cout << l2[index - 1];
        cout << s[3] << s[2] << s[1] << s[4] << endl;
    }
}
