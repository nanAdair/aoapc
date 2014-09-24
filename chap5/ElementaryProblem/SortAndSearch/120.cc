/* Title: 120
 * 考察点：
 * 1. getline返回可以直接在while循环中判断，如果是eof的话，可以直接跳出
 * 2. vector对象，在函数调用中，要按引用传递，可以保证对vector操作起作用，如果对象传
 *    过去是无效的。或者就用指针。无论是指针还是引用，在定义的时候必须定义为vector对
 *    象，不能是vector对象类型的指针，这样会段错误。
 * 3. 在数组交换的时候，注意index，这个试一试就可以了，注意右括号包含还是不包含
 * 4. 狂输出时，可以利用sleep来看程序中间结果
 * 5. 这道题的算法思路，就是找到最大的，交换到index为0处，然后再交换一次，把最大的交
 *    换到最右边，依次类推。最后使得整个序列顺序化*/
#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
using namespace std;

#define MAX 31
void swap(int num[], int right);
void sort_pancakes(int num[], int n, vector<int> *res);
bool is_ordered(int num[], int n);
int main()
{
    string temp;
    while (getline(cin, temp)) {
        cout << temp << endl;
        stringstream ss(temp);
        int pancakes[MAX];
        int i = 0;
        while (ss >> pancakes[i])
            i++;

        vector<int> res;

        sort_pancakes(pancakes, i, &res);

        for (vector<int>::iterator it = res.begin(); it != res.end(); it++) {
            cout << *it << " ";
        }
        cout << 0 << endl;
    }
}

void sort_pancakes(int num[], int n, vector<int> *res)
{
    int max_number, round;
    max_number = round = 0;
    while (!is_ordered(num, n)) {
        int index = 0;
        for (int i = 0; i < n - round; i++) {
            if (num[i] > max_number) {
                max_number = num[i];
                index = i;
            }
        }

        if (index != 0) {
            swap(num, index);
            //res.push_back(n - index);
            res->push_back(n - index);
        }
        round++;
        swap(num, n - round);
        //res.push_back(round);
        res->push_back(round);
        max_number = 0;
    }
}

bool is_ordered(int num[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        if (num[i] > num[i + 1])
            return 0;
    }
    return 1;
}

void swap(int num[], int right)
{
    for (int i = 0; i <= right / 2; i++) {
        int temp = num[i];
        num[i] = num[right - i];
        num[right - i] = temp;
    }
}
