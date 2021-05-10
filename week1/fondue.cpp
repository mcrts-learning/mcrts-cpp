#include <iostream>
using namespace std;

int main(){
	const double BASE(4);
	double fromage(800.0);
	double eau(2.0);
	double ail(2.0);
	double pain(400.0);
	
	int nb_convives(0);
	cout << "Entrez le nombre de personne(s) conviées à la fondue : ";
	cin >>  nb_convives;
	cout << endl;
	
	fromage *= nb_convives / BASE;
	eau *= nb_convives / BASE;
	ail *= nb_convives / BASE;
	pain *= nb_convives / BASE;
	
	cout << endl << "Entrez le nombre de personne(s) conviées à la fondue :" << endl;
	cout << " - " << fromage << " gr de Vacherin fribourgeois" << endl;
	cout << " - " << eau << " dl d'eau" << endl;
	cout << " - " << ail << " gousse(s) d'ail" << endl;
	cout << " - " << pain << " gr de pain" << endl;
	cout << " - du poivre à volonté" << endl;
}

