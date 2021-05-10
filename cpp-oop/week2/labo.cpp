#include <iostream>
#include <string>
using namespace std;

class Souris
{
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/

  private:
    double poids;
    string couleur;
    unsigned int age;
    unsigned int esperance_vie;
    bool clonee;

    static void init() {
      cout << "Une nouvelle souris !" << endl;
    }
  
  public:
    Souris(double poids, string couleur, unsigned int age, unsigned int esperance_vie)
    : poids(poids), couleur(couleur), age(age), esperance_vie(esperance_vie), clonee(false) {
      init();
    }

    Souris(double poids, string couleur, unsigned int age)
    : poids(poids), couleur(couleur), age(age), clonee(false) {
      esperance_vie = 36;
      init();
    }
    Souris(double poids, string couleur)
    : poids(poids), couleur(couleur), clonee(false) {
      age = 0;
      esperance_vie = 36;
      init();
    }
    Souris(Souris const& s)
    : poids(s.poids), couleur(s.couleur), age(s.age), esperance_vie(s.esperance_vie*4/5), clonee(true) {
      cout << "Clonage d'une souris !" << endl;
    }
    ~Souris() {
      cout << "Fin d'une souris..." << endl;
    }

    void afficher() const {
      string s("");
      if (clonee) {
        s = ", clonee,";
      }
      cout << "Une souris " << couleur << s
           << " de " << age << " mois et pesant "
           << poids << " grammes" << endl;
    }
    void vieillir() {
      age += 1;
      if (clonee and age > esperance_vie / 2) {
        couleur = "verte";
      }
    }
    void evolue() {
      while (age < esperance_vie) {
        vieillir();
      }
    }

  /*******************************************
   * Ne rien modifier après cette ligne.
   *******************************************/

}; // fin de la classe Souris

int main()
{
  Souris s1(50.0, "blanche", 2);
  Souris s2(45.0, "grise");
  Souris s3(s2);
  // ... un tableau peut-être...
  s1.afficher();
  s2.afficher();
  s3.afficher();
  s1.evolue();
  s2.evolue();
  s3.evolue();
  s1.afficher();
  s2.afficher();
  s3.afficher();
  return 0;
}
