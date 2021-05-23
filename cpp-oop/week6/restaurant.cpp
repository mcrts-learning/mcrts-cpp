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
};
Produit::Produit(string nom, string unite="")
  : nom(nom), unite(unite) {}
Produit::~Produit() {}
string Produit::getNom() const
  { return nom; }
string Produit::getUnite() const
  { return unite; }
string Produit::toString() const
  { 
    cout << "-- \t TEST : in Produit::toString \t --" << endl;
    return getNom(); }
const Produit* Produit::adapter(double quantite) const
  { return this; }

inline bool operator==(Produit const& lhs, Produit const& rhs)
  { return bool(lhs.getNom() == rhs.getNom() and lhs.getUnite() == rhs.getUnite()); }
inline bool operator!=(Produit const& lhs, Produit const& rhs)
  { return !(lhs == rhs); }

void testProduit() {
  Produit p("oeufs");
  cout << bool(p.getNom() == "oeufs") << " | test Produit::getNom()" << endl;
  cout << bool(p.getUnite() == "") << " | test Produit::getUnite()" << endl;
  cout << bool(p.toString() == "oeufs") << " | test Produit::toString()" << endl;
  cout << bool(*p.adapter(2) == p) << " | test Produit::adapter()" << endl;
}
//====================================================
typedef unique_ptr<Produit> pProduit;

class Ingredient {
private:
  pProduit produit;
  double quantite;
public:
  Ingredient(Produit const&, double);
  ~Ingredient();
  const Produit& getProduit() const;
  double getQuantite() const;
  string descriptionAdaptee() const;
};

Ingredient::Ingredient(Produit const& p, double quantite)
  : produit(new Produit(p.getNom(), p.getUnite())), quantite(quantite) {}
Ingredient::~Ingredient() {}
const Produit& Ingredient::getProduit() const
  { return *produit; }
double Ingredient::getQuantite() const
  { return quantite; }
string Ingredient::descriptionAdaptee() const
  { return to_string(quantite) + " " + produit->getUnite() + " de " + produit->adapter(quantite)->toString(); }


void testIngredient() {
  {
    Produit p("oeufs");
    {    
      Ingredient i(p, 2);
      cout << bool(i.getQuantite() == 2) << " | test Ingredient::getQuantite()" << endl;
      cout << bool(i.getProduit() == p) << " | test Ingredient::getProduit()" << endl;
      cout << bool(i.descriptionAdaptee() == "2.000000  de oeufs") << " | test Ingredient::descriptionAdaptee()" << endl;
    }

    {
      Ingredient i(p, 4);
      cout << bool(i.getQuantite() == 4) << " | test Ingredient::getQuantite()" << endl;
      cout << bool(i.getProduit() == p) << " | test Ingredient::getProduit()" << endl;
      cout << bool(i.descriptionAdaptee() == "4.000000  de oeufs") << " | test Ingredient::descriptionAdaptee()" << endl;
    }
  }

  {
    Produit p("sel", "gramme(s)");
    Ingredient i(p, 10);
    cout << bool(i.getQuantite() == 10) << " | test Ingredient::getQuantite()" << endl;
    cout << bool(i.getProduit() == p) << " | test Ingredient::getProduit()" << endl;
    cout << bool(i.descriptionAdaptee() == "10.000000 gramme(s) de sel") << " | test Ingredient::descriptionAdaptee()" << endl;
  }
}
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
  Recette adapter(int) const;
  string toString() const;
  double quantiteTotale(string&) const;
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
Recette Recette::adapter(int n) const
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
double Recette::quantiteTotale(string& nom) const {return 0;}

void testRecette() {
  {
    Produit p("oeufs");
    Recette r("omelette");
    ostringstream oss;
    oss << "  Recette " << '"' << "omelette" << '"' << " x 1:";
    cout << bool(r.toString() == oss.str()) << " | test Recette::toString()" << endl;
    r.ajouter(p, 2);
    oss << endl << "  1. 2.000000  de oeufs";
    cout << bool(r.toString() == oss.str()) << " | test Recette::toString()" << endl;
  }

  {
    Produit p("oeufs");
    Recette r("omelette pour deux", 2);
    ostringstream oss;
    oss << "  Recette " << '"' << "omelette pour deux" << '"' << " x 2:";
    cout << bool(r.toString() == oss.str()) << " | test Recette::toString()" << endl;
    r.ajouter(p, 2);
    oss << endl << "  1. 4.000000  de oeufs";
    cout << bool(r.toString() == oss.str()) << " | test Recette::toString()" << endl;
  }

  {
    Produit p("oeufs");
    Recette r("omelette pour deux");
    r.ajouter(p, 2);
    Recette r_adpat = r.adapter(10);
    ostringstream oss;
    oss << "  Recette " << '"' << "omelette pour deux" << '"' << " x 10:";
    oss << endl << "  1. 20.000000  de oeufs";
    cout << bool(r_adpat.toString() == oss.str()) << " | test Recette::toString()" << endl;
  }

  {
    Produit p("oeufs");
    Recette r("omelette pour trois", 2);
    r.ajouter(p, 3);
    Recette r_adpat = r.adapter(10);
    ostringstream oss;
    oss << "  Recette " << '"' << "omelette pour trois" << '"' << " x 20:";
    oss << endl << "  1. 60.000000  de oeufs";
    cout << bool(r_adpat.toString() == oss.str()) << " | test Recette::toString()" << endl;
  }
}
//====================================================

