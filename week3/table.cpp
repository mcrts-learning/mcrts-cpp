#include <iostream>
using namespace std;

int main() {
	
	cout << "Tables de multiplication" << endl << endl;
	for (int table(2); table <= 10; table++) {
		cout << "Table de " << table << " :" << endl;
		for (int x(1); x <= 10; x++) {
			cout << "  " << x << " * " << table << " = " << x * table << endl;
		}
	}
}
