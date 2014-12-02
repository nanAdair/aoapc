/* Title: 321
 * 考察点：还是定义状态，然后bfs搜索状态空间。
 * 这道题的状态就是灯的状态以及当前所在的房间号
 * 动作状态是采取的动作，以及目标房间
 * 如果用map来记录状态的话会tle，所以要用hash来记录
 * 即使是最简单的hash函数就可以了，这道题学习了C++里面的unordered_map的
 * 使用方法*/
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <cstring>
using namespace std;

#define ROOMS 11
string handles[] = {"Switch on light in room", "Switch off light in room", "Move to room"};

class State
{
public:
    State() {}
    State(int a, bool b[]):
        room(a) {for (int i = 0; i < ROOMS; i++) light[i] = b[i];}

    State &operator=(const State&);

    int room;
    bool light[ROOMS];
};

bool operator==(const State &s1, const State &s2)
{
    if (s1.room != s2.room)
        return false;
    for (int i = 0; i < ROOMS; i++)
        if (s1.light[i] != s2.light[i])
            return false;
    return true;
}

ostream &operator<<(ostream &os, const State &s)
{
    os << endl << "room: " << s.room << endl;
    for (int i = 0; i < ROOMS; i++)
        os << s.light[i] << " ";
    os << endl;
}

class StateHash
{
public:
    size_t operator() (const State &s) const
    {
        int res = s.room;
        for (int i = 0; i < ROOMS; i++) {
            res = res * 2 + s.light[i];
        }
        return res;
    }
};

bool operator<(const State &s1, const State &s2)
{
    if (s1.room != s2.room)
        return s1.room < s2.room;
    for (int i = 0; i < ROOMS; i++) {
        if (s1.light[i] != s2.light[i])
            return s1.light[i] < s2.light[i];
    }
}

State &State::operator=(const State &s)
{
    room = s.room;
    for (int i = 0; i <ROOMS; i++)
        light[i] = s.light[i];
}

class Op
{
public:
    Op() {}
    Op(int a, int b):
        operation(a),
        target(b) {}

    int operation;
    int target;
};

class Moves
{
public:
    Moves() {}
    Moves(State a):
        cur(a) {}
    Moves(State a, vector<Op> b):
        cur(a),
        records(b) {}

    Moves &operator=(const Moves&m);
    State cur;
    vector<Op> records;
};

Moves &Moves::operator=(const Moves &m)
{
    cur = m.cur;
    records=m.records;
}

vector<int> graph[ROOMS];
vector<int> switches[ROOMS];
Moves res;
void bfs(int num);
void is_res(Moves m, int target);
void output(int n, int r);
int main()
{
    int r, d, s;
    int count = 1;
    while (cin >> r >> d >> s) {
        if (!r && !d && !s)
            break;

        for (int i = 0; i < ROOMS; i++) {
            graph[i].clear();
            switches[i].clear();
        }
        for (int i = 0; i < d; i++) {
            int p, q;
            cin >> p >> q;
            graph[p].push_back(q);
            graph[q].push_back(p);
        }
        for (int i = 0; i < s; i++) {
            int p, q;
            cin >> p >> q;
            if (p == q)
                continue;
            switches[p].push_back(q);
        }

        if (r == 1) {
            output(count++, r);
            continue;
        }
        res = Moves();
        bfs(r);
        output(count, r);
        count++;
    }
}

void output(int n, int r)
{
    cout << "Villa #" << n << endl;
    if (res.records.size() == 0 && r != 1) {
        cout << "The problem cannot be solved." << endl << endl;
        return;
    }
    cout << "The problem can be solved in " << res.records.size()
        << " steps:" << endl;
    for (int i = 0; i < res.records.size(); i++) {
        int p, q;
        p = res.records[i].operation;
        q = res.records[i].target;
        cout << "- " << handles[p] << " " << q << "." << endl;
    }
    cout << endl;
}

void bfs(int num)
{
    bool tlights[ROOMS];
    memset(tlights, 0, sizeof(tlights));
    tlights[1] = 1;
    State init_state = State(1, tlights);
    Moves init(init_state);

    queue<Moves> q;
    //map<State, int> occur;
    unordered_map<State, int, StateHash> occur;
    occur[init_state] = 0;
    q.push(init);

    while (!q.empty()) {
        Moves now = q.front();
        is_res(now, num);
        for (int i = 0; i < 3; i++) {
            bool nlights[ROOMS];
            int nroom;
            vector<Op> nop;
            if (i == 0 || i == 1) {
                for (int j = 0; j < switches[now.cur.room].size(); j++) {
                    int to_room = switches[now.cur.room][j];
                    bool flag = 0;
                    if (i == 0 && !now.cur.light[to_room]) {
                        for (int k = 0; k < ROOMS; k++)
                            nlights[k] = now.cur.light[k];
                        nlights[to_room] = 1;
                        nroom = now.cur.room;
                        nop = now.records;
                        nop.push_back(Op(0, to_room));
                        flag = 1;
                    }
                    else if (i && now.cur.light[to_room]) {
                        for (int k = 0; k < ROOMS; k++)
                            nlights[k] = now.cur.light[k];
                        nlights[to_room] = 0;
                        nroom = now.cur.room;
                        nop = now.records;
                        nop.push_back(Op(1, to_room));
                        flag = 1;
                    }

                    if (flag) {
                        Moves new_move(State(nroom, nlights), nop);
                        if (occur.find(new_move.cur) == occur.end() || 
                            occur[new_move.cur] > nop.size()) {
                            occur[new_move.cur] = nop.size();
                            if (res.records.size() == 0 ||
                                    new_move.records.size() < res.records.size())
                            q.push(new_move);
                        }
                    }
                }
            }
            else if (i == 2) {
                for (int j = 0; j < graph[now.cur.room].size(); j++) {
                    bool flag = 0;
                    int to_room = graph[now.cur.room][j];
                    if (now.cur.light[to_room]) {
                        for (int k = 0; k < ROOMS; k++)
                            nlights[k] = now.cur.light[k];
                        nroom = to_room;
                        nop = now.records;
                        nop.push_back(Op(2, to_room));
                        flag = 1;
                    }
                    if (flag) {
                        Moves new_move(State(nroom, nlights), nop);
                        if (occur.find(new_move.cur) == occur.end() || 
                            occur[new_move.cur] > nop.size()) {
                            occur[new_move.cur] = nop.size();
                            if (res.records.size() == 0 ||
                                    new_move.records.size() < res.records.size())
                            q.push(new_move);
                        }
                    }
                }
            }
        }
        q.pop();
    }
}

void is_res(Moves m, int target)
{
    for (int i = 0; i < target; i++)
        if (m.cur.light[i])
            return;
    if (!m.cur.light[target])
        return;
    if (m.cur.room != target)
        return;

    if (res.records.size() == 0 || res.records.size() > m.records.size())
        res = m;
}
