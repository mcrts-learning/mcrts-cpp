#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int distance(int x, int y)
{
  return abs(x - y);
}

class Creature
{
  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/
  protected:
    string nom_;
    int niveau_;
    int points_de_vie_;
    int force_;
    int position_;
  
  public:
    Creature(string nom_, int niveau_, int points_de_vie_, int force_, int position_=0)
    : nom_(nom_), niveau_(niveau_), points_de_vie_(points_de_vie_), force_(force_), position_(position_) {}

    int position() const {return position_;}

    bool vivant() const {return bool(points_de_vie_ > 0);}
    int points_attaque() const {
      if (vivant())
        return force_ * niveau_;
      else
        return 0;
    }
    void deplacer(int pos) {
      if (vivant())
        position_ += pos;
    }
    void adieux() const {
      cout << nom_ << " n'est plus!" << endl;
    }
    void faiblir(int value) {
      if (vivant()) {
        points_de_vie_ = max(points_de_vie_ - value, 0);
        if (!vivant())
          adieux();
      }
    }
    void afficher() const {
      cout << nom_ << ", niveau: "
         << niveau_ << ", points de vie: "
         << points_de_vie_ << ", force: "
         << force_ << ", points d'attaque: "
         << points_attaque() << ", position: "
         << position() << endl;
    }
};

class Dragon: public Creature
{
  private:
    int portee_flamme_;

    int eval_distance(Creature& bete) {return distance(position(), bete.position());}
    bool a_portee(Creature& bete) {return bool(eval_distance(bete) <= portee_flamme_);}

  public:
    Dragon(string nom_, int niveau_, int points_de_vie_, int force_, int portee_flamme_, int position_=0)
    : Creature(nom_, niveau_, points_de_vie_, force_, position_), portee_flamme_(portee_flamme_) {}

    void voler(int pos) {
      if (vivant())
        position_ = pos;
    }

    void souffle_sur(Creature& bete) {
      if (vivant() and bete.vivant() and a_portee(bete)) {
        bete.faiblir(points_attaque());
        faiblir(eval_distance(bete));

        if (vivant() and !bete.vivant())
          niveau_++;
      }
    }
};

class Hydre: public Creature
{
  private:
    int longueur_cou_;
    int dose_poison_;

    int eval_distance(Creature& bete) {return distance(position(), bete.position());}
    bool a_portee(Creature& bete) {return bool(eval_distance(bete) <= longueur_cou_);}

  public:
    Hydre(string nom_, int niveau_, int points_de_vie_, int force_, int longueur_cou_, int dose_poison_, int position_=0)
    : Creature(nom_, niveau_, points_de_vie_, force_, position_), longueur_cou_(longueur_cou_), dose_poison_(dose_poison_) {}

    void empoisonne(Creature& bete) {
      if (vivant() and bete.vivant() and a_portee(bete)) {
        bete.faiblir(points_attaque() + dose_poison_);

        if (vivant() and !bete.vivant())
          niveau_++;
      }
    }
};

void combat(Dragon& dragon, Hydre& hydre) {
  hydre.empoisonne(dragon);
  dragon.souffle_sur(hydre);
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
int main()
{
  Dragon dragon("Dragon rouge"   , 2, 10, 3, 20         );
  Hydre  hydre ("Hydre maléfique", 2, 10, 1, 10, 1,  42 );

  dragon.afficher();
  cout << "se prépare au combat avec :" << endl;
  hydre.afficher();

  cout << endl;
  cout << "1er combat :" << endl;
  cout << "    les créatures ne sont pas à portée, donc ne peuvent pas s'attaquer."
       << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "Le dragon vole à proximité de l'hydre :" << endl;
  dragon.voler(hydre.position() - 1);
  dragon.afficher();

  cout << endl;
  cout << "L'hydre recule d'un pas :" << endl;
  hydre.deplacer(1);
  hydre.afficher();

  cout << endl;
  cout << "2e combat :" << endl;
  cout << "\
  + l'hydre inflige au dragon une attaque de 3 points\n\
      [ niveau (2) * force (1) + poison (1) = 3 ] ;\n\
  + le dragon inflige à l'hydre une attaque de 6 points\n\
      [ niveau (2) * force (3) = 6 ] ;\n\
  + pendant son attaque, le dragon perd 2 points de vie supplémentaires\n\
       [ correspondant à la distance entre le dragon et l'hydre : 43 - 41 = 2 ].\
" << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "Le dragon avance d'un pas :" << endl;
  dragon.deplacer(1);
  dragon.afficher();

  cout << endl;
  cout << "3e combat :" << endl;
  cout << "\
  + l'hydre inflige au dragon une attaque de 3 points\n\
      [ niveau (2) * force (1) + poison (1) = 3 ] ;\n\
  + le dragon inflige à l'hydre une attaque de 6 points\n\
      [ niveau (2) * force (3) = 6 ] ;\n\
  + pendant son attaque, le dragon perd 1 point de vie supplémentaire\n\
       [ correspondant à la distance entre le dragon et l'hydre : 43 - 42 = 1 ] ;\n\
  + l'hydre est vaincue et le dragon monte au niveau 3.\
" << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "4e Combat :" << endl;
  cout << "    quand une créature est vaincue, rien ne se passe." << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  return 0;
}
