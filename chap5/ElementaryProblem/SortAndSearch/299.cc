/* Title：299
 * 考察点：bubble sort implementation*/
#include <iostream>
using namespace std;

#define MAX 51
void swap(int num[], int l, int r);
int bubblesort(int num[], int n);
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int l;
        int number[MAX];
        cin >> l;
        for (int j = 0; j < l; j++)
            cin >> number[j];

        int res = bubblesort(number, l);

        cout << "Optimal train swapping takes " << res << " swaps." << endl;
    }
}

int bubblesort(int num[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (num[j] > num[j + 1]) {
                swap(num, j, j + 1);
                sum++;
            }
        }
    }
    return sum;
}

void swap(int num[], int l, int r)
{
    int temp;
    temp = num[l];
    num[l] = num[r];
    num[r] = temp;
}
