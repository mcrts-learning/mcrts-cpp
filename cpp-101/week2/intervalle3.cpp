#include <iostream>
#include <math.h>
using namespace std;


int main(){
	double x(0);
	cout << "Entrez une valeur pour x : ";
	cin >> x;
	cout << endl;
	
	bool domain_expr1(x != 0);
	bool domain_expr2(x != 1 && x > 0);
	
	double root(pow(x, 2) - 8*x);
	bool domain_expr3(x != 2 && root >= 0);
	
	
	bool domain_sin((sin(x) - x/20.) >= 0);
	double numerator(pow(x, 3) - 1);
	bool domain_log(
		x != 0
		&& numerator != 0
		&& numerator > 1
	);
	bool domain_expr4(domain_sin && domain_log);
	
	if (domain_expr1){
		double res(x / (1 - exp(x)));
		cout << "Expression 1 = " << res << endl;
	} else {
		cout << "Expression 1 : indefinie" << endl;
	}
	if (domain_expr2){
		double res(x * log(x) * exp(2 /(x - 1)));
		cout << "Expression 2 = " << res << endl;
	} else {
		cout << "Expression 2 : indefinie" << endl;
	}
	if (domain_expr3){
		double res((-x - sqrt(pow(x, 2) - 8 * x))/(2-x));
		cout << "Expression 3 = " << res << endl;
	} else {
		cout << "Expression 3 : indefinie" << endl;
	}
	if (domain_expr4){
		double res(sqrt( (sin(x) - x/20) * log(pow(x, 2) -1/x)));
		cout << "Expression 4 = " << res << endl;
	} else {
		cout << "Expression 4 : indefinie" << endl;
	}

	return 0;
}


