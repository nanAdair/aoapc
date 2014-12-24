/* Title: 10382
 * 考察点：贪心，圆和条带上沿的左右交点做为区间的左右端点
 * 然后同样地贪心找连续最右端点
 * 注意double类型的变量 /= 2可能结果和想象不同*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Point
{
    Point(double x1, double x2):
        l(x1),
        r(x2) {}
    double l;
    double r;
};

bool cmp(const Point &p1, const Point &p2)
{
    return p1.l < p2.l;
}

int main()
{
    int n;
    double l, w;
    while (cin >> n >> l >> w) {
        vector<Point> sprinkles;
        for (int i = 0; i < n; i++) {
            double x, r;
            cin >> x >> r;
            double x1, x2;
            double tmp = sqrt(r * r - (w/2.0) * (w/2.0));
            // Right!!!!!
            x1 = x - sqrt(r * r - (w/2.0) * (w/2.0));
            x2 = x + sqrt(r * r - (w / 2.0) * (w/2.0));
            // Wrong!!!!!
            //w /= 2.0;
            //x1 = x - sqrt(r * r - w *w);
            //x2 = x + sqrt(r * r - w* w);
            sprinkles.push_back(Point(x1, x2));
        }

        sort(sprinkles.begin(), sprinkles.end(), cmp);
        for (int i = 0; i < n; i++)
            cout << sprinkles[i].l << " " << sprinkles[i].r << endl;

        if (sprinkles[0].l > 0) {
            cout << -1 << endl;
            continue;
        }

        double start, largest;
        start = largest = 0;
        int i, count;
        i = count = 0;
        while (i < sprinkles.size() && largest < l) {
            while (i < sprinkles.size() && sprinkles[i].l <= start) {
                if (sprinkles[i].r > largest) 
                    largest = sprinkles[i].r;
                i++;
            }
            if (largest > start) {
                count++;
                start = largest;
            }
            else 
                break;
        }
        if (largest < l)
            cout << -1 << endl;
        else
            cout << count << endl;
    }
}
