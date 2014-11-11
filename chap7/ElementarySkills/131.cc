/* Title: 131
 * 考察点：恶心人的模拟题，一共9种情况，一种一种分析
 * 遍历一个长度为5的序列
 * 还要好好看看子集生成的方法
 * 可以用位运算生成子集表示，为1的push，为0的换deck push*/
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cstring>
using namespace std;

void construct_best(const vector<string> &hand, const vector<string> &deck, int num);
void best_type(vector<string> &seq);
void output();
string result[] = {"straight-flush", "four-of-a-kind", "full-house", "flush",
                    "straight", "three-of-a-kind", "two-pairs", "one-pair", "highest-card"};
bool flag[10];
int main()
{
    string s;
    while (getline(cin, s)) {
        stringstream ss(s);
        vector<string> hand, deck;
        for (int i = 0; i < 5; i++) {
            string temp;
            ss >> temp;
            hand.push_back(temp);
        }
        for (int i = 0; i < 5; i++) {
            string temp;
            ss >> temp;
            deck.push_back(temp);
        }
        memset(flag, 0, sizeof(flag));
        for (int i = 0; i <= 5; i++) 
            construct_best(hand, deck, i);
        cout << "Hand: ";
        for (int i = 0; i < 5; i++)
            cout << hand[i] << " ";
        cout << "Deck: ";
        for (int i = 0; i < 5; i++)
            cout << deck[i] << " ";
        output();
    }
}

void construct_best(const vector<string> &hand, const vector<string> &deck, int num)
{
    vector<string> best;
    if (num == 0) {
        for (int i = 0; i < 5; i++)
            best.push_back(hand[i]);
        best_type(best);
        return;
    }
    if (num == 5) {
        for (int i = 0; i < 5; i++)
            best.push_back(deck[i]);
        best_type(best);
        return;
    }
    if (num == 1) {
        for (int i = 0; i < 5; i++) {
            best.clear();
            int j = 0;
            while (j < 5) {
                if (j != i)
                    best.push_back(hand[j]);
                j++;
            }
            best.push_back(deck[0]);
            best_type(best);
        }
        return;
    }
    if (num == 4) {
        for (int i = 0; i < 5; i++) {
            best.clear();
            best.push_back(hand[i]);
            for (int j = 0; j < 4; j++)
                best.push_back(deck[j]);
            best_type(best);
        }
        return;
    }
    if (num == 2) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                int k = 0;
                best.clear();
                while (k < 5) {
                    if (k != i && k != j)
                        best.push_back(hand[k]);
                    k++;
                }
                best.push_back(deck[0]);
                best.push_back(deck[1]);
                best_type(best);
            }
        }
        return;
    }
    if (num == 3) {
        for (int i = 0; i < 5; i++) {
            for (int j = i+1; j < 5; j++) {
                //if (i == j)
                    //continue;
                best.clear();
                best.push_back(hand[i]);
                best.push_back(hand[j]);
                for (int k = 0; k < 3; k++)
                    best.push_back(deck[k]);
                best_type(best);
            }
        }
    }
}

void best_type(vector<string> &seq)
{
    bool is_same_color = 0; // 5张同色
    bool is_three_of_a_kind = 0 ; // 三张相同
    bool is_four_of_a_kind = 0; // 四张相同
    bool is_continuous = 0; // 是否连续
    int number_of_two = 0; // 2张相同的对数
    bool cards[14][4];
    memset(cards, 0, sizeof(cards));

    for (int i = 0; i < 5; i++) {
        int x, y;
        switch(seq[i][0]) {
            case 'A':
                x = 1;
                break;
            case 'T':
                x = 10;
                break;
            case 'J':
                x = 11;
                break;
            case 'Q':
                x = 12;
                break;
            case 'K':
                x = 13;
                break;
            default:
                x = seq[i][0] - '0';
                break;
        }
        switch(seq[i][1]) {
            case 'C':
                y = 0;
                break;
            case 'D':
                y = 1;
                break;
            case 'H':
                y = 2;
                break;
            case 'S':
                y = 3;
                break;
        }
        cards[x][y] = 1;
    }

    int color_number[4];
    int cards_number[14];
    memset(color_number, 0, sizeof(color_number));
    memset(cards_number, 0, sizeof(cards_number));
    for (int i = 0; i < 4; i++) {
        for (int k = 1; k < 14; k++) {
            if (cards[k][i] == 1) {
                color_number[i] += 1;
                cards_number[k] += 1;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        if (color_number[i] == 5)
            is_same_color = 1;
    }
    for (int i = 1; i < 14; i++) {
        if (cards_number[i] == 2)
            number_of_two += 1;
        else if (cards_number[i] == 3)
            is_three_of_a_kind = 1;
        else if (cards_number[i] == 4)
            is_four_of_a_kind = 1;
    }
    for (int i = 1; i <= 10; i++) {
        int j;
        bool test_flag = 1;
        if (i == 10) {
            for (j = 0; j < 4; j++) {
                if (cards_number[(i+j)] != 1) {
                    test_flag = 0;
                    break;
                }
            }
            if (test_flag) {
                if(cards_number[1] != 1)
                    test_flag = 0;
            }
        }
        else {
            for (j = 0; j < 5; j++) {
                if (cards_number[(i+j)] != 1) {
                    test_flag = 0;
                    break;
                }
            }
        }
        if (test_flag)
            is_continuous = 1;
    }

    if (is_continuous && is_same_color)
        flag[0] = 1;
    if (is_four_of_a_kind)
        flag[1] = 1;
    if (number_of_two == 1 && is_three_of_a_kind)
        flag[2] = 1;
    if (is_same_color)
        flag[3] = 1;
    if (is_continuous)
        flag[4] = 1;
    if (is_three_of_a_kind)
        flag[5] = 1;
    if (number_of_two == 2)
        flag[6] = 1;
    if (number_of_two == 1)
        flag[7] = 1;
    flag[8] = 1;
}

void output()
{
    for (int i = 0; i < 9; i++)
        if (flag[i]) {
            cout << "Best hand: " << result[i] << endl;
            return;
        }
}
