#include <cmath>
#include <iostream>
using namespace std;

int main() {
	constexpr double g(9.81);
	
	double h(0);
	cout << "H0 =";
	cin >> h;
	
	double eps(0);
	cout << "eps =";
	cin >> eps;
	
	int n(0);
	cout << "nbr =";
	cin >> n;
	
	double v(sqrt(2 * g * h));
	for (int i(0); i < n; i++) {
		v *= eps;
	}
	h = pow(v, 2)/(2 * g);
	cout << "Hauteur =" << h;
	return 0;
}
