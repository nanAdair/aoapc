/* Title: 110
 * 考察点：本题的关键在于看出这个序列排序的方法
 * 每一层的if语句其实是一个字符和前面已有字符进行比较的
 * 而不是要所有字符两两比较，就比较简单了，只需要把新的字符插入到
 * 已有字符串的各个位置就可以了*/
#include <iostream>
#include <string>
using namespace std;

string number("abcdefgh");

void meta_sort(string &res, int depth, int n);
int main()
{
    int num;
    cin >> num;
    for (int n = 0; n < num; n++) {
        int variables;
        cin >> variables;

        if (n != 0)
            cout << endl;
        cout << "program sort(input,output);" << endl;
        cout << "var" << endl;
        for (int i = 0; i < variables; i++) {
            if (i != 0)
                cout << ",";
            cout << number[i];
        }
        cout << " : integer;" << endl;
        cout << "begin" << endl;
        cout << "  readln(";
        for (int i = 0; i < variables; i++) {
            if (i == 0)
                cout << number[i];
            else
                cout << "," << number[i];
        }
        cout << ");" << endl;

        string res;
        res += "a";
        meta_sort(res, 1, variables);

        cout << "end." << endl;
    }
}

void meta_sort(string &res, int depth, int n)
{
    if (depth == n) {
        for (int j = 0; j < depth; j++)
            cout << "  ";
        cout << "writeln(";
        for (int j = 0; j < res.size(); j++) {
            if (j != 0)
                cout << ",";
            cout << res[j];
        }
        cout << ")" << endl;
        return;
    }
    string now = number.substr(depth, 1);
    for (int i = res.size(); i >= 0; i--) {
        for (int j = 0; j < depth; j++)
            cout << "  ";
        if (i == res.size()) {
            cout << "if " << res[i-1] << " < " << now << " then" << endl;
        }
        else if (i != 0) {
            cout << "else if " << res[i-1] << " < " << now << " then" << endl;
        }
        else {
            cout << "else" << endl;
        }
        res.insert(i, now);
        meta_sort(res, depth+1, n);
        res.erase(i, 1);
    }
}
