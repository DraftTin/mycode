#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void test(int* c) {
    c = new int(3);
    c[0] = 5;
    c[1] = 5;
    c[2] = 5;
    cout << c[0] << endl;
}

int main() {
    int* a = new int(3);
    a[0] = 1;
    a[1] = 1;
    a[2] = 1;
    test(a);
    cout << a[0] << endl;
    return 0;
}