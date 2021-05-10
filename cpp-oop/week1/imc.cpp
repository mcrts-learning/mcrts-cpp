#include <iostream>
using namespace std;

/*****************************************************
 * Compléter le code à partir d'ici
 *****************************************************/
class Patient {
  private:
    double poids_;
    double taille_;
  
  public:
    void init(double poids, double taille);
    void afficher();
    double imc();
    double poids();
    double taille();
};

void Patient::init(double p, double t) {
  if (p <= 0 or t <= 0) {
    p = 0;
    t = 0;
  }
  poids_ = p;
  taille_ = t;
}
double Patient::poids() {
  return poids_;
}
double Patient::taille() {
  return taille_;
}
double Patient::imc() {
  if (taille_ == 0) {
    return 0;
  } else {
    return poids_ / (taille_ * taille_);
  }
}
void Patient::afficher() {
  cout << "Patient : " << poids_ << " kg pour "<< taille_ << " m" << endl;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  Patient quidam;
  double poids, taille;
  do {
    cout << "Entrez un poids (kg) et une taille (m) : ";
    cin >> poids >> taille;
    quidam.init(poids, taille);
    quidam.afficher();
    cout << "IMC : " << quidam.imc() << endl;
  } while (poids * taille != 0.0);
  return 0;
}
