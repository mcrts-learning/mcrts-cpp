#include <iostream>
using namespace std;

int main(){
	int age(0);
	cout << "Quel est votre age ? ";
	cin >> age;
	cout << endl;
	
	const int year(2021);
	cout << "Vous etes né en " << year - age << "."<< endl;
}
