/* Title: 699
 * 考察点：简单的建树，然后用一个int来表示垂直的层*/
#include <iostream>
#include <cstring>
#include <stack>
using namespace std;

class Node
{
public:
    Node() {}
    Node(int a):
        number(a),
        vlayer(0),
        find_left(0),
        left(NULL),
        right(NULL) {}

    int number;
    int vlayer;
    bool find_left;
    Node *left;
    Node *right;
};

void process_data(int *sum, int min_layer, Node *root);
void output(int *sum, int n);
int main()
{
    int root_number;
    int count = 1;
    while (cin >>root_number && root_number != -1) {
        stack<Node *> tree;

        Node *root = new Node(root_number);
        tree.push(root);

        int min_layer = root->vlayer;
        int max_layer = root->vlayer;

        while (!tree.empty()) {
            int num;
            cin >> num;

            Node *parent = tree.top();
            if (num == -1) {
                if (parent->find_left == 0)
                    parent->find_left = 1;
                else
                    tree.pop();
            }
            else {
                Node *new_node = new Node(num);
                if (parent->find_left == 0) {
                    parent->find_left = 1;
                    parent->left = new_node;
                    new_node->vlayer = parent->vlayer - 1;
                    min_layer = min_layer < new_node->vlayer ? min_layer : new_node->vlayer;
                    tree.push(new_node);
                }
                else {
                    parent->right = new_node;
                    new_node->vlayer = parent->vlayer + 1;
                    max_layer = max_layer > new_node->vlayer ? max_layer : new_node->vlayer;
                    tree.pop();
                    tree.push(new_node);
                }
            }
        }

        int sum[1000];
        memset(sum, 0, 1000 * sizeof(int));
        process_data(sum, -min_layer, root);

        cout << "Case " << count << ":" << endl;
        output(sum, max_layer - min_layer);
        count++;
    }
}

void process_data(int *sum, int min_layer, Node *root)
{
    int layer = min_layer + root->vlayer;
    sum[layer] += root->number;

    if (root->left != NULL)
        process_data(sum, min_layer, root->left);
    if (root->right != NULL)
        process_data(sum, min_layer, root->right);
}

int number_length(int num)
{
    int length = 0;
    while (num) {
        length++;
        num /= 10;
    }

    return length;
}
void output(int *sum, int n)
{
    int length = 0;
    for (int i = 0; i <= n; i++) {
        if (i != n)
            cout << sum[i] << " ";
        else
            cout << sum[i];
    }
    cout << endl;
    cout << endl;
}
