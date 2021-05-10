#include <iostream>
#include <cmath>
using namespace std;

double factorielle(int k) {
    double res(1);
    for (int i(1); i <= k; i++) {
        res *= i;
    }
    return res;
}
double somme_partielle(double x, int N) {
    double res(0);
    for (int i(0); i < N; i++) {
        res += pow(-1, i)*pow(x, 2*i)/factorielle(2*i);
    }
    return res;
}

int main() {
    double x(3.1415/2);
    cout << "cos " << x << " = " << somme_partielle(x, 50) << endl;
}
