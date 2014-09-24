/* Title: 10474
 * 考察点：qsort解决问题*/
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

#define MAX 10001
int cmp(const void *a, const void *b);
void process(int marble[], int index[], int n);
int main()
{
    int n, q, num;
    num = 1;
    while (cin >> n >> q && n != 0 && q != 0) {
        int marble[MAX], index[MAX];
        for (int i = 0; i < n; i++)
            cin >> marble[i];
        process(marble, index, n);

        cout << "CASE# " << num << ":" << endl;
        for (int i = 0; i < q; i++) {
            int number;
            cin >> number;
            if (index[number])
                cout << number << " found at " << index[number] << endl;
            else
                cout << number << " not found" << endl;
        }
        num++;
    }
}

void process(int marble[], int index[], int n)
{
    qsort(marble, n, sizeof(int), cmp);
    memset(index, 0, MAX * sizeof(int));
    index[marble[0]] = 1;
    for (int i = 1; i < n; i++) {
        if (marble[i - 1] != marble[i]) {
            index[marble[i]] = i + 1;
        }
    }
}

int cmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
