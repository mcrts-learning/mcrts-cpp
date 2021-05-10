#include <iostream>
#include <vector>
using namespace std;

double scalaire(vector<double> u, vector<double> v){
    double result(0);
    for (size_t i(0); i < u.size(); i++) {
        result += u[i] * v[i];
    }
    return result;
}

int main() {
    vector<double> u;
    vector<double> v;
    u = {5, 3, -1};
    v = {2, 1, 2};
    cout << scalaire(u, v) << endl;
    return 0;
}