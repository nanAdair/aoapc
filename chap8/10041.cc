/* Title: 10041
 * 考察点：二分，左减右增函数，求极小值
 * 从单调性来判断当前点是在左边还是右边，然后二分求值*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX 0x7fffffff

int cal(const vector<int> &vec, int pos)
{
    int res = 0;
    for (int i = 0; i < vec.size(); i++)
        res += abs(pos - vec[i]);
    return res;
}

int main()
{
    int num;
    cin >> num;
    for (int n = 0; n < num; n++) {
        int r;
        cin >> r;
        vector<int> street;
        for (int i = 0; i < r; i++) {
            int tmp;
            cin >> tmp;
            street.push_back(tmp);
        }
        if (r == 1) {
            cout << 0 << endl;
            continue;
        }
        sort(street.begin(), street.end());
        int left, right, mid;
        left = street[0];
        right = street[r-1];
        while (1) {
            mid = (left + right) / 2;
            int length_mid = cal(street, mid);
            int length_left, length_right;
            int i = 1;
            while (1) {
                length_left = cal(street, mid-i);
                if (length_left != length_mid)
                    break;
                i++;
                if ((mid - i) < street[0])
                    break;
            }
            i = 1;
            while (1) {
                length_right = cal(street, mid+i);
                if (length_right != length_mid)
                    break;
                i++;
                if ((mid + i) > street[r-1])
                    break;
            }
            if (length_left <= length_mid && length_mid < length_right)
                right = mid;
            else if (length_left > length_mid && length_mid >= length_right)
                left = mid;
            else
                break;
        }

        cout << cal(street, mid) << endl;
    }
}
