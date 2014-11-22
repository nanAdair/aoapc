/* Title: 10012
 * 考察点：全排列 每个排列的距离计算*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

double min_size;
vector<double> radius;

double cal();
bool next_per();
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        double last;
        int m;
        cin >> m;

        radius.clear();
        for (int j = 0; j < m; j++) {
            double temp;
            cin >> temp;
            radius.push_back(temp);
        }
        sort(radius.begin(), radius.end());

        min_size = 1000000000;
        do {
            double sum = cal();
            if (sum < min_size)
                min_size = sum;
        } while (next_per());
        cout << fixed << setprecision(3) << min_size << endl;
    }
}

double dis(double a, double b)
{
    return sqrt(pow(a+b, 2) - pow(a-b, 2));
}

double disPoint(double x, double y)
{
    return sqrt(pow(x, 2) + pow(y, 2));
}

// 注意这里圆的距离的计算方法，有可能是一个大圆多个小圆
double cal()
{
    double x[10], y[10];
    double res = 0;
    for (int i = 0; i < radius.size(); i++) {
        y[i] = radius[i];
        if (i == 0)
            x[i] = radius[i];
        else
            x[i] = x[i-1] + dis(radius[i-1], radius[i]);
        if (x[i] < radius[i])
            x[i] = radius[i];
        for (int j = 0; j < i; j++) {
            if (radius[j] + radius[i] > disPoint(x[i] - x[j], y[i] - y[j]))
                x[i] = x[j] + dis(radius[j], radius[i]);
        }
        if (res < x[i] + radius[i])
            res = x[i] + radius[i];
    }
    // Wrong Answer Here
    //for (int i = 0; i < radius.size()-1; i++) 
        //res += dis(radius[i], radius[i+1]);
    //res = res + (radius[0] + radius[radius.size()-1]);

    return res;
}

void swap_vec(int i, int j)
{
    double temp = radius[i];
    radius[i] = radius[j];
    radius[j] = temp;
}

bool next_per()
{
    int i = radius.size()-1;
    while (i > 0 && radius[i-1] >= radius[i])
        i--;
    if (i == 0)
        return 0;
    double min_i = 1000000000;
    int index;
    for (int j = i; j < radius.size(); j++) {
        if (min_i > radius[j] && radius[j] > radius[i-1]) {
            min_i = radius[j];
            index = j;
        }
    }
    swap_vec(i-1, index);
    sort(radius.begin()+i, radius.end());

    return 1;
}
