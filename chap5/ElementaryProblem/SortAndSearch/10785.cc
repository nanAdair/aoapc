/* Title: 10785
 * 考察点：无*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool is_vowel(int a);
int main()
{
    int index[3][9];
    for (int i = 0; i < 9; i++) {
        index[0][i] = i;
        index[1][i] = i + 9;
        index[2][i] = i + 9 * 2;
    }
    int vowel[5] = {'A' - 'A', 'U' - 'A', 'E' - 'A', 'O' - 'A', 'I' - 'A'};
    int constant[21];
    int j = 0;
    while (j < 21) {
        for (int p = 0; p < 9; p++) {
            for (int q = 0; q < 3; q++) {
                if (!is_vowel(index[q][p]) && j < 21)
                    constant[j++] = index[q][p];
            }
        }
    }

    int number;
    cin >> number;

    for (int i = 0; i < number; i++) {
        int count[26] = {0};
        vector<char> even;
        vector<char> odd;
        int input;
        cin >> input;

        int indexc, indexv;
        indexc = indexv = 0;
        for (int k = 1; k <= input; k++) {
            if (k % 2 == 1) {
                if (count[vowel[indexv]] < 21) {
                    count[vowel[indexv]] += 1;
                    odd.push_back(vowel[indexv] + 'A');
                }
                else {
                    indexv += 1;
                    count[vowel[indexv]] += 1;
                    odd.push_back(vowel[indexv] + 'A');
                }
            }
            else {
                if (count[constant[indexc]] < 5) {
                    count[constant[indexc]] += 1;
                    even.push_back(constant[indexc] + 'A');
                }
                else {
                    indexc += 1;
                    count[constant[indexc]] += 1;
                    even.push_back(constant[indexc] + 'A');
                }
            }
        }
        sort(even.begin(), even.end());
        sort(odd.begin(), odd.end());

        cout << "Case " << i + 1 << ": ";
        for (int k = 0; k < input; k++) {
            if (k % 2 == 0)
                cout << odd[k >> 1];
            else
                cout << even[k >> 1];
        }
        cout << endl;
    }
}

bool is_vowel(int a)
{
    char b = 'A' + a;
    if (b == 'A' || b == 'E' || b == 'I' || b == 'O' || b == 'U')
        return 1;
    return 0;
}
