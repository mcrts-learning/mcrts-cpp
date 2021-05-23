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

void testProduit() {
  Produit p("oeufs");
  cout << bool(p.getNom() == "oeufs") << " | test Produit::getNom()" << endl;
  cout << bool(p.getUnite() == "") << " | test Produit::getUnite()" << endl;
  cout << bool(p.toString() == "oeufs") << " | test Produit::toString()" << endl;
  cout << bool(*p.adapter(2) == p) << " | test Produit::adapter()" << endl;
  cout << bool(p.quantiteTotale("oeufs") == 1.0) << " | test Produit::quantiteTotale()" << endl;
  cout << bool(p.quantiteTotale("sel") == 0.0) << " | test Produit::quantiteTotale()" << endl;
}
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

void testIngredient() {
  {
    Produit p("oeufs");
    {    
      Ingredient i(p, 2);
      cout << bool(i.getQuantite() == 2) << " | test Ingredient::getQuantite()" << endl;
      cout << bool(i.getProduit() == p) << " | test Ingredient::getProduit()" << endl;
      cout << bool(i.descriptionAdaptee() == "2.000000  de oeufs") << " | test Ingredient::descriptionAdaptee()" << endl;
      cout << bool(i.quantiteTotale("oeufs") == 2.0) << " | test Ingredient::quantiteTotale()" << endl;
      cout << bool(i.quantiteTotale("sel") == 0.0) << " | test Ingredient::quantiteTotale()" << endl;
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
    cout << bool(r.quantiteTotale("oeufs") == 2.0) << " | test Recette::quantiteTotale()" << endl;
    cout << bool(r.quantiteTotale("sel") == 0.0) << " | test Recette::quantiteTotale()" << endl;
  }

  {
    Produit p("oeufs");
    Recette r("omelette");
    r.ajouter(p, 2);
    r.ajouter(p, 10);
    cout << bool(r.quantiteTotale("oeufs") == 12.0) << " | test Recette::quantiteTotale()" << endl;
    cout << bool(r.quantiteTotale("sel") == 0.0) << " | test Recette::quantiteTotale()" << endl;
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
    cout << bool(r.quantiteTotale("oeufs") == 4.0) << " | test Recette::quantiteTotale()" << endl;
    cout << bool(r.quantiteTotale("sel") == 0.0) << " | test Recette::quantiteTotale()" << endl;
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
    cout << bool(r_adpat.quantiteTotale("oeufs") == 20.0) << " | test Recette::quantiteTotale()" << endl;
    cout << bool(r_adpat.quantiteTotale("sel") == 0.0) << " | test Recette::quantiteTotale()" << endl;
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
  {
    Produit oeufs("oeufs");
    Produit farine("farine", "grammes");
    Produit beurre("beurre", "grammes");
    Produit sucreGlace("sucre glace", "grammes");
    Produit chocolatNoir("chocolat noir", "grammes");
    Produit amandesMoulues("amandes moulues", "grammes");
    Produit extraitAmandes("extrait d'amandes", "gouttes");

    ProduitCuisine glacage("glaçage au chocolat");
    glacage.ajouterARecette(chocolatNoir, 200);
    glacage.ajouterARecette(beurre, 25);
    glacage.ajouterARecette(sucreGlace, 100);

    ProduitCuisine glacageParfume("glaçage au chocolat parfumé");
    glacageParfume.ajouterARecette(extraitAmandes, 2);
    glacageParfume.ajouterARecette(glacage, 1);

    Recette recette("tourte glacée au chocolat");
    recette.ajouter(oeufs, 5);
    recette.ajouter(farine, 150);
    recette.ajouter(beurre, 100);
    recette.ajouter(amandesMoulues, 50);
    recette.ajouter(glacageParfume, 2);
    
    cout << bool(recette.quantiteTotale("beurre") == 150.0) << " | test ProduitCuisine::quantiteTotale()" << endl;

    Recette doubleRecette = recette.adapter(2);
    cout << bool(doubleRecette.quantiteTotale("beurre") == 300.0) << " | test ProduitCuisine::quantiteTotale()" << endl;
    cout << bool(doubleRecette.quantiteTotale("oeufs") == 10.0) << " | test ProduitCuisine::quantiteTotale()" << endl;
    cout << bool(doubleRecette.quantiteTotale("extrait d'amandes") == 8.0) << " | test ProduitCuisine::quantiteTotale()" << endl;
    cout << bool(doubleRecette.quantiteTotale("glaçage au chocolat") == 4.0) << " | test ProduitCuisine::quantiteTotale()" << endl;
  }
}
//====================================================

void testProduitCusine_Ingredient() {
  {
    ProduitCuisine p("omelette");
    Produit oeufs("oeufs");
    Produit sel("sel", "pincée(s)");
    Produit beurre("beurre", "gramme(s)");
    p.ajouterARecette(oeufs, 2);
    p.ajouterARecette(sel, 1);
    p.ajouterARecette(beurre, 5);
    Ingredient i(p, 2);
    cout << bool(i.getProduit().toString() == p.toString()) << " | test Ingredient::getProduit()" << endl;
    cout << bool(i.getProduit().adapter(2)->toString() == p.adapter(2)->toString()) << " | test Ingredient::adapter()"<< endl;
    cout << " | test Ingredient::descriptionAdaptee()" << endl << i.descriptionAdaptee() << endl;
    cout << endl;
  }
}
//====================================================

void test_debug1(){
  Produit farine_cs("Farine", "cs");
  ProduitCuisine sauce("Sauce aux noisettes");
  sauce.ajouterARecette(farine_cs, 25);
  ProduitCuisine p("Lait au noisettes");
  p.ajouterARecette(sauce, 8.5);
  cout << bool(p.adapter(7)->quantiteTotale("Farine") == 1487.5) << endl;
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

void test_debug() {
  cout << boolalpha;
  cout << "--- Test 1 ---" << endl;
  test_debug1();
  cout << endl;
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
