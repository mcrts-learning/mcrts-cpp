#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

/*****************************************************
  * Compléter le code à partir d'ici
 *****************************************************/
//====================================================
#include <memory>

class Produit {
protected:
  string nom, unite;
public:
  Produit(string, string);
  ~Produit();
  string getNom() const;
  string getUnite() const;
  virtual string toString() const;
  virtual const Produit* adapter(double) const;
  virtual double quantiteTotale(string const&) const;

};
Produit::Produit(string nom, string unite="")
  : nom(nom), unite(unite) {}
Produit::~Produit() {}
string Produit::getNom() const
  { return nom; }
string Produit::getUnite() const
  { return unite; }
string Produit::toString() const
  { return getNom(); }
const Produit* Produit::adapter(double quantite) const
  { return this; }
double Produit::quantiteTotale(string const& nom_produit) const
  {
    if (nom_produit == nom)
      return 1.0;
    else
      return 0.0;
  }

inline bool operator==(Produit const& lhs, Produit const& rhs)
  { return bool(lhs.getNom() == rhs.getNom() and lhs.getUnite() == rhs.getUnite()); }
inline bool operator!=(Produit const& lhs, Produit const& rhs)
  { return !(lhs == rhs); }
//====================================================

class Ingredient {
private:
  Produit const& produit;
  double quantite;
public:
  Ingredient(Produit const&, double);
  ~Ingredient();
  const Produit& getProduit() const;
  double getQuantite() const;
  string descriptionAdaptee() const;
  double quantiteTotale(string const&) const;
};

Ingredient::Ingredient(Produit const& p, double quantite)
  : produit(p), quantite(quantite) {}
Ingredient::~Ingredient() {}
const Produit& Ingredient::getProduit() const
  { return produit; }
double Ingredient::getQuantite() const
  { return quantite; }
string Ingredient::descriptionAdaptee() const
  { return to_string(quantite) + " " + produit.getUnite() + " de " + produit.adapter(quantite)->toString(); }
double Ingredient::quantiteTotale(string const& nom_produit) const
  { return produit.quantiteTotale(nom_produit) * quantite; }
//====================================================

typedef Ingredient* pIngredient;

class Recette {
protected:
  string nom;
  double nbFois_;
public:
  vector<pIngredient> ingredients;
public:
  Recette(string, double);
  ~Recette();
  void clear();
  void ajouter(Produit const&, double);
  Recette adapter(double) const;
  string toString() const;
  double quantiteTotale(string const&) const;
};

Recette::Recette(string nom, double nbFois_=1.)
  : nom(nom), nbFois_(nbFois_) {}
Recette::~Recette() 
  { clear(); }
void Recette::clear()
  {
    for (auto& p : ingredients)
      delete p;
    ingredients.clear();
  }
void Recette::ajouter(Produit const& p, double quantite)
  { ingredients.push_back(new Ingredient(p, quantite * nbFois_));}
Recette Recette::adapter(double n) const
  {
    Recette recette(nom, nbFois_ * n);
    for (auto& i : ingredients) {
      recette.ajouter(i->getProduit(), i->getQuantite()/nbFois_);
    }
    return recette;
  }
string Recette::toString() const
  {
    ostringstream msg;
    msg << "  Recette " << '"' << nom << '"' << " x " << nbFois_ << ":";
    for (size_t i(0); i < ingredients.size(); i++) {
      msg << endl;
      msg << "  " << i+1 << ". " << ingredients[i]->descriptionAdaptee();
    }
    return msg.str();
  }
double Recette::quantiteTotale(string const& nom_produit) const
  {
    double count(0);
    for (auto& i :  ingredients)
      count += i->quantiteTotale(nom_produit);
    return count;
  }
//====================================================

class ProduitCuisine: public Produit {
private:
  Recette recette;
public:
  ProduitCuisine(string, string, double);
  ~ProduitCuisine();
  void ajouterARecette(Produit const&, double);
  const ProduitCuisine* adapter(double n) const override;
  string toString() const override;
  double quantiteTotale(string const&) const override;
};

ProduitCuisine::ProduitCuisine(string nom, string unite="portion(s)", double nbFois_=1.)
  : Produit(nom, unite), recette(Recette(nom, nbFois_)) {}
ProduitCuisine::~ProduitCuisine() {}
void ProduitCuisine::ajouterARecette(Produit const& produit, double quantite)
  { recette.ajouter(produit, quantite); }
const ProduitCuisine* ProduitCuisine::adapter(double n) const
  {
    ProduitCuisine* produit = new ProduitCuisine(nom, unite, n);
    for (auto& i : recette.adapter(n).ingredients) {
      produit->recette.ajouter(i->getProduit(), i->getQuantite() / n);
    }
    return produit;
  }
string ProduitCuisine::toString() const
  {
    ostringstream msg;
    msg << Produit::toString() << endl
        << this->recette.toString();
    return msg.str();
  }
double ProduitCuisine::quantiteTotale(string const& nom_produit) const
  { 
    if (nom_produit == nom)
      return 1.0;
    else
      return recette.quantiteTotale(nom_produit);
  }

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
void afficherQuantiteTotale(const Recette& recette, const Produit& produit)
{
  string nom = produit.getNom();
  cout << "Cette recette contient " << recette.quantiteTotale(nom)
       << " " << produit.getUnite() << " de " << nom << endl;
}

int main()
{
  // quelques produits de base
  Produit oeufs("oeufs");
  Produit farine("farine", "grammes");
  Produit beurre("beurre", "grammes");
  Produit sucreGlace("sucre glace", "grammes");
  Produit chocolatNoir("chocolat noir", "grammes");
  Produit amandesMoulues("amandes moulues", "grammes");
  Produit extraitAmandes("extrait d'amandes", "gouttes");

  ProduitCuisine glacage("glaçage au chocolat");
  // recette pour une portion de glaçage:
  glacage.ajouterARecette(chocolatNoir, 200);
  glacage.ajouterARecette(beurre, 25);
  glacage.ajouterARecette(sucreGlace, 100);
  cout << glacage.toString() << endl;

  ProduitCuisine glacageParfume("glaçage au chocolat parfumé");
  // besoin de 1 portions de glaçage au chocolat et de 2 gouttes
  // d'extrait d'amandes pour 1 portion de glaçage parfumé

  glacageParfume.ajouterARecette(extraitAmandes, 2);
  glacageParfume.ajouterARecette(glacage, 1);
  cout << glacageParfume.toString() << endl;

  Recette recette("tourte glacée au chocolat");
  recette.ajouter(oeufs, 5);
  recette.ajouter(farine, 150);
  recette.ajouter(beurre, 100);
  recette.ajouter(amandesMoulues, 50);
  recette.ajouter(glacageParfume, 2);

  cout << "===  Recette finale  =====" << endl;
  cout << recette.toString() << endl;
  afficherQuantiteTotale(recette, beurre);
  cout << endl;

  // double recette
  Recette doubleRecette = recette.adapter(2);
  cout << "===  Recette finale x 2 ===" << endl;
  cout << doubleRecette.toString() << endl;

  afficherQuantiteTotale(doubleRecette, beurre);
  afficherQuantiteTotale(doubleRecette, oeufs);
  afficherQuantiteTotale(doubleRecette, extraitAmandes);
  afficherQuantiteTotale(doubleRecette, glacage);
  cout << endl;

  cout << "===========================\n" << endl;
  cout << "Vérification que le glaçage n'a pas été modifié :\n";
  cout << glacage.toString() << endl;

  return 0;
}
