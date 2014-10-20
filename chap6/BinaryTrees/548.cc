#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Node
{
public:
    Node() {}
    Node(int a):
        num(a),
        left(NULL),
        right(NULL) {}

    int num;
    Node *left;
    Node *right;
};

Node *build(vector<int> &inorder, vector<int> &postorder, 
        int instart, int inend, int poststart, int postend);
void find_min(Node *root, int &sum, int cur, int &res);
void free_space(Node *root);
int main()
{
    string line1, line2;
    while (getline(cin, line1)) {
        getline(cin, line2);
        stringstream ss1(line1);
        stringstream ss2(line2);

        vector<int> inorder;
        vector<int> postorder;

        int temp;
        int min_value = 10000000;
        int sum = 10000000;
        while (ss1 >> temp) {
            inorder.push_back(temp);
        }
        while (ss2 >> temp)
            postorder.push_back(temp);

        Node *root = build(inorder, postorder, 0, inorder.size() - 1, 0, postorder.size() - 1);
        find_min(root, sum, 0, min_value);
        free_space(root);
        
        cout << min_value << endl;
    }
}

Node *build(vector<int> &inorder, vector<int> &postorder, 
        int instart, int inend, int poststart, int postend)
{
    int root_num;
    Node *root;
    if (instart > inend || poststart > postend)
        return NULL;
    if (instart == inend) {
        root_num = inorder[instart];
        root = new Node(root_num);
        return root;
    }

    root_num = postorder[postend];
    root = new Node(root_num);

    int pos = -1;
    for (int i = instart; i <= inend; i++) {
        if (root_num == inorder[i]) {
            pos = i - instart;
            break;
        }
    }
    if (pos == -1)
        return NULL;


    root->left = build(inorder, postorder, instart, instart + pos - 1, poststart, poststart + pos - 1);
    root->right = build(inorder, postorder, instart + pos + 1, inend, poststart + pos, postend - 1);
    return root;
}

void find_min(Node *root, int &sum, int cur, int &res)
{
    cur += root->num;
    if (root->left == NULL && root->right == NULL) {
        if (cur < sum) {
            sum = cur;
            res = root->num;
        }
        if (cur == sum && root->num < res) {
            res = root->num;
        }
    }
    if (root->left != NULL)
        find_min(root->left, sum, cur, res);
    if (root->right != NULL)
        find_min(root->right, sum, cur, res);
}

void free_space(Node *root)
{
    if (root->left != NULL)
        free_space(root->left);
    if (root->right != NULL)
        free_space(root->right);

    delete root;
}
