#include <iostream>
using namespace std;

/*
L'arbre de décision qui détermine l'ordre des questions est produit par
l'algorithme ID3 (iterative dichotomizer 3) suivant la matrice :

	| C1 | C2 | C3 | C4 | C5 | C6 |
Q1	| 1  | 1  | 0  | 1  | 1  | 1  |
Q2	| 0  | 1  | 1  | 0  | 1  | 1  |
Q3	| 1  | 1  | 0  | 0  | 0  | 1  |
Q4	| 1  | 1  | 0  | 1  | 0  | 0  |

L'arbre de décision obtenu est :
1. (Q3 = 1)
	2. (Q2 = 1)
		3. (Q4 = 1)
			C2
		3. (Q4 = 0)
			C6
	2. (Q2 = 0)
		C1
1. (Q3 = 0)
	2. (Q4 = 1)
		C4
	2. (Q4 = 0)
		3. (Q1 = 1)
			C5
		3. (Q1 = 0)
			C3
*/


int main()
{
	const string champ1("l'agaric jaunissant.");
	const string champ2("l'amanite tue-mouches.");
	const string champ3("le cèpe de Bordeaux.");
	const string champ4("le coprin chevelu.");
	const string champ5("la girolle.");
	const string champ6("le pied bleu.");
	const string question1("Est-ce que votre champignon a des lamelles (1 : oui, 0 : non) ? ");
	const string question2("Est-ce que votre champignon vit en forêt (1 : oui, 0 : non) ? ");
	const string question3("Est-ce que votre champignon a un chapeau convexe (1 : oui, 0 : non) ? ");
	const string question4("Est-ce que votre champignon a un anneau (1 : oui, 0 : non) ? ");
	
	cout << "Pensez à un champignon : amanite tue-mouches, pied bleu, girolle," << endl
	     << "cèpe de Bordeaux, coprin chevelu ou agaric jaunissant." << endl << endl;
	
	string champignon("");
	bool q(false);
	cout << question3;
	cin >> q;
	
	if (q) {
		cout << question2;
		cin >> q;
		if (q) {
			cout << question4;
			cin >> q;
			if (q) {
				champignon = champ2;
			} else {
				champignon = champ6;
			}
		} else {
			champignon = champ1;
		}
	} else {
		cout << question4;
		cin >> q;
		if (q) {
			champignon = champ4;
		} else {
			cout << question1;
			cin >> q;
			if (q) {
				champignon = champ5;
			} else {
				champignon = champ3;
			}
		}
	}
	cout << "==> Le champignon auquel vous pensez est " << champignon;
	return 0;
}
