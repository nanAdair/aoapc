/* Title: 10420
 * 考察点：qsort在手，排序题目无忧*/
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
using namespace std;

#define MAX 2001
int cmp(const void *p1, const void *p2);
int main()
{
    string country[MAX];
    int n;
    cin >> n;
    string temp;
    getline(cin, temp);

    for (int i = 0; i < n; i++) {
        getline(cin, temp);
        stringstream ss(temp);
        ss >> country[i];
    }

    qsort(country, n, sizeof(string), cmp);

    int num = 1;
    for (int i = 1; i < n; i++) {
        if (!strcmp(country[i].c_str(), country[i - 1].c_str()))
            num++;
        else {
            cout << country[i-1] << " " << num << endl;
            num = 1;
        }
    }

    cout << country[n - 1] << " " << num << endl;
}

int cmp(const void *p1, const void *p2)
{
    return strcmp(*(char **)p1, *(char **)p2);
}
