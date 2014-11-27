/* Title: 10887
 * 简单set判重，2sAC看来set不适合用来做hash表*/
#include <iostream>
#include <string>
#include <set>
#include <vector>
using namespace std;

int main()
{
    int num;
    cin >> num;
    for (int n = 1; n <= num; n++) {
        int p, q;
        cin >> p >> q;
        string sj;
        getline(cin, sj); 
        vector<string> s1, s2;
        for (int i = 0; i < p; i++) {
            string temp;
            getline(cin, temp);
            s1.push_back(temp);
        }
        for (int i = 0; i < q; i++) {
            string temp;
            getline(cin, temp);
            s2.push_back(temp);
        }

        set<string> concat;
        for (int i = 0; i < p; i++) {
            for (int j = 0; j < q; j++) {
                string ns = s1[i] + s2[j];
                if (concat.find(ns) == concat.end())
                    concat.insert(ns);
            }
        }

        cout << "Case " << n << ": " << concat.size() << endl;
    }
}
