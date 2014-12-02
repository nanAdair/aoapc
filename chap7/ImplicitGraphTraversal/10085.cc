/* Title: 10085
 * 考察点：和书上的8数码问题一样。只是要搜索全部的状态空间。
 * 用大小为9的int数组来表示3×3的九宫格，这就是状态的表示，然后用set来存状态的出现即可*/
#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

class State
{
public:
    State() { memset(data, 0, sizeof(data)); }
    State(const State &s);
    State &operator=(const State &s);
    string op;
    int data[9];
};

State::State(const State &s)
{
    for (int i = 0; i < 9; i++)
        data[i] = s.data[i];
    op = s.op;
}

State& State::operator=(const State &s)
{
    for (int i = 0; i < 9; i++)
        data[i] = s.data[i];
    op = s.op;
}

State res;
int dx[] = { 0, -1, 0, 1};
int dy[] = {-1,  0, 1, 0};
char dir[] = {'L', 'U', 'R', 'D'};

void bfs(State s);
void renew_res(const State &s);
void output(int n);
int main()
{
    int num;
    cin >> num; 
    for (int n = 1; n <= num; n++) {
        State init;
        for (int i = 0; i < 9; i++)
            cin >> init.data[i];
        res = init;
        bfs(init);
        output(n);
        cout << endl;
    }
}

void output(int n)
{
    cout << "Puzzle #" << n;
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0)
            cout << endl << res.data[i];
        else
            cout << " " << res.data[i];
    }
    cout << endl;
    for (int i = 0; i < res.op.length(); i++)
        cout << res.op[i];
    cout << endl;
}

bool cmp(const State &s1, const State &s2)
{
    for (int i = 0; i < 9; i++) {
        if (s1.data[i] != s2.data[i])
            return s1.data[i] < s2.data[i];
        else
            continue;
    }
    return 0;
}

void bfs(State s)
{
    bool (*fn_pt) (const State&, const State&) = cmp;
    set<State, bool (*)(const State&, const State&)> record(fn_pt);
    record.insert(s);
    queue<State> sr;
    sr.push(s);

    while (!sr.empty()) {
        State now = sr.front();
        renew_res(now);
        int z;
        for (int i = 0; i < 9; i++) 
            if (now.data[i] == 0) {
                z = i;
                break;
            }
        int newx, newy;
        for (int i = 0; i < 4; i++) {
            newx = z / 3 + dx[i];
            newy = z % 3 + dy[i];
            if (newx >= 0 && newx < 3 && newy >= 0 && newy < 3) {
                int newz = newx * 3 + newy;
                State new_state = now;
                new_state.data[z] = now.data[newz];
                new_state.data[newz] = now.data[z];
                new_state.op += dir[i];
                if (record.find(new_state) == record.end()) {
                    record.insert(new_state);
                    sr.push(new_state);
                }
            }
        }
        sr.pop();
    }
}

void renew_res(const State &s)
{
    if (s.op.length() > res.op.length())
        res = s;
}
