/* Title: 10050
 * 考察点：简单的去除倍数*/
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int days;
        cin >> days;
        int pnum;
        cin >> pnum;
        int h;
        vector<int> party;
        for (int j = 0; j < pnum; j++) {
            cin >> h;
            party.push_back(h);
        }

        int date[3700];
        memset(date, 0, 3700 * sizeof(int));
        for (int j = 0; j < pnum; j++) {
            int temp = party[j];
            while (temp <= days) {
                if (temp % 7 != 6 && temp % 7 != 0)
                    date[temp] = 1;
                temp += party[j];
            }
        }

        int sum = 0;
        for (int j = 1; j <= days; j++)
            if (date[j] == 1)
                sum++;

        cout << sum << endl;
    }
}
