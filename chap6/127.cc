/* Title: 127
 * 考察点：模拟题，栈操作直接用STL即可
 * 注意用数组保存每个栈会TLE
 * 还要另外保存每个栈的左边和右边，把空栈直接排除掉*/
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cstdio>
#include <vector>
using namespace std;

void output(stack<string> piles[]);
void simulate(stack<string> piles[]);
int move(stack<string> piles[], int index);
bool can_move(stack<string> piles[], int right, int left);
int cmp(string s1, string s2);

int card_left[52], card_right[52];
int main()
{
    string line1, line2;
    while (getline(cin, line1) && line1[0] != '#') {
        getline(cin, line2);

        stringstream ss1(line1);
        stringstream ss2(line2);

        stack<string> piles[52];
        for (int i = 0; i < 52; i++) {
            string cards;
            if (i < 26) {
                ss1 >> cards;
                piles[i].push(cards);
            }
            else {
                ss2 >> cards;
                piles[i].push(cards);
            }
            card_left[i] = i - 1;
            card_right[i] = i + 1;
        }

        simulate(piles);

        output(piles);
    }
}

void output(stack<string> piles[])
{
    int sum = 0;
    int i = 0;
    while (i < 52) {
        sum++;
        i = card_right[i];
    }

    if (sum > 1)
        cout << sum << " piles remaining: ";
    else
        cout << sum << " pile remaining: ";

    int num = 0;
    i = 0;
    while (i < 52) {
        num++;
        cout << piles[i].size();
        string temp = (num != sum) ? " " : "";
        cout << temp;
        i = card_right[i];
    }
    cout << endl;
}

void simulate(stack<string> piles[])
{
    int index = 0;

    while (index < 52) {
        if (index == 0 || piles[index].empty()) {
            index++;
            continue;
        }

        int res;
        res = move(piles, index);

        if (res != -1) 
            index = res;
        else
            index++;
    }
}

int move(stack<string> piles[], int index)
{
    int left1, left2, left3;

    left2 = left3 = -1;
    left1 = card_left[index];
    if (left1 != -1)
        left2 = card_left[left1];
    if (left2 != -1)
        left3 = card_left[left2];

    if (left1 == -1)
        return -1;
    if (left3 != -1) {
        if (can_move(piles, index, left3))
            return left3;
    }
    if (can_move(piles, index, left1))
        return left1;
    else
        return -1;
}

bool can_move(stack<string> piles[], int right, int left)
{
    if (cmp(piles[right].top(), piles[left].top())) {
        string temp = piles[right].top();
        piles[right].pop();
        piles[left].push(temp);

        if (piles[right].empty()) {
            int l, r;
            l = card_left[right];
            r = card_right[right];
            card_left[r] = l;
            card_right[l] = r;
        }
        return 1;
    }
    return 0;
}

int cmp(string s1, string s2)
{
    if (s1[0] == s2[0] || s1[1] == s2[1])
        return 1;
    return 0;
}
