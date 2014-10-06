/* Title: 11111
 * 考察点：简单的递归
 * 注意负数要在正数的前面*/
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;

int play(vector<int> &dolls, int left, int right);
int main()
{
    string temp;
    string str1 = ":-) Matrioshka!";
    string str2 = ":-( Try again.";

    while (getline(cin, temp)) {
        stringstream ss(temp);
        vector<int> dolls;
        int num;
        while (ss >> num)
            dolls.push_back(num);

        bool flag = 1;
        if(play(dolls, 0, dolls.size()-1))
            cout << str1 << endl;
        else 
            cout << str2 << endl;
    }
}

int play(vector<int> &dolls, int left, int right)
{
    if (dolls[left] > 0)
        return 0;
    if (left + 1 == right && dolls[left] == -dolls[right])
        return 1;
    else if (left + 1 == right && dolls[left] != -dolls[right])
        return 0;

    int sum, index, indexl, indexr;
    sum = 0;
    index = indexl = left + 1;

    while (index < right) {
        if (dolls[index] == -dolls[indexl]) {
            indexr = index;
            if (play(dolls, indexl, indexr)) {
                sum += abs(dolls[indexl]);
                index++;
                indexl = index;
            }
            else 
                return 0;
        }
        else
            index++;
    }

    if (indexl != index)
        return 0;
    if (sum < -dolls[left])
        return 1;
    return 0;
}
