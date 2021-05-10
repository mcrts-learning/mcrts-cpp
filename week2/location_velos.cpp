#include <iostream>
using namespace std;

int main()
{
  cout << "Donnez l'heure de début de la location (un entier) : ";
  int debut;
  cin >> debut;

  cout << "Donnez l'heure de fin de la location (un entier) : ";
  int fin;
  cin >> fin;

  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/
	constexpr int tarifA0(0);
	constexpr int tarifA1(7);
	constexpr int tarifB0(7);
	constexpr int tarifB1(17);
	constexpr int tarifC0(17);
	constexpr int tarifC1(24);
	
	
	if (!(debut >=0 && debut <= 24) or !(fin >=0 && fin <= 24)){
		cout << "Les heures doivent être comprises entre 0 et 24 !" << endl;
	} else if (fin == debut) {
		cout << "Bizarre, vous n'avez pas loué votre vélo bien longtemps !" << endl;
	} else if (fin < debut) {
		cout << "Bizarre, le début de la location est après la fin ..." << endl;
	} else {
		int timeA(
			max(
				0,
				min(tarifA1, fin) - max(tarifA0, debut)
			));
		int timeB(
			max(
				0,
				min(tarifB1, fin) - max(tarifB0, debut)
			));
		int timeC(
			max(
				0,
				min(tarifC1, fin) - max(tarifC0, debut)
			));
		int total(0);
		
		cout << "Vous avez loué votre vélo pendant" << endl;
		if (timeA + timeC > 0) {
			total += timeA + timeC * 1;
			cout << timeA + timeC << " heure(s) au tarif horaire de "
				 << 1     << " franc(s)" << endl;
		}
		if (timeB > 0) {
			total += timeB * 2;
			cout << timeB << " heure(s) au tarif horaire de "
				 << 2     << " franc(s)" << endl;
		}
		cout << "Le montant total à payer est de "
			 << total << " franc(s)." << endl;
	}
	

	
    
    

    



  /*******************************************
   * Ne rien modifier après cette ligne.
   *******************************************/

  return 0;
}
