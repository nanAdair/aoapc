/* Title: 540
 * 考察点：简单的list操作，只是为了加快操作，必须用一个数组记录
 * list中的位置信息，所以需要自己实现list来保存元素指针
 * 事实是其实用iterator数组也是可以的。初始化的时候是list.end(), 而不是0或NULL*/
#include <iostream>
#include <cstring>
using namespace std;

class LNode
{
public:
    LNode() {}
    LNode(int a):
        num(a),
        prev(NULL),
        next(NULL) {}

    int num;
    LNode *prev;
    LNode *next;
};

class List
{
public:
    List():
        head(NULL),
        tail(NULL) {}

    LNode *push_back(int);
    void erase(LNode *);
    LNode *insert(LNode *, int);
    int front();

    LNode *head;
    LNode *tail;
};

LNode *List::push_back(int a)
{
    LNode *node = new LNode(a);
    if (head == NULL) {
        head = node;
        tail = node;
    }
    else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }

    return node;
}

LNode *List::insert(LNode *pos, int a)
{
    LNode *node = new LNode(a);

    pos->prev->next = node;
    node->prev = pos->prev;
    node->next = pos;
    pos->prev = node;

    return node;
}

void List::erase(LNode *pos)
{
    LNode *left, *right;
    left = pos->prev;
    right = pos->next;

    if (left != NULL)
        left->next = right;
    if (right != NULL)
        right->prev = left;
    if (pos == head)
        head = right;
    if (pos == tail)
        tail = left;

    delete pos;
}

int List::front()
{
    return head->num;
}

void output(List &ll);
void ins(List &qq, int team_number, int team[], LNode *position[]);
void del(List &qq, int team_number, int team[], LNode *position[]);
int main()
{
    int gnum;
    int count = 1;
    while (cin >> gnum && gnum != 0) {
        int team[1000000];
        LNode *position[1001];
        memset(team, 0, 1000000 * sizeof(int));
        for (int i = 0; i < 1001; i++)
            position[i] = NULL;

        for (int i = 0; i < gnum; i++) {
            int mnum;
            cin >> mnum;
            for (int j = 0; j < mnum; j++) {
                int number;
                cin >> number;
                team[number] = i + 1;
            }
        }

        List qq;
        int team_number;
        string command;
        cout << "Scenario #" << count << endl;
        while (cin >> command) {
            if (command == "ENQUEUE") {
                cin >> team_number;
                ins(qq, team_number, team, position);
            }
            else if (command == "DEQUEUE") {
                int res = qq.front();
                cout << res << endl;

                del(qq, res, team, position);
            }
            else
                break;
        }

        cout << endl;
        count++;
    }
}

void ins(List &qq, int team_number, int team[], LNode *position[])
{
    LNode *posnow = position[team[team_number]];

    if (posnow == NULL || posnow == qq.tail) {
        posnow = qq.push_back(team_number);
    }
    else {
        posnow = qq.insert(posnow->next, team_number);
    }
    position[team[team_number]] = posnow;
}

void del(List &qq, int team_number, int team[], LNode *position[])
{
    LNode *posnow = position[team[team_number]];

    if (posnow == qq.head)
        position[team[team_number]] = NULL;
    qq.erase(qq.head);
}

void output(List &ll)
{
    LNode *temp = ll.head;
    while (temp != NULL) {
        cout << temp->num << endl;
        temp = temp->next;
    }
}
