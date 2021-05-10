#include<iostream>
#include<string>
#include<vector>
#include<memory>
using namespace std;

struct Maison{
  string adresse;
};

struct Personne{
  string nom;
  shared_ptr<Maison> maison;
};

void affiche(Personne p) {
    cout << p.nom << " | "  << (*p.maison).adresse << endl;
}

void affiche(vector<Personne> personnes) {
    for (auto p : personnes) {
        affiche(p);
    }
}

int main() {
    shared_ptr<Maison> maison1(new Maison({"169 rue du faubourg de roubaix, 59800 Lille"}));
    shared_ptr<Maison> maison2(new Maison({"4 la place, 59695 Gussignies"}));
    
    vector<Personne> personnes;
    personnes.push_back(Personne({"Martin", maison1}));
    personnes.push_back(Personne({"Bernadette", maison1}));
    personnes.push_back(Personne({"Simon", maison2}));
    personnes.push_back(Personne({"Pierre", maison2}));
    affiche(personnes);
    cout << endl;

    personnes[0].maison = maison2;
    affiche(personnes);
    cout << endl;
    return 0;
}