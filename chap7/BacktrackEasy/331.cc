/* Title: 331
 * 考察点：先用bubble_sort自己跑一边得出需要的最小交换次数
 * 注意此题之所以会有多种不同的swap maps就是因为每次可以选择的交换对不同
 * 所以就实际模拟每次可能选择的交换对即可*/
#include <iostream>
#include <vector>
using namespace std;

vector<int> test_case;
int bubble_sort(vector<int> test_case);
void swap_vec(vector<int> &vec, int i, int j);
void find_swaps(int min_swap, int cur_swap);
bool is_sort();
int res;
int main()
{
    int n = 1;
    int num;
    while (cin >> num && num) {
        test_case.clear();
        for (int i = 0; i < num; i++) {
            int temp;
            cin >> temp;
            test_case.push_back(temp);
        }

        vector<int> init = test_case;
        res = 0;
        if (is_sort()) {
            cout << "There are " << res << " swap maps for input data set " << n << "." << endl;
            n++;
            continue;
        }
        int min_swap = bubble_sort(init);
        find_swaps(min_swap, 0);
        cout << "There are " << res << " swap maps for input data set " << n << "." << endl;
        n++;
    }
}

bool is_sort()
{
    for (int i = 0; i < test_case.size()-1; i++)
        if (test_case[i] > test_case[i+1])
            return 0;
    return 1;
}

void find_swaps(int min_swap, int cur_swap)
{
    if (cur_swap == min_swap) {
        if (is_sort())
            res++;
        return;
    }
    for (int i = 0; i < test_case.size()-1; i++) {
        if (test_case[i] > test_case[i+1]) {
            swap_vec(test_case, i, i+1);
            find_swaps(min_swap, cur_swap+1);
            swap_vec(test_case, i, i+1);
        }
    }
}

int bubble_sort(vector<int> test_case)
{
    int swaps = 0;
    for (int i = 0; i < test_case.size(); i++) {
        for (int j = 0; j < test_case.size()-i-1; j++) {
            if (test_case[j] > test_case[j+1]) {
                swaps++;
                swap_vec(test_case, j, j+1);
            }
        }
    }
    return swaps;
}

void swap_vec(vector<int> &vec, int i, int j)
{
    int temp = vec[i];
    vec[i] = vec[j];
    vec[j] = temp;
}
