/* Title: 10562
 * 考察点：第一点看题意，只有一个根
 * 第二点判断右边界的时候不能从pos开始加，因为虽然第二行可能是-，但是第三行可能已经结
 * 束了，所以注意这种情况要两行一起来判断
 * 数据会出现在一行字符串中有'\0'的情况*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void output(vector<string> &tree, int layer, int pos);
bool isCha(char c);
int main()
{
    int n;
    cin >> n;
    string temp;
    getline(cin, temp);

    for (int i = 0; i < n; i++) {
        vector<string> tree;
        while (getline(cin, temp) && temp != "#")
            tree.push_back(temp);

        cout << "(";
        if (tree.size() > 0) {
            for (int j = 0; j < tree[0].length(); j++) {
                if (isCha(tree[0][j])) {
                    output(tree, 0, j);
                    break;
                }
            }
        }
        cout << ")" << endl;
    }
}

void output(vector<string> &tree, int layer, int pos)
{
    cout << tree[layer][pos] << "(";
    if (layer + 1 >= tree.size() || tree[layer+1][pos] != '|') {
        cout << ")";
        return ;
    }

    int i, left, right;
    i = left = right = pos;
    while (left >= 0 && tree[layer+2][left] == '-')
        left--;
    if (left >= 0 && tree[layer+2][left] != '-')
        left += 1;
    if (left == -1)
        left = 0;
    right = left;
    while (tree[layer+2][right] == '-' && tree[layer+3][right] != '\0')
        right++;

    for (int i = left; i < right; i++)
        if (isCha(tree[layer+3][i]))
            output(tree, layer+3, i);

    cout << ")";
}

bool isCha(char c)
{
    if (isprint(c) && c != ' ' && c != '|' && c != '-' && c != '#' && c != '\0')
    //if (c != ' ' && c != '\0')
        return 1;
    return 0;
}
