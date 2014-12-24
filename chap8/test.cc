#include <iostream>
#include <string>
using namespace std;

int main()
{
    string hello = "helllllll";
    cout << string(hello.begin(), hello.begin()) << endl;
    cout << string(hello.begin(), hello.begin()+1) << endl;
}
