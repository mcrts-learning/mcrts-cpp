#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum Category { saving, business };

class Compte {
  private:
    Category category;
    double solde;
    double taux;

  public:
    Compte(Category category, double solde, double taux)
    : category(category), solde(solde), taux(taux) {}

    void afficheCompte() {
      string s;
      switch ( category ) {
        case saving:
          s = "epargne";
          break;
        case business:
          s = "courant";
          break;
      }
      cout << "   Compte " << s << " : " << solde << " francs" << endl;
    }

    void compoundInterest() {
      double interets(taux * solde);
      solde = solde + interets;
    }
};

class Client {
  private:
    string nom;
    string ville;
    vector<Compte> comptes;

    void afficheComptes() {
      for(auto c : comptes) {
        c.afficheCompte();
      }
    }
    void afficheClient() {
      cout << "Client " << nom << " de " << ville << endl;
    }
  
  public:
    Client(string nom, string ville)
    : nom(nom), ville(ville) {
      vector<Compte> comptes({});
    }
    void afficheClientDetails() {
      afficheClient();
      afficheComptes();
    }

    void addCompte(Compte c) {
      comptes.push_back(c);
    }

    void compoundInterest() {
      for(size_t i(0); i < comptes.size(); i++) {
        comptes[i].compoundInterest();
      }
    }
};

int main()
{
  // Données pour tous les comptes privés (taux d'intérêt) :
  double taux1(0.01);
  // Données pour tous les comptes d'épargne (taux d'intérêt) :
  double taux2(0.02);

  Client client1("Pedro", "Genève");
  Compte c1(business, 1000.0, taux1);
  Compte c2(saving, 2000.0, taux2);
  client1.addCompte(c1);
  client1.addCompte(c2);


  Client client2("Alexandra", "Lausanne");
  Compte c3(business, 3000.0, taux1);
  Compte c4(saving, 4000.0, taux2);
  client2.addCompte(c3);
  client2.addCompte(c4);

  cout << "Données avant le bouclement des comptes :" << endl;
  client1.afficheClientDetails();
  client2.afficheClientDetails();
  client1.compoundInterest();
  client2.compoundInterest();

  cout << "Données apres le bouclement des comptes :" << endl;
  client1.afficheClientDetails();
  client2.afficheClientDetails();

  return 0;
}
