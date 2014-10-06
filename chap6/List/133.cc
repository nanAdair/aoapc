/* Title: 133
 * 考察点：list的删除以及移动操作，以及这些操作带来的后果*/
#include <iostream>
#include <list>
using namespace std;

list<int>::iterator movek(list<int> &l, list<int>::iterator it, int k);
list<int>::iterator movem(list<int> &l, list<int>::iterator it, int m);
list<int>::iterator renewk(list<int> &l, list<int>::iterator it);
list<int>::iterator renewm(list<int> &l, list<int>::iterator it);

int main()
{
    int N, k, m;
    while (cin >> N >> k >> m) {
        if (N == 0 && k == 0 && m == 0)
            break;
        list<int> persons;
        for (int i = 1; i <= N; i++)
            persons.push_back(i);

        list<int>::iterator itk, itm;
        itk = persons.begin();
        itm = --persons.end();

        while (!persons.empty()) {
            itk = movek(persons, itk, k);
            itm = movem(persons, itm, m);

            if (itk != itm) {
                string temp;
                temp = *itk >= 10 ? " " : "  ";
                cout << temp << *itk;
                temp = *itm >= 10 ? " " : "  ";
                cout << temp << *itm;
                itk = persons.erase(itk);
                if (itk == itm)
                    itk++;
                itm = persons.erase(itm);
            }
            else {
                string temp;
                temp = *itk >= 10 ? " " : "  ";
                cout << temp << *itk;
                itk = itm = persons.erase(itk);
            }
            if (!persons.empty())
                cout << ",";

            itk = renewk(persons, itk);
            itm = renewm(persons, itm);
        }
        cout << endl;
    }
}

list<int>::iterator movek(list<int> &l, list<int>::iterator it, int k)
{
    list<int>::iterator temp = it;
    int i = 1;
    while (i < k) {
        temp++;
        if (temp == l.end())
            temp = l.begin();
        i++;
    }

    return temp;
}

list<int>::iterator movem(list<int> &l, list<int>::iterator it, int m)
{
    list<int>::iterator temp = it;
    int i = 1;
    while (i < m) {
        if (temp == l.begin())
            temp = --l.end();
        else
            temp--;
        i++;
    }

    return temp;
}

list<int>::iterator renewk(list<int> &l, list<int>::iterator it)
{
    if (it == l.end())
        return l.begin();
    else
        return it;
}

list<int>::iterator renewm(list<int> &l, list<int>::iterator it)
{
    if (it == l.end())
        it = l.begin();
    return movem(l, it, 2);
}
