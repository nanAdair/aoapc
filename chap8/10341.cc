/* Title: 10341
 * 考察点：单调递减函数求根。二分求值*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const double EPS = 1e-14;

int p, q, r, s, t, u;
double F(double x);
int main()
{
    while (cin >> p >> q >> r >> s >> t >> u) {
        double m, l, r;
        l = 0;
        r = 1;
        if (F(0) * F(1) > 0) {
            cout << "No solution" << endl;
            continue;
        }

        while (abs(F(m)) >= EPS) {
            m = l + (r - l) / 2;
            if (F(m) > 0)
                l = m;
            else
                r = m;
        }
        cout << fixed << setprecision(4) << m << endl;
    }
}

double F(double x)
{
    return p*exp(-x) + q*sin(x) + r*cos(x) + s*tan(x) + t*x*x + u;
}
