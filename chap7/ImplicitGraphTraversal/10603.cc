/* Title: 10603
 * 考察点：和书上的茶杯倒水的题目类似，只不过题中的状态要多一个此时一共到了多少升的记
 * 录。利用广搜搜索所有的状态，注意剪枝的条件是同样的水杯状态，但是total要比之前记录
 * 多。
 *
 * WA了两次，因为没有考虑初始的两个状态，一个是输入target和第二个杯子相同，此时不用倒
 * 另外一个是最终的target会降到0，这也是一个初始状态，所以要注意区别*/
#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <queue>
using namespace std;

class State
{
public:
    State() {}
    State(int i, int j, int p, int q):
        amount(q) 
    {
        cups[0] = i;
        cups[1] = j;
        cups[2] = p;
   }

    int cups[3];
    int amount;
};

int init[3];
int target;
int number[201];

void renew(const State &s);
void bfs(State &s);
void test_state(const State &s);
int main()
{
    int num;
    cin >> num;
    for (int n = 0; n < num; n++) {
        cin >> init[0] >> init[1] >> init[2] >> target;

        bool flag = 0;
        if (init[2] == target) {
            cout << 0 << " " << target << endl;
            continue;
        }
        memset(number, 0, sizeof(number));
        State beginning(0, 0, init[2], 0);
        bfs(beginning);

        while (target >= 0 && number[target] == 0)
            target--;
        if (target == init[2] || target == 0)
            cout << 0 << " " << target << endl;
        else
            cout << number[target] << " " << target << endl;
    }
}

class Cups
{
public:
    Cups() {}
    Cups(int i, int j, int k):
        a(i), b(j), c(k) {}
    int a;
    int b;
    int c;
};

bool cmp(const Cups &c1, const Cups &c2)
{
    if (c1.a != c2.a)
        return c1.a < c2.a;
    else if (c1.b != c2.b)
        return c1.b < c2.b;
    else 
        return c1.c < c2.c;
}

void bfs(State &s)
{
    bool(*fnt)(const Cups&, const Cups&) = cmp;
    // map的key值非内置类型时的初始化
    map<Cups, int, bool(*)(const Cups&, const Cups&) > visited(fnt);
    Cups first_one(s.cups[0], s.cups[1], s.cups[2]);
    visited[first_one] = 0;
    queue<State> q;
    q.push(s);

    while (!q.empty()) {
        State now = q.front();
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++) {
                if (i == j)
                    continue;
                int next_cups[3], total;
                for (int k = 0; k < 3; k++)
                    next_cups[k] = now.cups[k];
                int to_add, to_sub;
                to_add = next_cups[i];
                to_sub = 0;
                next_cups[i] -= to_add;
                next_cups[j] += to_add;
                if (next_cups[j] > init[j]) {
                    to_sub = next_cups[j] - init[j];
                }
                next_cups[i] += to_sub;
                next_cups[j] -= to_sub;
                total = now.amount + to_add - to_sub;
                State new_state(next_cups[0], next_cups[1], next_cups[2], total);
                Cups track(next_cups[0], next_cups[1], next_cups[2]);
                bool flag = 0;
                if (visited.find(track) == visited.end()) 
                    flag = 1;
                else {
                    if (visited[track] > total) {
                        flag = 1;
                    }
                }
                if (flag) {
                    visited[track] = total;
                    renew(new_state);
                    q.push(new_state);
                }
            }
        }
        q.pop();
    }
}

void renew(const State &s)
{
    for (int i = 0; i < 3; i++) {
        int index = s.cups[i];
        if (!number[index] || s.amount < number[index])
            number[index] = s.amount;
    }
}

void test_state(const State &s)
{
    for (int i = 0; i < 3; i++) {
        cout << s.cups[i] << " ";
    }
    cout << s.amount << endl;

}
