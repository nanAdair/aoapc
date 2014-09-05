#include <iostream>
#include <cstring>
#include <string>
using namespace std;

#define MAX 10001
class BigNumber
{
public:
    friend bool operator<(const BigNumber &lhs, const BigNumber &rhs);
    friend bool operator==(const BigNumber &lhs, const BigNumber &rhs);
    BigNumber():
        number(""), length(0) {}
    BigNumber(string &s);
    BigNumber(const string &s);

    void operator+=(const BigNumber&);
    void operator*=(const BigNumber&);
    void operator-=(const BigNumber&);
    BigNumber operator/=(const BigNumber&);
    void operator%=(const BigNumber&);

    string revert() const;

private:
    string number;
    int length;
};

ostream &operator<<(ostream &os, const BigNumber &);
BigNumber operator+(const BigNumber &lhs, const BigNumber &rhs);
BigNumber operator*(const BigNumber &lhs, const BigNumber &rhs);
BigNumber operator/(const BigNumber &lhs, const BigNumber &rhs);
BigNumber operator%(const BigNumber &lhs, const BigNumber &rhs);

BigNumber::BigNumber(string &s):
    number(s.length(), ' '), length(s.length())
{
    for (int i = 0; i < length; i++)
        number[i] = s[length - i - 1];
}

BigNumber::BigNumber(const string &s):
    length(s.length())
{
    for (int i = 0; i < length; i++)
        number.push_back(s[length - i - 1]);
}

void BigNumber::operator+=(const BigNumber &b)
{
    char temp[MAX];

    int c, i;
    c = 0;
    for (i = 0; i < b.length && i < length; i++) {
        int sum = number[i] - '0' + b.number[i] - '0' + c;
        temp[i] = sum % 10 + '0';
        c = sum / 10;
    }

    if (i < b.length) {
        while (i < b.length) {
            int sum = b.number[i] - '0' + c;
            temp[i] = sum % 10 + '0';
            c = sum / 10;
            i++;
        }
    }
    else if (i < length) {
        while (i < length) {
            int sum = number[i] - '0' + c;
            temp[i] = sum % 10 + '0';
            c = sum / 10;
            i++;
        }
    }
    if (c == 1)
        temp[i++] = '1';
    temp[i] = '\0';

    number = temp;
    length = i;
}

void BigNumber::operator*=(const BigNumber &b)
{
    char temp[MAX];
    BigNumber factor("0");

    if (number == "0" || b.number == "0") {
        this->number = "0";
        this->length = 1;
        return;
    }

    for (int i = 0; i < b.length; i++) {
        int j;
        for (j = 0; j < i; j++)
            temp[j] = '0';
        int c = 0;
        for (int k = 0; k < length; k++) {
            int sum = (number[k] - '0') * (b.number[i] - '0') + c;
            temp[j++] = sum % 10 + '0';
            c = sum / 10;
        }
        if (c)
            temp[j++] = c + '0';
        temp[j] = '\0';


        string res(j, ' ');
        for (int k = 0; k < j; k++)
            res[k] = temp[j - k - 1];
        BigNumber one(res);

        factor += one;
    }

    *this = factor;
}

/* assume that b <= *this */
void BigNumber::operator-=(const BigNumber &b)
{
    char temp[MAX];
    int i, c;
    c = 0;
    for (i = 0; i < b.length; i++) {
        int res = (number[i] - '0') - (b.number[i] - '0') - c;
        if (res < 0) {
            temp[i] = res + 10 + '0';
            c = 1;
        }
        else {
            temp[i] = res + '0';
            c = 0;
        }
    }
    while (i < length) {
        int res = number[i] - '0' - c;
        if (res < 0) {
            temp[i] = res + 10 + '0';
            c = 1;
        }
        else {
            temp[i] = res + '0';
            c = 0;
        }
        i++;
    }
    temp[i] = '\0';
    
    number = temp;
    int j = number.length() - 1;
    while (number[j] == '0' && j >= 0)
        j--;
    number.erase(j + 1);
    if (number.empty())
        number = "0";
    length = number.length();
}

BigNumber BigNumber::operator/=(const BigNumber &b)
{
    if (*this < b) {
        BigNumber return_value = *this;
        *this = BigNumber("0");
        return return_value;
    }

    int i = length - 1;
    string res, temp;
    BigNumber remainder("0");
    while (i >= 0) {
        temp = number[i];
        BigNumber dividend = remainder * BigNumber("10") + BigNumber(temp);
        while (dividend < b && i > 0) {
            temp = number[--i];
            if (!res.empty())
                res.push_back('0');
            dividend = dividend * BigNumber("10") + BigNumber(temp);
        }

        remainder = dividend;
        int quotient = 0;
        while (b < remainder || b == remainder) {
            remainder -= b;
            quotient++;
        }

        res.push_back(quotient + '0');
        i--;
    }

    *this = BigNumber(res);
    return remainder;
}

void BigNumber::operator%=(const BigNumber &b)
{
    *this = (*this /= b);
}

string BigNumber::revert() const
{
    string temp(length, ' ');
    for (int i = 0; i < length; i++)
        temp[i] = number[length - i - 1];

    return temp;
}

ostream &operator<<(ostream &os, const BigNumber &n)
{
    os << n.revert();
    return os;
}

BigNumber operator+(const BigNumber &lhs, const BigNumber &rhs)
{
    BigNumber sum = lhs;
    sum += rhs;
    return sum;
}

BigNumber operator*(const BigNumber &lhs, const BigNumber &rhs)
{
    BigNumber product = lhs;
    product *= rhs;
    return product;
}

