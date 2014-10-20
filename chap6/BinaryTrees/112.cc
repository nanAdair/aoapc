/* Title: 112
 * 考察点：根据符号的表达式建树，
 * 节点第一次出现是push入栈
 * 每一个节点一定会遇到(...)(....)这样的形式，
 * 在第一次遇到)时，标注已找到左儿子（可以是空）
 * 在第二次遇到)时，把它pop出来
 * 对建好的树，然后dfs
 * 注意在取栈的元素的时候要先确认栈是否是空的*/
#include <iostream>
#include <cstdio>
#include <stack>
using namespace std;

class Node
{
public:
    Node() {}
    Node(int a):
        num(a),
        left(NULL),
        right(NULL),
        find_left(0),
        find_right(0) {}

    int num;
    Node *left;
    Node *right;
    bool find_left;
    bool find_right;
};

void reclaim(Node *root);
void dfs(Node *root, int current, int sum, int &flag);
int main()
{
    int sum;
    while (cin >> sum) {
        stack<char> symbols;
        stack<Node *> expression;
        Node *root = NULL;

        char c;
        cin >> c;
        symbols.push(c);
        int flag = 0;

        while (!symbols.empty()) {
            cin >> c;
            if (c != ')' && c != '(') {
                ungetc(c, stdin);
                int number;
                cin >> number;

                Node *newnode = new Node(number);
                if (root == NULL) {
                    root = newnode;
                    expression.push(newnode);
                    continue;
                }

                Node *parent = expression.top();
                if (parent->find_left == 0) {
                    parent->left = newnode;
                }
                else {
                    parent->right = newnode;
                }
                expression.push(newnode);
            }
            else if (c == '(')
                symbols.push(c);
            else {
                if (root == NULL) {
                    break;
                }

                Node *parent; 
                if (!expression.empty())
                    parent = expression.top();
                if (parent->find_left == 0)
                    parent->find_left = 1;
                else {
                    expression.pop();
                }
                symbols.pop();
            }
        }
        int current = 0;
        if (root != NULL) {
            dfs(root, 0, sum, flag);
            reclaim(root);

        }
        if (flag)
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
}

void dfs(Node *root, int current, int sum, int &flag)
{
    if (flag)
        return;
    current += root->num;
    if (root->left == NULL && root->right == NULL) {
        if (current == sum)
            flag = 1;
        return;
    }
    if (root->left != NULL)
        dfs(root->left, current, sum, flag);
    if (root->right != NULL)
        dfs(root->right, current, sum, flag);
}

void reclaim(Node *root)
{
    if (root->left == NULL && root->right == NULL)
        delete root;
    else if (root->left != NULL)
        reclaim(root->left);
    else if (root->right != NULL)
        reclaim(root->right);
}
