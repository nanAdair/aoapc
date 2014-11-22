/* Title: 167
 * 考察点：标准的八皇后问题*/
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

bool visited[3][15];
int test_case[20][8][8];
int maxres[20];
int Curr[8];
int n;

void search(int cur);
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 8; k++)
                cin >> test_case[i][j][k];
        }
    }

    memset(maxres, 0, sizeof(maxres));
    search(0);

    for (int i = 0; i < n; i++)
        cout << setw(5) << maxres[i] << endl;
}

// 按行放置
void search(int cur)
{
    if (cur == 8) {
        for (int i = 0; i < n; i++) {
            int temp = 0;
            for (int j = 0; j < 8; j++) 
                temp += test_case[i][j][Curr[j]];
            if (temp > maxres[i])
                maxres[i] = temp;
        }
        return;
    }

    for (int j = 0; j < 8; j++) {
        if (!visited[0][j] && !visited[1][j-cur+7] && !visited[2][cur+j]) {
            Curr[cur] = j;
            visited[0][j] = visited[1][j-cur+7] = visited[2][cur+j] = 1;
            search(cur+1);
            visited[0][j] = visited[1][j-cur+7] = visited[2][cur+j] = 0;
        }
    }

}
