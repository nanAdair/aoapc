/* Title: 10152
 * 解题思路：
 * 1. 保存起初的序列信息，vector下标自动保存位置
 * 2. 读入目标序列，根据字符串的key，保存这个字符串的目标位置
 * 3. 在起初的序列中，对于某个位置的字符串，如果起初序列在它前面有
 *    在目标序列中应该在它后面的字符串，那么它就应该移动，设置flag
 * 4. 对于某个字符串移动后，根据题意一定是移动到top。所以所有应在它
 *    前面的字符串都会在后续移动
 *
 * 考察点：
 * 注意vector对象，在push_back之后，对象中原有元素的地址是可能发生改变的*/
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Turtle 
{
public:
    Turtle() {}
    Turtle(string &str):
        name(str),
        order(0),
        move(0) {}
    string name;
    int order;  // 保存目标位置
    int move;   // 是否会进行移动
};

void process(vector<Turtle> &origin);
bool cmp(Turtle a, Turtle b);
void output(vector<Turtle> &origin);
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++ ) {
        int m;
        vector<Turtle> origin;
        /* 在这里要用Turtle*, 因为后面要改变origin对象的数据 */
        map<string, Turtle*> temp;
        cin >> m;
        string name;
        getline(cin, name);
        for (int j = 0; j < m; j++) {
            getline(cin, name);
            Turtle one(name);
            origin.push_back(one);
        }

        /* 创建一个hash，以便通过字符串迅速找到原始序列中字符串所在位置 */
        for (int j = 0; j < m; j++) {
            temp[origin[j].name] = &origin.at(j);
        }
        for (int j = 0; j < m; j++) {
            getline(cin, name);
            int order = j + 1;
            temp[name]->order = order;
        }

        process(origin);

        sort(origin.begin(), origin.end(), cmp);

        output(origin);
    }
}

void process(vector<Turtle> &origin)
{
    int max_order = 0;
    for (vector<Turtle>::iterator ita = origin.begin(); ita != origin.end(); ita++) {
        for (vector<Turtle>::iterator itb = origin.begin(); itb != ita; itb++) {
            if (itb->order > ita->order) {
                ita->move = 1;
                if (ita->order > max_order)
                    max_order = ita->order;
                break;
            }
        }
    }

    for (vector<Turtle>::iterator it = origin.begin(); it != origin.end(); it++) {
        if (it->order < max_order)
            it->move = 1;
    }
}

bool cmp(Turtle a, Turtle b)
{
    return a.order < b. order;
}

void output(vector<Turtle> &origin)
{
    for (int i = origin.size() - 1; i >= 0; i--) {
        if (origin[i].move == 1)
            cout << origin[i].name << endl;
    }
    cout << endl;
}
