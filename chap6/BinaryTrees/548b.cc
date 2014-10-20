/* Title: 548
 * 考察点：二叉树的中序和后序遍历重建二叉树
 * Node *build(int len, int *in, int *post)
 * len -- 这个树的长度
 * in -- 中序遍历的序列
 * post -- 后序遍历的序列
 * Return 当前树的根节点
 *
 * 思路就是先找到后序的最后一个节点就是当前树的根
 * 找到这个根在中序序列中的相对位置leng，整个序列长度为n
 * 左边的序列长度leng就是左子树的长度
 * 后先的序列长度n-leng-1就是右子树的长度
 * 在中序序列中，左右子树的起始位置分别是in, in + leng + 1
 * 在后续序列中，左右子树的起始位置分别是post, post + leng
 * 在前序序列中，左右子树的起始位置分别是pre+1, pre+leng+1*/
#include <iostream>
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

int res, minSum;
void build(int n, int *in, int *post, int sum, int *preorder);
int main()
{
    string line1, line2;
    while (getline(cin, line1)) {
        getline(cin, line2);
        stringstream ss1(line1);
        stringstream ss2(line2);

        minSum = 0x7fffffff;
        res = 0x7fffffff;

        int inorder[10001], postorder[10001], preorder[10001];
        int i = 0;
        int sum = 0;
        while (ss1 >> inorder[i++]) ;
        i = 0;
        while (ss2 >> postorder[i++]) ;

        build(i - 1, inorder, postorder, sum, preorder);

        //for (int j = 0; j < i - 1; j++)
            //cout << preorder[j] << " ";
        //cout << endl;

        cout << res << endl;
    }
}

void build(int n, int *in, int *post, int sum, int *preorder)
{
    if (n <= 0)
        return ;
    int root = post[n - 1];

    if (n == 1) {
        preorder[0] = root;
        int temp = sum + root;
        if (temp < minSum) {
            minSum = temp;
            res = root;
        }
        else if (temp == minSum)
            res = res < root ? res : root;
        return ;
    }

    int pos = -1;
    for (int i = 0; i < n; i++) {
        if (in[i] == root) {
            pos = i;
            break;
        }
    }

    build(pos, in, post, sum + root, preorder + 1);
    build(n - pos - 1, in + pos + 1, post + pos, sum + root, preorder + pos + 1);
    preorder[0] = root;
}