BigNumber operator-(const BigNumber &lhs, const BigNumber &rhs)
{
    BigNumber difference = lhs;
    difference -= rhs;
    return difference;
}

BigNumber operator/(const BigNumber &lhs, const BigNumber &rhs)
{
    BigNumber quotient = lhs;
    quotient /= rhs;
    return quotient;
}

BigNumber operator%(const BigNumber &lhs, const BigNumber &rhs)
{
    BigNumber remainder = lhs;
    remainder %= rhs;
    return remainder;
}

bool operator<(const BigNumber &lhs, const BigNumber &rhs)
{
    if (lhs.length > rhs.length)
        return 0;
    if (lhs.length < rhs.length)
        return 1;
    if (strcmp(lhs.revert().c_str(), rhs.revert().c_str()) < 0)
        return 1;
    return 0;
}

bool operator==(const BigNumber &lhs, const BigNumber &rhs)
{
    if (lhs.length != rhs.length)
        return 0;
    if (!strcmp(lhs.revert().c_str(), rhs.revert().c_str()))
        return 1;
    return 0;
}

bool operator!=(const BigNumber &lhs, const BigNumber &rhs)
{
    return !(lhs == rhs);
}

void testAdd()
{
    string s, t;
    t = "0";
    BigNumber sum(t);

    while (cin >> s) {
        if (s == "0")
            break;
        BigNumber temp(s);
        sum += temp;
    }

    cout << sum << endl;
}

void testProduct()
{
    string s, t;
    while (cin >> s >> t) {
        BigNumber b1(s);
        BigNumber b2(t);

        cout << b1 * b2 << endl;
    }
}

void testMinus()
{
    string s, t;
    while (cin >> s >> t) {
        BigNumber b1(s);
        BigNumber b2(t);

        cout << b1 - b2 << endl;
    }
}

void testDivide()
{
    string s, t;
    while (cin >> s >> t) {
        BigNumber b1(s);
        BigNumber b2(t);

        cout << b1 / b2 << endl;
    }
}

void testMod()
{
    string s, t;
    while (cin >> s >> t) {
        BigNumber b1(s);
        BigNumber b2(t);

        cout << b1 % b2 << endl;
    }
}

void testCmp()
{
    string s, t;
    while (cin >> s >> t) {
        BigNumber b1(s);
        BigNumber b2(t);

        if (b1 < b2)
            cout << "b1 < b2" << endl;
        if (b1 == b2)
            cout << "b1 == b2" << endl;
        if (b1 != b2)
            cout << "b1 != b2" << endl;
    }
}

bool is_big(BigNumber &b)
{
    string s = b.revert();
    string limit = "2147483647";

    if (s.length() > 10)
        return 1;
    else if (s.length() < 10)
        return 0;
    else {
        for (int i = 0; i < 10; i++) {
            if (s[i] > limit[i])
                return 1;
            else if (s[i] < limit[i])
                return 0;
        }
        return 0;
    }
}

string stripHeadZero(string &s)
{
    int i = 0;
    while (s[i] == '0' && i < s.length())
        i++;

    if (i == s.length())
        return "0";
    string res(s.begin() + i, s.end());
    return res;
}

/* Remember to remove the head zero
 * And don't remove the only "0"*/
void prob465()
{
    string v1, v2, op;
    while (cin >> v1 >> op >> v2) {
        cout << v1 << " " << op << " " << v2 << endl;
        if (v1 != "0")
            v1 = stripHeadZero(v1);
        if (v2 != "0")
            v2 = stripHeadZero(v2);
        BigNumber s(v1);
        BigNumber t(v2);

        BigNumber res;
        if (op == "+")
            res = s + t;
        if (op == "*")
            res = s * t;


        if (is_big(s))
            cout << "first number too big" << endl;
        if (is_big(t))
            cout << "second number too big" << endl;
        if (is_big(res))
            cout << "result too big" << endl;
    }
}

/* find how many number after the point 
 * erase the back 0 at the same time*/
int stripPointAndBackZero(string &s)
{
    int i = 0;
    while (s[i] != '.' && i < s.length())
        i++;

    if (i < s.length()) {
        int j = s.length() - 1;
        while (s[j] == '0')
            j--;

        s.erase(j + 1);
        s.erase(i, 1);
    }

    return s.length() - i;
}

void printRes(string &s, int pos)
{
    int length = s.length();
    if (length == pos)
        cout << "." << s << endl;
    else if (length > pos) {
        for (int i = 0; i < length; i++) {
            if (i == length - pos)
                cout << ".";
            cout << s[i];
        }
        cout << endl;
    }
    else {
        cout << ".";
        for (int i = 0; i < pos - length; i++)
            cout << "0";
        for (int i = 0; i < length; i++)
            cout << s[i];
        cout << endl;
    }
}
void prob748()
{
    string fp;
    int mi;
    while (cin >> fp >> mi) {
        int pos = stripPointAndBackZero(fp);
        fp = stripHeadZero(fp);
        BigNumber res(fp);
        BigNumber factor(fp);

        for (int i = 1; i < mi; i++)
            res = res * factor;

        pos *= mi;

        string integer = res.revert();
        printRes(integer, pos);
    }
}

void prob10494()
{
    string s, t, op;
    while (cin >> s >> op >> t) {
        if (s != "0")
            s = stripHeadZero(s);
        if (t != "0")
            t = stripHeadZero(t);
        if (op == "%")
            cout << s % t << endl;
        else
            cout << s / t << endl;
    }

}
int main()
{
    //testAdd();
    //testProduct();
    //prob465();
    //prob748();
    //testMinus();
    //testCmp();
    //testDivide();
    //testMod();
    prob10494();
}
