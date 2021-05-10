#include <iostream>
#include <iomanip> // pour setprecision()
using namespace std;

int main()
{
	// Réduire le format d'affichage
	cout << setprecision(4);

	// Paramètres
	double taux_croissance_lapins(0.3);
	double taux_attaque(0.01);
	double taux_croissance_renards(0.008);
	double taux_mortalite(0.1);
	int duree(50);

	double renards_i(0.0);
	double lapins_i(0.0);

	/*****************************************************
	* Compléter le code à partir d'ici
	*****************************************************/

	// ===== PARTIE 1 =====
	// Saisie des populations initiales
	double renard(0);
	do {
		cout << "Combien de renards au départ (>= 2) ? ";
		cin >> renard;
	} while (renard < 2);
	
	double lapin(0);
	do {
		cout << "Combien de lapins au départ  (>= 5) ? ";
		cin >> lapin;
	} while (lapin < 5);


	// ===== PARTIE 2 =====
	// Première simulation

	cout <<  endl << "***** Le taux d'attaque vaut "<< taux_attaque * 100 << "%" <<  endl;
	
	lapins_i = lapin;
	renards_i = renard;
	for (int i(1); i <= duree; i++) {
		double lgrowth(1.0 + taux_croissance_lapins - taux_attaque * renards_i);
		double rgrowth(1.0 + taux_attaque * lapins_i * taux_croissance_renards - taux_mortalite);
		lapins_i *= lgrowth;
		renards_i *= rgrowth;
		lapins_i = max(0.0, lapins_i);
		renards_i = max(0.0, renards_i);
		cout << "Après " << i << " mois, il y a " << lapins_i
			 << " lapins et " << renards_i << " renards" << endl;

	}

	// ===== PARTIE 3 =====
	// Variation du taux d'attaque
	
	cout << endl;
	double taux_attaque0(0.0);
	do {
		cout << "taux d'attaque au départ en % (entre 0.5 et 6) ? ";
		cin >> taux_attaque0;
	} while (taux_attaque0 < 0.5 or 6 < taux_attaque0);
	
	double taux_attaque1(0.0);
	do {
		cout << "taux d'attaque à la fin  en % (entre "<< taux_attaque0 << " et 6) ? ";
		cin >> taux_attaque1;
	} while (taux_attaque1 < taux_attaque0 or 6 < taux_attaque1);
	
	for (double taux(taux_attaque0); taux <= taux_attaque1; taux++)  {
		cout <<  endl << "***** Le taux d'attaque vaut "<< taux << "%" <<  endl;
		
		taux_attaque = taux / 100.;
		lapins_i = lapin;
		renards_i = renard;
		bool lapin_ext(false);
		bool renard_ext(false);
		for (int i(1); i <= duree; i++) {
			double lgrowth(1.0 + taux_croissance_lapins - taux_attaque * renards_i);
			double rgrowth(1.0 + taux_attaque * lapins_i * taux_croissance_renards - taux_mortalite);
			lapins_i *= lgrowth;
			renards_i *= rgrowth;
			
			
			lapins_i = max(0.0, lapins_i);
			renards_i = max(0.0, renards_i);
			
			if (!lapin_ext and lapins_i < 5) {
				lapin_ext = true;
			}
			if (!renard_ext and renards_i < 5) {
				renard_ext = true;
			}
			
			if (lapins_i < 2) {
				lapins_i = 0.0;
			}
			if (renards_i < 2) {
				renards_i = 0.0;
			}
			if (renards_i < 1 and lapins_i < 1) {
				duree = i;
			}
		}
		cout << "Après " << duree << " mois, il y a " << lapins_i
			 << " lapins et " << renards_i << " renards" << endl;
		
		if (renard_ext or lapin_ext or renards_i < 1 or lapins_i < 1) {
			if (renard_ext) {
				cout << "Les renards ont été en voie d'extinction" << endl;
				if (renards_i > 5) {
					cout << "mais la population est remontée ! Ouf !" << endl;
				} else if (renards_i < 1) {
					cout << "et les renards ont disparu :-(" << endl;
				}
			}
			if (lapin_ext) {
				cout << "Les lapins ont été en voie d'extinction" << endl;
				if (lapins_i > 5) {
					cout << "mais la population est remontée ! Ouf !" << endl;
				} else if (lapins_i < 1) {
				cout << "et les lapins ont disparu :-(" << endl;
				}
			}
			
		} else {
			cout << "Les lapins et les renards ont des populations stables." << endl;
		}
	}

	/*******************************************
	* Ne rien modifier après cette ligne.
	*******************************************/

	return 0;
}
