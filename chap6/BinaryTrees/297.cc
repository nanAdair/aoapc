/* Title: 297
 * 考察点：二叉树拓展成四叉树。性质不变，根据先序序列可以直接建树
 * 另外注意二维数组做为函数参数传参，明确写上第二维的大小*/
#include <iostream>
#include <stack>
#include <cstring>
#include <sstream>
using namespace std;

class Node
{
public:
    Node() {}
    Node(char a):
        color(a),
        sons(0),
        one(NULL),
        two(NULL),
        three(NULL),
        four(NULL) {}

    char color;
    int sons;
    Node *one;
    Node *two;
    Node *three;
    Node *four;
};

Node *construct_tree(string &s);
void deconstruct_tree(Node *root);
void pad(Node *root, int tree[][32], int lcolumn, int rcolumn, int uraw, int draw);
int calculate(int tree1[][32], int tree2[][32]);
void print_tree(Node *root);

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string str1, str2;
        cin >> str1 >> str2;

        int tree1[32][32];
        int tree2[32][32];

        memset(tree1, 0, 32 * 32 * sizeof(int));
        memset(tree2, 0, 32 * 32 * sizeof(int));

        Node *root1, *root2;

        root1 = construct_tree(str1);
        root2 = construct_tree(str2);

        pad(root1, tree1, 0, 32, 0, 32);
        pad(root2, tree2, 0, 32, 0, 32);

        int res = calculate(tree1, tree2);
        cout << "There are " << res << " black pixels." << endl;
        deconstruct_tree(root1);
        deconstruct_tree(root2);
    }
}

void print_tree(Node *root)
{
    cout << root->color;
    if (root->color == 'p') {
        print_tree(root->one);
        print_tree(root->two);
        print_tree(root->three);
        print_tree(root->four);
    }
}

Node *construct_tree(string &s)
{
    stringstream cc(s);
    char c;
    cc >> c;
    Node *root = new Node(c);

    stack<Node *> tree;
    tree.push(root);

    while (!tree.empty()) {
        cc >> c;
        Node *new_node = new Node(c);
        Node *parent = tree.top();

        if (parent->sons == 0) {
            parent->one = new_node;
        }
        else if (parent->sons == 1) {
            parent->two = new_node;
        }
        else if (parent->sons == 2) {
            parent->three = new_node;
        }
        else 
            parent->four = new_node;

        parent->sons++;
        if (parent->sons == 4)
            tree.pop();
        if (new_node->color == 'p')
            tree.push(new_node);
    }

    return root;
}

void deconstruct_tree(Node *root)
{
    if (root->one != NULL)
        deconstruct_tree(root->one);
    if (root->two != NULL)
        deconstruct_tree(root->two);
    if (root->three != NULL)
        deconstruct_tree(root->three);
    if (root->four != NULL)
        deconstruct_tree(root->four);
    delete root;
}

void pad(Node *root, int tree[][32], int lcolumn, int rcolumn, int uraw, int draw)
{
    int color = 0;
    if (root->color == 'f')
        color = 1;

    if (root->color != 'p') {
        for (int i = lcolumn; i < rcolumn; i++) 
            for (int j = uraw; j < draw; j++)
                tree[j][i] = color;
        return ;
    }
    

    int column_add = (rcolumn - lcolumn) / 2;
    int raw_add = (draw - uraw) / 2;
    pad(root->one, tree, lcolumn + column_add, rcolumn, uraw, uraw + raw_add);
    pad(root->two, tree, lcolumn, lcolumn + column_add, uraw, uraw + raw_add);
    pad(root->three, tree, lcolumn, lcolumn + column_add, uraw + raw_add, draw);
    pad(root->four, tree, lcolumn + column_add, rcolumn, uraw + raw_add, draw);
}

int calculate(int tree1[][32], int tree2[][32])
{
    int res = 0;
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            if (tree1[i][j] || tree2[i][j])
                res++;
        }
    }

    return res;
}
