#include <iostream>
using namespace std;

int main()
{
  int debut(0);
  do {
    cout << "de (>= 1) ? ";
    cin >> debut;
  } while (debut < 1);

  int fin(0);
  do {
    cout << "a (>= " << debut << ") ? ";
    cin >> fin;
  } while (fin < debut);

  /*******************************************
   * Completez le programme a partir d'ici.
   *******************************************/
	for (int i(debut); i <= fin; i++) {
		int k(0);
		int value(i);
		do {
			k++;
			if (value % 3 == 0) {
				value += 4;
			} else if (value % 4 == 0) {
				value /= 2;
			} else {
				value--;
			}
		} while (value > 0);
		cout << i << " -> " << k << endl;
	}

  /*******************************************
   * Ne rien modifier apres cette ligne.
   *******************************************/

  return 0;
}
