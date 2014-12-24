/* Title: 10020
 * 考察点：贪心，区间覆盖，确定了左端点后，找到最远的右端点，
 * 能够覆盖左端点。
 * 然后把新的右端点设置为左端点。
 * 在O(n)时间内可以找到所有序列点可以覆盖的最远连续右端点
 * 判断右端点是否能覆盖到目标即可。*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Point
{
public:
    Point(int a, int b):
        l(a),
        r(b) {}
    int l;
    int r;
};

bool operator<(const Point &p1, const Point &p2)
{
    return p1.l < p2.l;
    //if (p1.l != p2.l)
        //return p1.l < p2.l;
    //else
        //return p1.r < p2.r;
}

bool cmp(const Point &p1, const Point &p2)
{
    return p1 < p2;
}
int main()
{
    int num;
    cin >> num;
    for (int n = 0; n < num; n++) {
        vector<Point> base;
        int target;
        cin >> target;
        int a, b;
        while (cin >> a >> b) {
            if (!a && !b)
                break;
            base.push_back(Point(a, b));
        }

        sort(base.begin(), base.end(), cmp);
        int cur, right, last_index, index;
        cur = right = 0;
        last_index = index = -1;
        vector<Point> res;
        for (int i = 0; i < base.size(); i++) {
            right = 0;
            while (base[i].l <= cur && i < base.size()) {
                if (base[i].r > right) {
                    right = base[i].r;
                    index = i;
                }
                i++;
            }
            if (last_index != index) {
                res.push_back(base[index]);
                last_index = index;
                cur = right;
            }
            else
                break;
        }
        if (cur < target)
            cout << 0 << endl;
        else {
            cout << res.size() << endl;
            for (int i = 0; i < res.size(); i++)
                cout << res[i].l << " " << res[i].r << endl;
        }
        if (n != num-1)
            cout << endl;
    }
}
