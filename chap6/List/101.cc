/* Title: 101
 * 考察点：还是模拟，注意认真读题！理解题意！
 * WA了一个小时在这里*/
#include <iostream>
#include <list>
#include <string>
#include <sstream>
using namespace std;

void output(list<int> piles[], int n);
list<int>::iterator find_pos(list<int> &pile, int value);
void moveonto(list<int> piles[], int a, int b, int pos[]);
void moveover(list<int> piles[], int a, int b, int pos[]);
void pileonto(list<int> piles[], int a, int b, int pos[]);
void pileover(list<int> piles[], int a, int b, int pos[]);

int main()
{
    int n;
    cin >> n;
    string verb;

    list<int> piles[25];
    int pos[25];

    for (int i = 0; i < n; i++) {
        piles[i].push_back(i);
        pos[i] = i;
    }

    while (cin >> verb && verb != "quit") {
        string prep;
        int a, b;

        cin >> a >> prep >> b;
        if (pos[a] == pos[b] || a >= n || b >= n) 
            continue;
        if (verb == "move" && prep == "onto")
            moveonto(piles, a, b, pos);
        else if (verb == "move" && prep == "over")
            moveover(piles, a, b, pos);
        else if (verb == "pile" && prep == "onto")
            pileonto(piles, a, b, pos);
        else if (verb == "pile" && prep == "over")
            pileover(piles, a, b, pos);
    }

    output(piles, n);
}

void moveonto(list<int> piles[], int a, int b, int pos[])
{
    int la, lb;
    list<int>::iterator it;
    la = pos[a];
    lb = pos[b];

    it = find_pos(piles[la], a);
    it = piles[la].erase(it);
    while (it != piles[la].end()) {
        piles[*it].push_back(*it);
        pos[*it] = *it;
        it = piles[la].erase(it);
    }

    it = find_pos(piles[lb], b);
    piles[lb].insert(++it, a);

    while (it != piles[lb].end()) {
        piles[*it].push_back(*it);
        pos[*it] = *it;
        it = piles[lb].erase(it);
    }

    pos[a] = lb;
}

void moveover(list<int> piles[], int a, int b, int pos[])
{
    int la, lb;
    list<int>::iterator it;
    la = pos[a];
    lb = pos[b];

    it = find_pos(piles[la], a);
    it = piles[la].erase(it);
    while (it != piles[la].end()) {
        piles[*it].push_back(*it);
        pos[*it] = *it;
        it = piles[la].erase(it);
    }
    piles[lb].push_back(a);
    pos[a] = lb;

}

void pileonto(list<int> piles[], int a, int b, int pos[])
{
    int la, lb;
    list<int>::iterator it_a, it_b, it_aend;
    la = pos[a];
    lb = pos[b];

    it_a = find_pos(piles[la], a);
    it_b = find_pos(piles[lb], b);
    it_aend = piles[la].end();

    for (list<int>::iterator it = it_a; it != it_aend; it++)
        pos[*it] = lb;

    piles[lb].insert(++it_b, it_a, it_aend);
    while (it_b != piles[lb].end()) {
        piles[*it_b].push_back(*it_b);
        pos[*it_b] = *it_b;
        it_b = piles[lb].erase(it_b);
    }
    piles[la].erase(it_a, it_aend);
}

void pileover(list<int> piles[], int a, int b, int pos[])
{
    int la, lb;
    list<int>::iterator it_a, it_b, it_aend;
    la = pos[a];
    lb = pos[b];

    it_a = find_pos(piles[la], a);
    it_b = find_pos(piles[lb], b);
    it_aend = piles[la].end();

    for (list<int>::iterator it = it_a; it != it_aend; it++)
        pos[*it] = lb;

    piles[lb].insert(piles[lb].end(), it_a, it_aend);
    piles[la].erase(it_a, it_aend);
}

void output(list<int> piles[], int n)
{
    list<int>::iterator it;

    for (int i = 0; i < n; i++) {
        cout << i << ":";
        for (it = piles[i].begin(); it != piles[i].end(); it++) {
            cout << " " << *it;
        }
        cout << endl;
    }
}

list<int>::iterator find_pos(list<int> &pile, int value)
{
    list<int>::iterator it;
    for (it = pile.begin(); it != pile.end(); it++)
        if (*it == value)
            return it;
}
