#include <iostream>
using namespace std;

int main(){
	double x(0);
	cout << "Entrez une valeur pour x : ";
	cin >> x;
	cout << endl;
	
	bool a(2 <= x && x < 3);
	bool b(0 < x && x <= 1);
	bool c(-10 <= x && x <= -2);
	
	if (a || b || c){
		cout << "x appartient a I" << endl;
	} else {
		cout << "x n'appartient pas a I" << endl;
	}

	return 0;
}


