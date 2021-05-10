#include <iostream>
using namespace std;

void function(int a){
	cout << "var a dans function : " << a
		 << " | adr : " << &a << endl;
	a = 10;
}

int main() {
	int a(0);
	
	cout << "var a dans main : " << a
		 << " | adr : " << &a << endl;
	
	function(a);
	
	cout << "var a dans main : " << a
		 << " | adr : " << &a << endl;
		 
	true = false;
	cout << true;
	return 0;
}


