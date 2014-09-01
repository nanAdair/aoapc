/* Title: 644
 * 考察点：
 * 字符串比较，找字串，find搞掂*/
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string code[10], temp;

    int index, flag, num;
    num = index = flag = 0;
    while (getline(cin, temp)) {
        if (temp != "9")
            code[index++] = temp;
        else {
            for (int i = 0; i < index; i++) {
                for (int j = 0; j < index; j++) {
                    if (code[i].find(code[j]) == 0 && i != j) {
                        flag = 1;
                        break;
                    }
                    if (flag)
                        break;
                }
            }

            if (flag)
                cout << "Set " << num + 1 << " is not immediately decodable" << endl;
            else 
                cout << "Set " << num + 1 << " is immediately decodable" << endl;

            for (int i = 0; i < index; i++)
                code[i].erase(code[i].begin(), code[i].end());
            num++;
            flag = 0;
            index = 0;
        }
    }
}
