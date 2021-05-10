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
	
	int hf(0);
	cout << "H fin =";
	cin >> hf;
	
	int n(0);
	double v(sqrt(2 * g * h));
	do {
		n++;
		v *= eps;
		h = pow(v, 2)/(2 * g);
	} while (h > hf);
	cout << "Nombre =" << n;
	return 0;
}
