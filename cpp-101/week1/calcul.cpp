#include <iostream>
using namespace std;


int main(){
	/* 
	I use instruction blocks here to scope my variables
	and avoid reuse of variable name conflict.
	*/
	{
		cout << "** Avec x et y des entiers **" << endl;
		int x(2), y(4);
		double a(x + y), b(x - y), c(x * y), d(x / y);
		
		cout << " Addition de " 		<< x << " par " << y << " = " << a << endl;
		cout << " Soustraction de " 	<< x << " par " << y << " = " << b << endl;
		cout << " Multiplication de " 	<< x << " par " << y << " = " << c << endl;
		cout << " Division de " 		<< x << " par " << y << " = " << d << endl;
		cout << endl;
	}
	{
		cout << "** Avec x et y des réels **" << endl;
		double x(2), y(4);
		double a(x + y), b(x - y), c(x * y), d(x / y);
		
		cout << " Addition de " 		<< x << " par " << y << " = " << a << endl;
		cout << " Soustraction de " 	<< x << " par " << y << " = " << b << endl;
		cout << " Multiplication de " 	<< x << " par " << y << " = " << c << endl;
		cout << " Division de " 		<< x << " par " << y << " = " << d << endl;
		cout << endl;
	}
	{
		cout << "** Avec x entier et y réel **" << endl;
		int x(2);
		double y(4);
		double a(x + y), b(x - y), c(x * y), d(x / y);
		
		cout << " Addition de " 		<< x << " par " << y << " = " << a << endl;
		cout << " Soustraction de " 	<< x << " par " << y << " = " << b << endl;
		cout << " Multiplication de " 	<< x << " par " << y << " = " << c << endl;
		cout << " Division de " 		<< x << " par " << y << " = " << d << endl;
	}
}
