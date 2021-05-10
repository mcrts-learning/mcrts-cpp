#include <iostream>
using namespace std;

int fibonnaci(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fibonnaci(n-2) + fibonnaci(n-1);
    }
}

int main() {
    double n0(0);
    cout << "fibonnaci " << n0 << " = " << fibonnaci(n0) << endl;
    double n1(1);
    cout << "fibonnaci " << n1 << " = " << fibonnaci(n1) << endl;
    double n2(7);
    cout << "fibonnaci " << n2 << " = " << fibonnaci(n2) << endl;
}
