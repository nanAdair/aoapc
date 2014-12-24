/* Title: 10245
 * 考察点：递归，分治*/
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Point
{
    Point(double a, double b):
        x(a),
        y(b) {}

    double x, y;
};

bool operator<(const Point &a, const Point &b)
{
    return a.x < b.x;
}

double dis(const Point &a, const Point &b)
{
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

double solve(const vector<Point> &g, int l, int r)
{
    if (l == r)
        return 10010;
    if (l == r - 1)
        return dis(g[l], g[r]);
    int mid = l + (r - l) / 2;
    double min_dis1, min_dis2, min_dis;
    min_dis1 = solve(g, l, mid);
    min_dis2 = solve(g, mid+1, r);
    min_dis = min_dis1 > min_dis2 ? min_dis2 : min_dis1;

    vector<Point> tmp;
    for (int i = l; i <= r; i++) {
        if (fabs(g[i].x - g[mid].x) < min_dis)
            tmp.push_back(g[i]);
    }

    for (int i = 0; i < tmp.size(); i++) {
        for (int j = i+1; j < tmp.size(); j++) {
            double distant = dis(tmp[i], tmp[j]);
            if (min_dis > distant)
                min_dis = distant;
        }
    }
    return min_dis;
}

int main()
{
    int num;
    while (cin >> num && num) {
        vector<Point> graph;
        for (int n = 0; n < num; n++) {
            double a, b;
            cin >> a >> b;
            graph.push_back(Point(a, b));
        }
        sort(graph.begin(), graph.end());

        double closet = solve(graph, 0, num-1);
        if (closet >= 10000)
            cout << "INFINITY" << endl;
        else
            cout << fixed << setprecision(4) << closet << endl;
    }
}
