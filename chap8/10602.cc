/* Title: 10602
 * 考察点：贪心
 * 对当前的字符串的最长前缀，遍历去找同前缀的字符串*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int n = 0; n < T; n++) {
        int num;
        cin >> num;
        vector<string> basket;
        string handle;
        for (int m = 0; m < num; m++) {
            string temp;
            cin >> temp;
            if (m == 0)
                handle = temp;
            else
                basket.push_back(temp);
        }

        int sum = handle.size();
        vector<string> res;
        res.push_back(handle);

        int length;
        while (!basket.empty()) {
            bool found = 0;
            vector<string>::iterator rit = basket.end();
            //for (int i = handle.size(); i >= 0; i--) {
            for (int i = handle.size(); i > 0; i--) {
                string prefix = string(handle.begin(), handle.begin() + i);
                length = prefix.length();
                for (vector<string>::iterator it = basket.begin(); it != basket.end(); it++) {
                    if (it->length() < length)
                        continue;
                    if (string(it->begin(), it->begin() + length) == prefix) {
                        rit = it;
                        break;
                    }
                }
                if (rit != basket.end()) {
                    handle = *rit;
                    sum += (rit->length() - length);
                    res.push_back(handle);
                    basket.erase(rit);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                handle = basket[0];
                sum += handle.length();
                res.push_back(handle);
                basket.erase(basket.begin());
            }
        }

        cout << sum << endl;
        for (int i = 0; i < res.size(); i++)
            cout << res[i] << endl;
    }
}