class ProduitCuisine: public Produit {
private:
  Recette recette;
public:
  ProduitCuisine(string, string);
  ~ProduitCuisine();
  void ajouterARecette(Produit const&, double);
  const ProduitCuisine* adapter(double n) const override;
  string toString() const override;
};

ProduitCuisine::ProduitCuisine(string nom, string unite="portion(s)")
  : Produit(nom, unite), recette(Recette(nom)) {}
ProduitCuisine::~ProduitCuisine() {}
void ProduitCuisine::ajouterARecette(Produit const& produit, double quantite)
  { recette.ajouter(produit, quantite); }
const ProduitCuisine* ProduitCuisine::adapter(double n) const
  {
    ProduitCuisine* produit = new ProduitCuisine(nom, unite);
    for (auto& i : this->recette.adapter(n).ingredients)
      produit->recette.ajouter(i->getProduit(), i->getQuantite());
    return produit;
  }
string ProduitCuisine::toString() const
  {
    cout << "-- \t TEST : in ProduitCuisine::toString \t --" << endl;
    ostringstream msg;
    msg << Produit::toString() << endl
        << this->recette.toString();
    return msg.str();
  }

void testProduitCusine() {
  {
    ProduitCuisine p("omelette");
    cout << " | test ProduitCuisine::toString()" << endl << p.toString() << endl;
    cout << endl;
  }

  {
    ProduitCuisine p("omelette");
    p.ajouterARecette(Produit("oeufs"), 2);
    p.ajouterARecette(Produit("sel", "pincée(s)"), 1);
    p.ajouterARecette(Produit("beurre", "gramme(s)"), 5);
    cout << " | test ProduitCuisine::ajouterARecette()" << endl << p.toString() << endl;
    cout << endl;
  }

  {
    ProduitCuisine p("omelette");
    p.ajouterARecette(Produit("oeufs"), 2);
    p.ajouterARecette(Produit("sel", "pincée(s)"), 1);
    p.ajouterARecette(Produit("beurre", "gramme(s)"), 5);
    cout << " | test ProduitCuisine::adapter()" << endl << p.adapter(2)->toString() << endl;
    cout << endl;
  }
}

//====================================================
void testProduitCusine_Ingredient() {
  {
    ProduitCuisine p("omelette");
    p.ajouterARecette(Produit("oeufs"), 2);
    p.ajouterARecette(Produit("sel", "pincée(s)"), 1);
    p.ajouterARecette(Produit("beurre", "gramme(s)"), 5);
    Ingredient i(p, 2);
    cout << bool(i.getProduit().toString() == p.toString()) << " | test Ingredient::getProduit()" << endl;
    cout << i.getProduit().toString() << endl;
    cout << p.toString() << endl;
    cout << bool(i.getProduit().adapter(2)->toString() == p.adapter(2)->toString()) << " | test Ingredient::adapter()"<< endl;
    cout << i.getProduit().adapter(2)->toString() << endl;
    cout << p.adapter(2)->toString() << endl;
    cout << " | test Ingredient::descriptionAdaptee()" << endl << i.descriptionAdaptee() << endl;
    cout << endl;
  }
}
//====================================================
void test() {
  cout << boolalpha;
  cout << "--- Test Produit ---" << endl;
  testProduit();
  cout << endl;
  cout << "--- Test Ingredient ---" << endl;
  testIngredient();
  cout << endl;
  cout << "--- Test Recette ---" << endl;
  testRecette();
  cout << endl;
  cout << "--- Test ProduitCuisine ---" << endl;
  testProduitCusine();
  cout << "--- Test ProduitCuisine & Ingredient ---" << endl;
  testProduitCusine_Ingredient();
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
  test();
  /*
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
*/
  return 0;
}
