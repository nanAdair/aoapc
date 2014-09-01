/* Title: 10878
 * 考察点：
 * 转码，开1000个string会报runtime error*/
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string input;
    int factor[] = {0, 0, 64, 32, 16, 8, 0, 4, 2, 1, 0};
    while (getline(cin, input)) {
        if (input[0] == '_')
            continue;
        int c = 0;
        for (int j = 0; j < input.length(); j++) {
            if (input[j] == 'o')
                c += factor[j];
        }
        cout << char(c);
    }
}
