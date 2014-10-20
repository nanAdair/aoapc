/* Title: 712
 * 考察点：简单的处理*/
#include <iostream>
#include <string>
using namespace std;

int find_pos(string test);
string process(string test, int index[], int depth);
int main()
{
    int depth;
    int count = 1;

    while (cin >> depth && depth != 0) {
        string temp;
        int index[8];
        for (int i = 0; i < depth; i++) {
            cin >> temp;
            index[i] = temp[1] - '0';
        }

        string result;
        cin >> result;

        cout << "S-Tree #" << count << ":" << endl;
        int number;
        cin >> number;
        for (int i = 0; i < number; i++) {
            string test;
            cin >> test;
            test = process(test, index, depth);
            int pos = find_pos(test);

            cout << result[pos];
        }
        cout << endl << endl;
        count++;
    }
}

string process(string test, int index[], int depth)
{
    string res = "";

    for (int i = 0; i < depth; i++) {
        char c = test[index[i] - 1];
        res.push_back(c);
    }

    return res;
}

int find_pos(string test)
{
    int length = test.length();
    int res = 0;

    int mul = 1;
    for (int i = 0; i < length; i++) {
        res += (test[length - i - 1] - '0') * mul;
        mul *= 2;
    }

    return res;
}
