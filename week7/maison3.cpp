#include<iostream>
#include<string>
#include<vector>
using namespace std;

struct Maison{
  string adresse;
};

struct Personne{
  string nom;
  Maison& maison;
};

void affiche(Personne p) {
    cout << p.nom << " | "  << p.maison.adresse << endl;
}

void affiche(vector<Personne> personnes) {
    for (auto p : personnes) {
        affiche(p);
    }
}

int main() {
    Maison maison1({"169 rue du faubourg de roubaix, 59800 Lille"});
    Maison maison2({"4 la place, 59695 Gussignies"});

    vector<Personne> personnes;
    personnes.push_back(Personne({"Martin", maison1}));
    personnes.push_back(Personne({"Bernadette", maison1}));
    personnes.push_back(Personne({"Simon", maison2}));
    personnes.push_back(Personne({"Pierre", maison2}));
    affiche(personnes);
    cout << endl;

    personnes.erase(personnes.begin(), personnes.begin()+1);
    //personnes.push_back(Personne({"Martin", maison2}));
    affiche(personnes);
    cout << endl;
    return 0;
}