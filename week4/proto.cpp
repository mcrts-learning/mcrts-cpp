#include <iostream>
using namespace std;

int demander_nombre(int infvalue, int supvalue);

int main() {
	int a(demander_nombre(10, -1));
	cout << a <<endl;

	return 0;
}

int demander_nombre(int infvalue, int supvalue) {
    int a(0);
    bool upperbound(true);
    if (supvalue <= infvalue) {
        upperbound = false;
    }

    if (upperbound) {
        do {
            cout << "Entrez un nombre entre " << infvalue
                << " et " << supvalue << " : ";
            cin >> a;
        } while (a < infvalue or a > supvalue);
    } else {
        do {
            cout << "Entrez un nombre supérieur à " << infvalue << " : ";
            cin >> a;
        } while (a < infvalue);
    }
    
    return a;
}
