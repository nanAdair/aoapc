/* Title: 442
 * 考察点：简单的栈操作，由于有严格的格式，所以在处理字符串的时候不用考虑太多特殊情况
 * 另外，起初用的是stack<char>，然后将临时矩阵用一个字符表示push进栈。后来发现无法处
 * 理类似((AB)(AB))的情况。于是改为stack<Matrix>实际存放矩阵即可*/
#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <sstream>
using namespace std;

class Matrix
{
public:
    Matrix() {}
    Matrix(int a, int b):
        raw(a),
        column(b) {}
    int raw;
    int column;
};

bool is_error(stack<Matrix> ml, bool &flag);
int main()
{
    int n;
    cin >> n;
    map<char, Matrix> hash_table;

    for (int i = 0; i < n; i++) {
        char name;
        int raw, column;
        cin >> name >> raw >> column;
        hash_table[name] = Matrix(raw, column);
    }

    string temp;
    getline(cin, temp);
    while (getline(cin, temp)) {
        stringstream ss(temp);
        char c;
        bool flag = 1;
        int sum = 0;
        stack<Matrix> mlist;

        while (ss >> c) {
            if (c == '(') 
                continue;
            if (c != ')') {
                if (hash_table.find(c) == hash_table.end()) {
                    flag = 0;
                    break;
                }
                Matrix m = hash_table[c];
                mlist.push(m);
                continue;
            }

            if (is_error(mlist, flag))
                break;
            Matrix right = mlist.top();
            mlist.pop();

            if (is_error(mlist, flag))
                break;
            Matrix left = mlist.top();
            mlist.pop();

            if (left.column != right.raw) {
                flag = 0;
                break;
            }

            sum += left.raw * left.column * right.column;
            Matrix now(left.raw, right.column);
            mlist.push(now);
        }

        if (!flag) {
            cout << "error" << endl;
            continue;
        }
        cout << sum << endl;
    }
}

bool is_error(stack<Matrix> ml, bool &flag)
{
    if (ml.empty()) {
        flag = 0;
        return 1;
    }
    return 0;
}
