/* Title：152
 * 考察点：原本以为要按照点与点之间距离去排序，后来想想是不可能的，因为距离是点对之间
 * 的，而一个点与这个点距离近，但是这个邻居点可能和另外的点距离更近的。
 * 解决方法最后是直接暴力全部距离*/
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iomanip>
using namespace std;

struct Tree 
{
    int x;
    int y;
    int z;
};

typedef struct Tree tree;

#define MAX 5001
int dis(const tree, const tree);
int cal(tree data[], int num, int index);

int main()
{
    tree data[MAX];
    int n = 0;

    int x, y, z;
    while (cin >> x >> y >> z) {
        if (x == 0 && y == 0 && z == 0)
            break;
        data[n].x = x;
        data[n].y = y;
        data[n].z = z;
        n++;
    }

    int count[11], lastDis;
    memset(count, 0, 11 * sizeof(int));

    for (int i = 0; i < n; i++) {
        int index = cal(data, n, i);
        if (index < 10)
            count[index] += 1;
    }

    for (int i = 0; i < 10; i ++)
        cout << setw(4) << count[i];
    cout << endl;
}

int cal(tree data[], int num, int index)
{
    int distance;
    distance = MAX;
    for (int i = 0; i < num; i++) {
        if (i == index)
            continue;
        int temp = dis(data[i], data[index]);
        if (temp < distance)
            distance = temp;
    }

    return distance;
}

int dis(tree s, tree t)
{
    int dis = (s.x - t.x) * (s.x - t.x) + (s.y - t.y) * (s.y - t.y) + (s.z - t.z) * (s.z - t.z);
    return (int)sqrt(dis);
}
