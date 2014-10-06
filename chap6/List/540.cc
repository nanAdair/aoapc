#include <iostream>
#include <list>
#include <cstring>
using namespace std;

void process(list<int> &qq, int num, int team[], list<int>::iterator position[]);
int main()
{
    int gnum;
    int count = 1;
    while (cin >> gnum && gnum != 0) {
        int team[1000000];
        list<int> qq;
        list<int>::iterator position[1001];
        memset(team, 0, 1000000 * sizeof(int));
        for (int i = 0; i < 1001; i++)
            position[i] = qq.end();
        for (int i = 0; i < gnum; i++) {
            int mnum;
            cin >> mnum;
            for (int j = 0; j < mnum; j++) {
                int number;
                cin >> number;
                team[number] = i + 1;
            }
        }

        int team_number;
        string command;
        cout << "Scenario #" << count << endl;
        while (cin >> command) {
            if (command == "ENQUEUE") {
                cin >> team_number;
                process(qq, team_number, team, position);
            }
            else if (command == "DEQUEUE") {
                int res = qq.front();
                cout << res << endl;

                if (position[team[res]] == qq.begin())
                    position[team[res]] = qq.end();
                qq.erase(qq.begin());
            }
            else
                break;
        }

        cout << endl;
        count++;
    }
}

void process(list<int> &qq, int num, int team[], list<int>::iterator position[])
{
    list<int>::iterator it = position[team[num]];
    if (it == qq.end()) {
        qq.push_back(num);
        position[team[num]] = --qq.end();
    }
    else {
        qq.insert(++it, num);
        position[team[num]] = --it;
    }
}
