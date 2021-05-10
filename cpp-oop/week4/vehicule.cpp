#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

extern const int DATE = 2015;

class Vehicule {
    protected:
        string marque;
        int date_achat;
        double prix_achat;
        double prix_courant;
    
    public:
        Vehicule(string marque, int date_achat, double prix_achat)
        : marque(marque), date_achat(date_achat), prix_achat(prix_achat), prix_courant(prix_achat) {}

        void affiche(ostream& cout) const {
            cout << "Vehicule(marque=\"" << marque
                 << "\", date_achat=" << date_achat
                 << ", prix_achat=" << prix_achat
                 << ", prix_courant=" << prix_courant
                 << ")";
        }
        void calculePrix() {
            prix_courant = prix_achat * (1 - 0.01 * (DATE - date_achat));
        }
};

ostream& operator<<(ostream& cout, const Vehicule& inst) {
    inst.affiche(cout);
    return cout;
}

class Voiture: public Vehicule {
    private:
        double cylindre;
        int nb_porte;
        double puissance;
        double kilometrage;
    
    public:
        Voiture(string marque, int date_achat, double prix_achat, double cylindre, int nb_porte, double puissance, double kilometrage)
        : Vehicule(marque, date_achat, prix_achat),
          cylindre(cylindre), nb_porte(nb_porte), puissance(puissance), kilometrage(kilometrage) {}

        void affiche(ostream& cout) const {
            cout << "Voiture(" << endl << "  ";
            Vehicule::affiche(cout);
            cout << endl
                 << "  cylindre=" << cylindre
                 << ", nb_porte=" << nb_porte
                 << ", puissance=" << puissance
                 << ", kilometrage=" << kilometrage
                 << endl << ")";
        }
        void calculePrix() {
            double rate(0);
            rate += 0.02 * (DATE - date_achat);
            rate += 0.05 * round(kilometrage / 10000);
            if (marque == "Renault" or marque == "Fiat")
                rate += 0.1;
            if (marque == "Ferrari" or marque == "Porsche")
                rate -= 0.2;
            prix_courant = prix_achat * (1 - rate);
        }
};

ostream& operator<<(ostream& cout, const Voiture& inst) {
    inst.affiche(cout);
    return cout;
}

enum PropulsionType { REACTION, HELICES };

class Avion: public Vehicule {
    private:
        PropulsionType propulsion;
        double nb_heure;
    public:
        Avion(string marque, int date_achat, double prix_achat, PropulsionType propulsion, double nb_heure)
        : Vehicule(marque, date_achat, prix_achat),
          propulsion(propulsion), nb_heure(nb_heure) {}
        
        void affiche(ostream& cout) const {
            cout << "Avion(" << endl << "  ";
            Vehicule::affiche(cout);
            string t;
            if (propulsion == HELICES)
                t = "helices";
            else
                t = "reaction";
            cout << endl
                 << "  type=" << t
                 << ", nb_heure=" << nb_heure
                 << endl << ")";
        }
        void calculePrix() {
            double rate(0);
            if (propulsion == REACTION)
                rate += 0.1 * round(nb_heure / 1000);
            else
                rate += 0.1 * round(nb_heure / 100);
            rate = min(1.0, rate);
            prix_courant = prix_achat * (1 - rate);
        }
};

ostream& operator<<(ostream& cout, const Avion& inst) {
    inst.affiche(cout);
    return cout;
}



int main() {
    cout << fixed << std::setprecision(2);
    vector<Voiture> garage;
    vector<Avion> hangar;
    garage.push_back(Voiture("Peugeot", 1998, 147325.79, 2.5, 5, 180.0, 12000));
    garage.push_back(Voiture("Porsche", 1985, 250000.00, 6.5, 2, 280.0, 81320));
    garage.push_back(Voiture("Fiat", 2001, 7327.30, 1.6, 3, 65.0, 3000));
    hangar.push_back(Avion("Cessna", 1972, 1230673.90, HELICES, 250));
    hangar.push_back(Avion("Nain Connu", 1992, 4321098.00, REACTION, 1300));
    for (auto voiture : garage) {
        voiture.calculePrix();
        voiture.affiche(cout);
        cout << endl;
    }
    for (auto avion : hangar) {
        avion.calculePrix();
        avion.affiche(cout);
        cout << endl;
    }
    return 0;
}