#include <iostream>
#include <string>
using namespace std;

class Timbre
{
private:
  static constexpr unsigned int ANNEE_COURANTE = 2016;

  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/
protected:
  string nom;
  unsigned int annee;
  string pays;
  double valeur_faciale;

public:
  unsigned int age() const {return (ANNEE_COURANTE - annee);}
  double vente() const {
    if (age() < 5)
      return valeur_faciale;
    else
      return 2.5 * age() * valeur_faciale;
  }
  void afficher(ostream& strm) const {
    strm << "de nom " << nom << " datant de "
      << annee << " (provenance " << pays << ") ayant pour valeur faciale "
      << valeur_faciale << " francs";
  }
  void print(ostream& strm) const {
    strm << "Timbre ";
    afficher(strm);
  }

public:
  Timbre(string nom, unsigned int annee, string pays="Suisse", double valeur_faciale=1.0)
  : nom(nom), annee(annee), pays(pays), valeur_faciale(valeur_faciale) {}
};

// --------------------------------------------------------------------
ostream& operator<<(ostream& strm, const Timbre& inst) {
    inst.print(strm);
    return strm;
}

// ====================================================================

class Rare: public Timbre
{
private:
  static constexpr unsigned int PRIX_BASE_TRES_RARE = 600;
  static constexpr unsigned int PRIX_BASE_RARE = 400;
  static constexpr unsigned int PRIX_BASE_PEU_RARE = 50;

  unsigned int exemplaire;
  unsigned int getBasePrix() const {
    if (exemplaire < 100)
      return PRIX_BASE_TRES_RARE;
    else if( (100 <= exemplaire) and (exemplaire < 1000) )
      return PRIX_BASE_RARE;
    else
      return PRIX_BASE_PEU_RARE;
  }

public:
  double vente() const {
    return getBasePrix() * ( age() / 10.0 );
  }
  void print(ostream& strm) const {
    strm << "Timbre rare (" << exemplaire << " ex.) ";
    afficher(strm);
  }

public:
  Rare(string nom, unsigned int annee, string pays, double valeur_faciale, unsigned int exemplaire)
  : Timbre(nom, annee, pays, valeur_faciale), exemplaire(exemplaire) {}
};

// --------------------------------------------------------------------
ostream& operator<<(ostream& strm, const Rare& inst) {
    inst.print(strm);
    return strm;
}

// ====================================================================

class Commemoratif: public Timbre
{
public:
  double vente() const {
    return Timbre::vente() * 2;
  }
  void print(ostream& strm) const {
    strm << "Timbre commémoratif ";
    afficher(strm);
  }
public:
  Commemoratif(string nom, unsigned int annee, string pays, double valeur_faciale)
  : Timbre(nom, annee, pays, valeur_faciale) {}
};

// --------------------------------------------------------------------
ostream& operator<<(ostream& strm, const Commemoratif& inst) {
    inst.print(strm);
    return strm;
}

// ====================================================================

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
int main()
{
  /* Ordre des arguments :
  *  nom, année d'émission, pays, valeur faciale, nombre d'exemplaires
  */
  Rare t1( "Guarana-4574", 1960, "Mexique", 0.2, 98 );
  Rare t2( "Yoddle-201"  , 1916, "Suisse" , 0.8,  3 );

  /* Ordre des arguments :
  *  nom, année d'émission, pays, valeur faciale, nombre d'exemplaires
  */
  Commemoratif t3( "700eme-501"  , 2002, "Suisse", 1.5 );
  Timbre       t4( "Setchuan-302", 2004, "Chine" , 0.2 );

  /* Nous n'avons pas encore le polymorphisme :-(
   * (=> pas moyen de faire sans copie ici :-( )  */
  cout << t1 << endl;
  cout << "Prix vente : " << t1.vente() << " francs" << endl;
  cout << t2 << endl;
  cout << "Prix vente : " << t2.vente() << " francs" << endl;
  cout << t3 << endl;
  cout << "Prix vente : " << t3.vente() << " francs" << endl;
  cout << t4 << endl;
  cout << "Prix vente : " << t4.vente() << " francs" << endl;

  return 0;
}
