/* Title: 10026
 * 考察点 ：贪心求一个排列
 * 注意这种整条序列较为稳定的问题，交换相邻元素可以比较大小的问题*/
#include <iostream>
#include <vector>
using namespace std;

class Task
{
public:
    Task(int a, int b, int c):
        id(a),
        days(b),
        fine(c) {}
    int id;
    int days;
    int fine;
};

bool operator<(const Task &t1, const Task &t2)
{
    if(t1.days * t2.fine != t2.days * t1.fine)
    return t1.days * t2.fine < t2.days * t1.fine;
    else
        return t1.id < t2.id;
}

bool operator>(const Task &t1, const Task &t2)
{
    return !(t1 < t2);
}

int main()
{
    int num;
    cin >> num;

    for (int n = 0; n < num; n++) {
        int tasks;
        cin >> tasks;
        vector<Task> t;
        for (int i = 1; i <= tasks; i++) {
            int b, c;
            cin >> b >> c;
            t.push_back(Task(i, b, c));
        }

        for (int i = 0; i < t.size(); i++) {
            for (int j = 0; j < t.size() - 1 - i; j++) {
                if (t[j+1] < t[j]) {
                    Task temp = t[j];
                    t[j] = t[j+1];
                    t[j+1] = temp;
                }
            }
        }

        cout << t[0].id;
        for (int i = 1; i < t.size(); i++)
            cout << " " << t[i].id;
        cout << endl;
        if (n != num-1)
            cout << endl;
    }
}
