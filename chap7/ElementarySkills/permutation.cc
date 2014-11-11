#include <iostream>
using namespace std;

#define MAX 10

bool visited[MAX];
int num = 1;
void permutation(int n, int A[], int curr);
int main()
{
    int n;
    cin >> n;

    int A[MAX];
    permutation(n, A, 0);
}

void permutation(int n, int A[], int curr)
{
    if (curr == n) {
        cout << num++ << ": ";
        for (int i = 0; i < n; i++)
            cout << A[i];
        cout << endl;
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            A[curr] = i;
            visited[i] = 1;
            permutation(n, A, curr+1);
            visited[i] = 0;
        }
    }
}
