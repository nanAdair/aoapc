/* Title: 839
 * 考察点：看到这样的题就先建树了，掌握先序排列的建树方法
 * 其实可以直接一个dfs解决的。*/
#include <iostream>
#include <stack>
using namespace std;

class Node
{
public:
    Node() {}
    Node(int a, int b, int c, int d):
        lweight(a),
        lsize(b),
        rweight(c),
        rsize(d),
        left(NULL),
        right(NULL) {}

    int lweight;
    int rweight;
    int lsize;
    int rsize;
    Node *left;
    Node *right;
};

int update_weight(Node *root, bool &flag);
void output(bool flag);
int main()
{
    int num;
    cin >> num;

    for (int i = 0; i < num; i++) {
        int lw, ls, rw, rs;
        cin >> lw >> ls >> rw >> rs;

        Node *root = new Node(lw, ls, rw, rs);
        bool flag = 1;
        stack<Node *> tree;
        if (lw != 0 && rw != 0) {
            update_weight(root, flag);
            output(flag);
            if (i != num - 1)
                cout << endl;
            continue;
        }

        tree.push(root);
        while (!tree.empty()) {
            cin >> lw >> ls >> rw >> rs;
            Node *new_node = new Node(lw, ls, rw, rs);
            Node *parent = tree.top();

            if (parent->lweight == 0 && parent->left == NULL) {
                parent->left = new_node;
                if (parent->rweight != 0)
                    tree.pop();
            }
            else if (parent->rweight == 0 && parent->right == NULL) {
                parent->right = new_node;
                tree.pop();
            }
            if (new_node->lweight == 0 || new_node->rweight == 0)
                tree.push(new_node);
        }

        update_weight(root, flag);
        output(flag);
        if (i != num - 1)
            cout << endl;
    }
}

int update_weight(Node *root, bool &flag)
{
    if (root->lweight == 0)
        root->lweight = update_weight(root->left, flag);
    if (root->rweight == 0)
        root->rweight = update_weight(root->right, flag);

    if (root->lweight * root->lsize != root->rweight * root->rsize)
        flag = 0;
    return root->lweight + root->rweight;
}

void output(bool flag)
{
    if (flag)
        cout << "YES" << endl;
    else
    cout << "NO" << endl;
}
