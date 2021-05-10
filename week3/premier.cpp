#include <cmath>
#include <iostream>
using namespace std;

int main() {
	int n(0);
	cout << "n :";
	cin >> n;
	
	double root(sqrt(n));
	
	if (n % 2 == 0) {
		cout << n << " n'est pas premier, car il est divisible par 2" << endl;
	} else {
		int i(3);
		do {
			if (n % i == 0) {
				cout << n << " n'est pas premier, car il est divisible par " << i  << endl;
				return 0;
			}
			i += 2;
		} while (i < root);
		cout << n << " est premier." << endl;
	}
	return 0;
}
