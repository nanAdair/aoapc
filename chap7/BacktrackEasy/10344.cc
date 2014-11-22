/* Title: 10344
 * 考察点：数组的全排列，加判断*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool is_23(const vector<int> &number);
bool is_end(const vector<int> &number);
bool find_next(vector<int> &number);
void print(const vector<int> &number);
int main()
{
    while (1) {
        vector<int> number;
        for (int i = 0; i < 5; i++) {
            int t;
            cin >> t;
            number.push_back(t);
        }
        if (is_end(number))
            break;

        sort(number.begin(), number.end());
        bool flag = 0;
        while (1) {
            //print(number);
            if (is_23(number)) {
                flag = 1;
                break;
            }
            if(!find_next(number))
                break;
        }
        if (flag)
            cout << "Possible" << endl;
        else
            cout << "Impossible" << endl;
    }
}

char op[] = {'+', '-', '*'};
bool construct_res(const vector<int> &number, int depth, int res)
{
    if (depth == 5)
        return res == 23;
    int store = res;
    bool flag = 0;
    for (int i = 0; i < 3; i++) {
        res = store;
        if (op[i] == '+')
            res += number[depth+1];
        else if (op[i] == '-')
            res -= number[depth+1];
        else
            res *= number[depth+1];
        flag |= construct_res(number, depth+1, res);
    }
    //if (depth == 0) {
        //res = number[0] + number[1];
        //flag |= construct_res(number, 1, res);
        //res = number[0] * number[1];
        //flag |= construct_res(number, 1, res);
        //res = number[0] - number[1];
        //flag |= construct_res(number, 1, res);
    //}
    //else {
        //res += number[depth+1];
        //flag |= construct_res(number, depth+1, res);
        //res = store;
        //res -= number[depth+1];
        //flag |= construct_res(number, depth+1, res);
        //res = store;
        //res *= number[depth+1];
        //flag |= construct_res(number, depth+1, res);
    //}
    return flag;
}

bool is_23(const vector<int> &number)
{
    return construct_res(number, 0, number[0]);
}

void print(const vector<int> &number)
{
    for (vector<int>::const_iterator it = number.begin(); it != number.end(); it++) 
        cout << *it << " ";
    
    cout << endl;
}

bool find_next(vector<int> &number)
{
    int i = number.size() - 1;
    while (i > 0 && number[i-1] >= number[i])
        i--;

    if (i == 0)
        return 0;

    int index;
    int min_value = 0x7fffffff;
    for (int j = i; j < number.size(); j++) {
        if (number[j] < min_value && number[j] > number[i-1]) {
            min_value = number[j];
            index = j;
        }
    }

    int temp = number[index];
    number[index] = number[i-1];
    number[i-1] = temp;

    sort(number.begin()+i, number.end());
    return 1;
}

bool is_end(const vector<int> &number)
{
    for (vector<int>::const_iterator it = number.begin(); it != number.end(); it++)
        if (*it != 0)
            return 0;
    return 1;
}
