#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Pour simplifier
typedef string Forme   ;
typedef string Couleur ;

class Brique
{
private:
  Forme   forme   ;
  Couleur couleur ;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/

  Brique(Forme forme, Couleur couleur)
  : forme(forme), couleur(couleur) {}

  ostream& afficher(ostream& sortie) const {
    if (couleur != "")
      sortie << "(" << forme << ", " << couleur << ")";
    else
      sortie <<  forme;
    return sortie;
  }
};
ostream& operator<<(ostream& sortie, Brique const& brique) {
  brique.afficher(sortie);
  return sortie;
}

class Construction
{
  friend class Grader;

  private:
    vector<vector<vector<Brique>>> contenu;

  public:
    Construction(Brique brique)
    : contenu(vector<vector<vector<Brique>>>({{{brique}}})) {}

    size_t hauteur() const {
      return contenu.size();
    }
    size_t profondeur() const {
      if (hauteur() == 0)
        return 0;
      else
        return contenu[0].size();
    }

    ostream& afficher(ostream& sortie) const {
      for(int i(hauteur() - 1); i >= 0; i--) {
        sortie << "Couche " << i << " :" << endl;
        for(int j(contenu[i].size() - 1); j >= 0; j--) {
          for(size_t k(0); k < contenu[i][j].size(); k++) {
              sortie << contenu[i][j][k] << " ";
          }
          sortie << endl;
        }
      }
      return sortie;
    }

  Construction& operator^=(Construction const& other) {
    for(size_t i(0); i < other.hauteur(); i++) {
      contenu.push_back(other.contenu[i]);
    }
    return *this;
  }

  Construction& operator-=(Construction const& other) {
    if (hauteur() > other.hauteur()) {}
    else {
      for(size_t i(0); i < hauteur(); i++) {
        for(size_t j(0); j < other.contenu[i].size(); j++) {
          contenu[i].push_back(other.contenu[i][j]);
        }
      }
    }
    return *this;
  }

  Construction& operator+=(Construction const& other) {
    if (hauteur() > other.hauteur() or profondeur() > other.profondeur()) {}
    else {
      for(size_t i(0); i < hauteur(); i++) {
        for(size_t j(0); j < profondeur(); j++) {
          for(size_t k(0); k < other.contenu[i][j].size(); k++) {
            contenu[i][j].push_back(other.contenu[i][j][k]);
          }
        }
      }
    }
    return *this;
  }



};
ostream& operator<<(ostream& sortie, Construction const& inst) {
  inst.afficher(sortie);
  return sortie;
}
Construction operator^(Construction c1, Construction const& c2) {
  return c1 ^= c2;
}
Construction operator-(Construction c1, Construction const& c2) {
  return c1 -= c2;
}
Construction operator+(Construction c1, Construction const& c2) {
  return c1 += c2;
}


const Construction operator*(unsigned int n, Construction const& a) {
  Construction res(a);
  for(size_t i(1); i < n; i++)
    res += a;
  return res;
}

const Construction operator/(unsigned int n, Construction const& a) {
  Construction res(a);
  for(size_t i(1); i < n; i++)
    res ^= a;
  return res;
}

const Construction operator%(unsigned int n, Construction const& a) {
  Construction res(a);
  for(size_t i(1); i < n; i++)
    res -= a;
  return res;
}


void test() {
  Brique toitD("obliqueD", "rouge");
  Brique toitG("obliqueG", "rouge");
  Brique toitM(" pleine ", "rouge");
  Brique mur  (" pleine ", "blanc");
  Brique vide ("                 ", "");
  Construction c1(mur);
  Construction c2(toitM);
  c1 = c1 ^ c1;
  c1 = c1 - c1;
  c2 = c2 ^ c2 ^ c2;
  c2 = c2 - c2 - c2;
  cout << "c1" << endl << c1 << endl;
  cout << "c2" << endl << c2 << endl;
  cout << "(c1 + c2)" << endl << (c1 + c2) << endl;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  // Modèles de briques
  Brique toitD("obliqueD", "rouge");
  Brique toitG("obliqueG", "rouge");
  Brique toitM(" pleine ", "rouge");
  Brique mur  (" pleine ", "blanc");
  Brique vide ("                 ", "");

  unsigned int largeur(4);
  unsigned int profondeur(3);
  unsigned int hauteur(3); // sans le toit

  // on construit les murs
  Construction maison( hauteur / ( profondeur % (largeur * mur) ) );

  // on construit le toit
  Construction toit(profondeur % ( toitG + 2*toitM + toitD ));
  toit ^= profondeur % (vide + toitG + toitD);

  // on pose le toit sur les murs
  maison ^= toit;

  // on admire notre construction
  cout << maison << endl;

  return 0;
}
