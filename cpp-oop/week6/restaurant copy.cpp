#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

/*****************************************************
  * Compléter le code à partir d'ici
 *****************************************************/
//====================================================

class Produit {
protected:
  string nom, unite;
public:
  Produit(string nom, string unite="")
  : nom(nom), unite(unite) {}
  string getNom() const {return nom;}
  string getUnite() const {return unite;}
  virtual string toString() const {return getNom();}
  virtual const Produit* adapter(double quantite) const {return this;}
};
//====================================================
typedef Produit* ProduitPTR;

class Ingredient {
private:
  ProduitPTR produit;
  double quantite;
public:
  Ingredient(Produit* produit, double quantite)
  : produit(produit), quantite(quantite) {}
  Produit& getProduit() const {return *produit;}
  double getQuantite() const {return quantite;}
  string descriptionAdaptee() const {
    return to_string(quantite) + " " + produit->getUnite() + " de " + produit->adapter(quantite)->toString();
  }
};
//====================================================
typedef Ingredient* IngredientPTR;

class Recette {
protected:
  string nom;
  double nbFois_;
public:
  vector<IngredientPTR> ingredients;
public:
  Recette(string nom, double nbFois_=1.)
  : nom(nom), nbFois_(nbFois_) {}
  void ajouter(Produit& p, double quantite) {
    ingredients.push_back(new Ingredient(&p, quantite * nbFois_));
  }
  Recette adapter(int n) const {
    Recette recette(nom, nbFois_ * n);
    for (auto& i : ingredients) {
      recette.ajouter(i->getProduit(), i->getQuantite());
    }
    return recette;
  } 
  virtual string toString() const {
    ostringstream msg;
    msg << "  Recette " << '"' << nom << '"' << " x " << nbFois_ << ":";
    for (size_t i(0); i < ingredients.size(); i++) {
      msg << endl;
      msg << "  " << i+1 << ". " << ingredients[i]->descriptionAdaptee();
    }
    return msg.str();
  }
  double quantiteTotale(string& nom) const {return 0;}
};
//====================================================
typedef Recette* RecettePTR;

class ProduitCuisine: public Produit {
private:
  Recette recette;
public:
  ProduitCuisine(string nom, string unite="portion(s)")
  : Produit(nom, unite), recette(Recette(nom)) {}
  void ajouterARecette(Produit& produit, int quantite) {
    recette.ajouter(produit, quantite);
  }
  ProduitCuisine* adapter(double n) const override {
    cout << "HERE--" << endl;
    ProduitCuisine* produit = new ProduitCuisine(nom, unite);
    produit->recette = produit->recette.adapter(n);
    produit->recette.toString();
    return produit;
  }
  string toString() const override {
    cout << "here--" <<endl;
    ostringstream msg;
    msg << Produit::toString() << endl
        << this->recette.toString();
    return msg.str();
  }
};
//====================================================
//====================================================
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

  cout << "//TEST" << endl;
  cout << recette.ingredients[4]->descriptionAdaptee() << endl;
  cout << "TEST\\\\" << endl;

  cout << "===  Recette finale  =====" << endl;
  cout << recette.toString() << endl;
  afficherQuantiteTotale(recette, beurre);
  cout << endl;
/*
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
