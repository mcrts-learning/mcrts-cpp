#include <iostream>
using namespace std;

/*******************************************
 * Complétez le programme à partir d'ici.
 *******************************************/
class Tirelire {
  private:
    double montant;

  public:
    double getMontant();
    void afficher();
    void secouer();
    void remplir(double montant);
    void vider();
    void puiser(double montant);
    bool montant_suffisant(double budget, double& solde);
    double calculerSolde(double budget);
};

double Tirelire::getMontant() {
  return montant;
}
void Tirelire::afficher() {
  if (montant > 0) {
    cout << "Vous avez : " << montant << " euros dans votre tirelire." << endl;

  } else {
    cout << "Vous etes sans le sou." << endl;
  }
}
void Tirelire::secouer() {
  if (montant > 0) {
    cout << "Bing bing" << endl;
  }
}
void Tirelire::remplir(double m) {
  if (m > 0) {
    montant += m;
  }
}
void Tirelire::vider() {
  montant = 0;
}
void Tirelire::puiser(double m) {
  if (m > 0) {
    if (montant < m) {
      vider();
    } else {
      montant -= m;
    }
  }
}
bool Tirelire::montant_suffisant(double budget, double& solde) {
  double newsolde(calculerSolde(budget));
  if (newsolde >= 0) {
    solde = newsolde;
    return true;
  } else {
    solde = -1 * newsolde;
    return false;
  }
}
double Tirelire::calculerSolde(double budget) {
  if (budget < 0) {
    return montant;
  } else {
    return montant - budget;
  }
}
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  Tirelire piggy;

  piggy.vider();
  piggy.secouer();
  piggy.afficher();

  piggy.puiser(20.0);
  piggy.secouer();
  piggy.afficher();

  piggy.remplir(550.0);
  piggy.secouer();
  piggy.afficher();

  piggy.puiser(10.0);
  piggy.puiser(5.0);
  piggy.afficher();

  cout << endl;

  // le budget de vos vacances de rève.
  double budget;

  cout << "Donnez le budget de vos vacances : ";
  cin >> budget;

  // ce qui resterait dans la tirelire après les
  // vacances
  double solde(0.0);

  if (piggy.montant_suffisant(budget, solde)) {
    cout << "Vous êtes assez riche pour partir en vacances !"
         << endl
         << "Il vous restera " << solde << " euros"
         << " à la rentrée." << endl << endl;
    piggy.puiser(budget);
  } else {
    cout << "Il vous manque " << solde << " euros"
         << " pour partir en vacances !" << endl << endl;
  }
  return 0;
}
