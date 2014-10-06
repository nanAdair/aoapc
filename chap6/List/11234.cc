/* Title: 11234
 * 考察点：求后缀表示式的计算方式改用队列实现的等价表示式
 * 根据后缀表达式建立二叉树，然后层次遍历后逆序输出即可*/
#include <iostream>
#include <stack>
#include <vector>
#include <sstream>
#include <queue>
using namespace std;

class Node 
{
public:
    Node () {}
    Node (char a):
        c(a),
        left(NULL),
        right(NULL) {}

    char c;
    Node *left;
    Node *right;
};

string bfs(Node *root);
int main()
{
    int n;
    cin >> n;
    string expression;
    getline(cin, expression);
    for (int i = 0; i < n; i++) {
        getline(cin, expression);

        stringstream ss(expression);
        stack<Node *> tree;
        char c;
        while (ss >> c) {
            Node *newnode = new Node(c);

            if (c >= 'a' && c <= 'z') {
                tree.push(newnode);
                continue;
            }

            Node *right = tree.top();
            tree.pop();
            Node *left = tree.top();
            tree.pop();
            newnode->left = left;
            newnode->right = right;

            tree.push(newnode);
        }

        string res;
        res = bfs(tree.top());

        for (int i = res.size() - 1; i >= 0; i--)
            cout << res[i];
        cout << endl;
    }
}

string bfs(Node *root)
{
    queue<Node *> order;
    string res;

    order.push(root);

    while (!order.empty()) {
        Node *temp = order.front();
        order.pop();
        res.push_back(temp->c);
        if (temp->left != NULL)
            order.push(temp->left);
        if (temp->right != NULL)
            order.push(temp->right);

        delete temp;
    }

    return res;
}
