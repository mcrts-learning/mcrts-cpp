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
protected:
  Coordonnees position_;
  Pavillon pavillon_;
  Etat etat_;
  static const int rayon_rencontre = 10;
public:
  Navire(int, int, Pavillon);

  void avancer(int, int);
  void renflouer();
  virtual void attaque(Navire& rhs) = 0;
  virtual void replique(Navire& rhs) = 0;
  virtual void est_touche() = 0;
  void rencontrer(Navire& rhs);

  const Coordonnees& position() const;
  virtual string toString() const;
  void afficher(ostream&) const;
};
//======================================================

void Coordonnees::operator+=(Coordonnees const& rhs)
  {
    this->x_ += rhs.x();
    this->y_ += rhs.y();
  }
double distance(Coordonnees const& lhs, Coordonnees const& rhs)
  { return sqrt(sq(lhs.x() - rhs.x()) + sq(lhs.y() - rhs.y())); }
string as_string(Coordonnees const& inst)
  { 
    int x(inst.x());
    int y(inst.y());
    return "(" + to_string(x) + ", " + to_string(y) + ")";
  }
ostream& operator<<(ostream& ostr, Coordonnees const& inst)
 {
   ostr << as_string(inst);
   return ostr;
 }

//======================================================

ostream& operator<<(ostream& ostr, Navire const& inst)
  { 
    inst.afficher(ostr);
    return ostr;
  }
double distance(Navire const& lhs, Navire const& rhs)
  { return distance(lhs.position(), rhs.position()); }
//======================================================

string as_string(Pavillon inst)
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
    ostr << as_string(inst);
    return ostr;
  }
string as_string(Etat inst)
  {
    switch (inst) {
      case Intact:
        return "intact";
      case Endommage:
        return "ayant subi des dommages";
      case Coule:
        return "coulé";
      default:
        return "état inconnu";
    }
  }
ostream& operator<<(ostream& ostr, Etat inst)
  { 
    ostr << as_string(inst);
    return ostr;
  }
//======================================================

Navire::Navire(int x, int y, Pavillon pavillon)
  : position_(x, y), pavillon_(pavillon), etat_(Intact) {}

void Navire::renflouer()
  { etat_ = Intact; }
void Navire::avancer(int x, int y)
  { 
    if (etat_ != Coule)
      position_ += Coordonnees(x, y);
  }

void Navire::rencontrer(Navire& rhs)
  {
    if (
        (distance(*this, rhs) <= rayon_rencontre)
        and (this->etat_ != Coule)
        and (rhs.etat_ != Coule)
        and (this->pavillon_ != rhs.pavillon_)
      ) {
      this->attaque(rhs);
      rhs.replique(*this);
    }
  }

const Coordonnees& Navire::position() const
  { return position_; }
string Navire::toString() const
  { 
    string msg;
    msg += " en " + as_string(position()) + " battant pavillon " + as_string(pavillon_) + ", " + as_string(etat_);
    return msg;
  }
void Navire::afficher(ostream& ostr) const
  { ostr << toString(); }
//======================================================

class Pirate: public virtual Navire {
using Navire::Navire;

public:
  void attaque(Navire& rhs) override;
  void replique(Navire& rhs) override;
  void est_touche() override;

  string toString() const override;
};

void Pirate::attaque(Navire& rhs)
  {
    if (etat_ != Coule) {
      cout << "A l'abordage !" << endl;
      rhs.est_touche();
    }
  }
void Pirate::replique(Navire& rhs)
  {
    if (etat_ != Coule) {
      cout << "Non mais, ils nous attaquent ! On riposte !!" << endl;
      this->attaque(rhs);
    }
  }
void Pirate::est_touche()
  {
    switch (Navire::etat_) {
      case Intact:
        Navire::etat_ = Endommage;
        break;
      case Endommage:
        Navire::etat_ = Coule;
        break;
      case Coule:
        break;
    }
  }
string Pirate::toString() const
  { return "bateau pirate" + Navire::toString();  }

//======================================================

class Marchand: public virtual Navire {
using Navire::Navire;

public: 
  void attaque(Navire& rhs) override;
  void replique(Navire& rhs) override;
  void est_touche() override;

  string toString() const override;
};
void Marchand::attaque(Navire& rhs)
  {
    if (etat_ != Coule)
      cout << "On vous aura ! (insultes) " << endl;
    }
void Marchand::replique(Navire& rhs)
  {
    if (etat_ == Coule)
      cout << "SOS je coule !" << endl;
    else
      cout << "Même pas peur !" << endl;
  }
void Marchand::est_touche()
  { etat_ = Coule; }
string Marchand::toString() const
  { return "navire marchand" + Navire::toString();  }

//======================================================

class Felon: public Pirate, public Marchand {
public:
  Felon(int, int, Pavillon);

  void attaque(Navire& rhs) override;
  void replique(Navire& rhs) override;
  void est_touche() override;

  string toString() const override;
};
Felon::Felon(int x, int y, Pavillon pavillon)
  : Navire(x, y, pavillon), Pirate(x, y, pavillon), Marchand(x, y, pavillon) {}

void Felon::attaque(Navire& rhs)
  { Pirate::attaque(rhs); }
void Felon::replique(Navire& rhs)
  { Marchand::replique(rhs); }
void Felon::est_touche()
  { Pirate::est_touche(); }
string Felon::toString() const
  { return "navire félon" + Navire::toString();  }

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
{
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

  return 0;
}
