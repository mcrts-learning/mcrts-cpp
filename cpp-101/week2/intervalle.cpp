#include <iostream>
using namespace std;

int main(){
	double x(0);
	cout << "Entrez une valeur pour x : ";
	cin >> x;
	cout << endl;
	
	if (-1. <= x && x < 1.){
		cout << "x appartient a I" << endl;
	} else {
		cout << "x n'appartient pas a I" << endl;
	}
}

