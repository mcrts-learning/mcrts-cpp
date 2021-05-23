#include <iostream>
#include <cmath>
using namespace std;

enum Pavillon { JollyRogers, CompagnieDuSenegal, CompagnieDOstende };

enum Etat { Intact, Endommage, Coule };

int sq(int x)
{
  return x*x;
}

class Coordonnees
{
public:
  Coordonnees(int un_x, int un_y) : x_(un_x), y_(un_y) {}
  int x() const {
    return x_;
  }
  int y() const {
    return y_;
  }
  void operator+=(Coordonnees const& autre); // à définir plus bas
private:
  int x_;
  int y_;
};

class Navire
{
  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/

public:
  void rencontrer(Navire const& rhs);
  const Coordonnees& getCoordonnees() const;

};
//======================================================

void Coordonnees::operator+=(Coordonnees const& rhs)
  {
    this->x_ += rhs.x();
    this->y_ += rhs.y();
  }
double distance(Coordonnees const& lhs, Coordonnees const& rhs)
  { return sqrt(sq(lhs.x() - rhs.x()) + sq(lhs.y() - rhs.y())); }
ostream& operator<<(ostream& ostr, Coordonnees const& inst)
 {
   ostr << "(" << inst.x() << ", " << inst.y() << ")";
   return ostr;
 }
//======================================================

ostream& operator<<(ostream& ostr, Navire const& inst)
  { return ostr; }
double distance(Navire const& lhs, Navire const& rhs)
  { return distance(lhs.getCoordonnees(), rhs.getCoordonnees()); }
//======================================================

string to_string(Pavillon inst)
{
  switch (inst) {
    case JollyRogers:
      return "pirate";
    case CompagnieDuSenegal:
      return "français";
    case CompagnieDOstende:
      return "autrichien";
    default:
      return "pavillon inconnu";
  }
}
ostream& operator<<(ostream& ostr, Pavillon inst)
  { 
    ostr << to_string(inst);
    return ostr;
  }

string to_string(Etat inst)
  {
    switch (inst) {
      case Intact:
        return "intact";
      case Endommage:
        return "yant subi des dommages";
      case Coule:
        return "coulé";
      default:
        return "état inconnu";
    }
  }
ostream& operator<<(ostream& ostr, Etat inst)
  { 
    ostr << to_string(inst);
    return ostr;
  }
//======================================================

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

void rencontre(Navire& ship1, Navire& ship2)
{
  cout << "Avant la rencontre :" << endl;
  cout << ship1 << endl;
  cout << ship2 << endl;
  cout << "Distance : " << distance(ship1, ship2) << endl;
  ship1.rencontrer(ship2);
  cout << "Apres la rencontre :" << endl;
  cout << ship1 << endl;
  cout << ship2 << endl;
}

int main()
{/*
  // Test de la partie 1
  cout << "===== Test de la partie 1 =====" << endl << endl;

  // Un bateau pirate 0,0
  Pirate ship1(0, 0, JollyRogers);
  cout << ship1 << endl;

  // Un bateau marchand en 25,0
  Marchand ship2(25, 0, CompagnieDuSenegal);
  cout << ship2 << endl;

  cout << "Distance : " << distance(ship1, ship2) << endl;

  cout << "Quelques déplacements..." << endl;
  cout << "  en haut à droite :" << endl;
  // Se déplace de 75 unités à droite et 10 en haut
  ship1.avancer(75, 10);
  cout << ship1 << endl;

  cout << "  vers le bas :" << endl;
  ship1.avancer(0, -5);
  cout << ship1 << endl;

  cout << endl << "===== Test de la partie 2 =====" << endl << endl;

  cout << "Bateau pirate et marchand ennemis (trop loins) :" << endl;
  rencontre(ship1, ship2);

  cout << endl << "Bateau pirate et marchand ennemis (proches) :" << endl;
  ship1.avancer(-40, -2);
  ship2.avancer(10, 2);
  rencontre(ship1, ship2);

  cout << endl << "Deux bateaux pirates ennemis intacts (proches) :" << endl;
  Pirate ship3(33, 8, CompagnieDOstende);
  rencontre(ship1, ship3);

  cout << endl << "Bateaux pirates avec dommages, ennemis :" << endl;
  rencontre(ship1, ship3);

  cout << endl << "Bateaux marchands ennemis :" << endl;
  Marchand ship4(21, 7, CompagnieDuSenegal);
  Marchand ship5(27, 2, CompagnieDOstende);
  rencontre(ship4, ship5);

  cout << endl << "Pirate vs Felon :" << endl;
  ship3.renflouer();
  Felon ship6(32, 10, CompagnieDuSenegal);
  rencontre(ship3, ship6);

  cout << endl << "Felon vs Pirate :" << endl;
  rencontre(ship6, ship3);
*/
  return 0;
}
