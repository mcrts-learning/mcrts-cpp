#include <string>
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

typedef string Date;

//========================================================
class Employe {
protected:
    string nom, prenom;
    int age;
    Date date_entree;
public:
    Employe(string nom, string prenom, int age, Date date_entree)
    : nom(nom), prenom(prenom), age(age), date_entree(date_entree) {}
    virtual ~Employe() {
        cout << "Delete | " << get_nom() << endl;
    };
    virtual double calculer_salaire() const = 0;
    virtual string get_nom() const {
        return "L'employé " + prenom + ' ' + nom;
    }
};
//========================================================
class Commercial: public Employe {
protected:
    double chiffre_affaire;
public:
    Commercial(string nom, string prenom, int age, Date date_entree, double chiffre_affaire)
    : Employe(nom, prenom, age, date_entree), chiffre_affaire(chiffre_affaire) {}
    ~Commercial() {}
};
//========================================================
class Vendeur: public Commercial {
using Commercial::Commercial;
public:
    ~Vendeur() {}
    double calculer_salaire() const override {
        return (0.2 * chiffre_affaire) + 400;
    }
    string get_nom() const override {
        return "Le vendeur " + prenom + ' ' + nom;
    }
};
//========================================================
class Representant: public Commercial {
using Commercial::Commercial;
public:
    ~Representant() {}
    double calculer_salaire() const override {
        return (0.2 * chiffre_affaire) + 800;
    }
    string get_nom() const override {
        return "Le représentant " + prenom + ' ' + nom;
    }
};
//========================================================
class Technicien: public Employe {
protected:
    int unites;
public:
    Technicien(string nom, string prenom, int age, Date date_entree, int unites)
    : Employe(nom, prenom, age, date_entree), unites(unites) {}
    ~Technicien() {}
    double calculer_salaire() const override {
        return 5.0 * unites;
    }
    string get_nom() const override {
        return "Le technicien " + prenom + ' ' + nom;
    }
};
//========================================================
class Manutentionnaire: public Employe {
protected:
    int heures;
public:
    Manutentionnaire(string nom, string prenom, int age, Date date_entree, int heures)
    : Employe(nom, prenom, age, date_entree), heures(heures) {}
    ~Manutentionnaire() {}
    double calculer_salaire() const override {
        return 65.0 * heures;
    }
    string get_nom() const override {
        return "Le manut. " + prenom + ' ' + nom;
    }
};
//========================================================
class Risque {
protected:
    double prime_mensuelle;
public:
    Risque(double prime_mensuelle=100.0)
    : prime_mensuelle(prime_mensuelle) {}
    ~Risque() {}
};
//========================================================
class TechnicienARisque: public Technicien, public Risque {
public:
    TechnicienARisque(string nom, string prenom, int age, Date date_entree, int unites, double prime_mensuelle=100.0)
    : Technicien(nom, prenom, age, date_entree, unites), Risque(prime_mensuelle) {}
    ~TechnicienARisque() {}
    double calculer_salaire() const override {
        return Technicien::calculer_salaire() + prime_mensuelle;
    }
};
//========================================================
class ManutentionnaireARisque: public Manutentionnaire, public Risque {
public:
    ManutentionnaireARisque(string nom, string prenom, int age, Date date_entree, int heures, double prime_mensuelle=100.0)
    : Manutentionnaire(nom, prenom, age, date_entree, heures), Risque(prime_mensuelle) {}
    ~ManutentionnaireARisque() {}
    double calculer_salaire() const override {
        return Manutentionnaire::calculer_salaire() + prime_mensuelle;
    }
};
//========================================================
typedef unique_ptr<Employe> Employe_ptr;

class Personnel {
protected:
    vector<Employe_ptr> employes;
public:
    Personnel() {}
    ~Personnel() {
        licencie();
    }
    void ajouter_employe(Employe* e) {
        employes.push_back(Employe_ptr(e));
    }

    void calculer_salaires() const {
        for (auto& e : employes)
            cout << e->get_nom() << " gagne " << e->calculer_salaire() << endl;
    }

    double salaire_moyen() const {
        double total(0);
        for (auto& e : employes)
            total += e->calculer_salaire();
        return (total / employes.size());
    }

    void licencie() {
        for (auto& p : employes)
            p.reset();
        employes.clear();
    }
};
//========================================================

void test(){
    cout << boolalpha;

    Vendeur v1("Pierre", "Business", 45, "1995", 30000);
    Representant v2("Léon", "Vendtout", 25, "2001", 20000);
    Technicien v3("Yves", "Bosseur", 28, "1998", 1000);
    Manutentionnaire v4("Jeanne", "Stocketout", 32, "1998", 45);
    TechnicienARisque v5("Jean", "Flippe", 28, "2000", 1000, 200);
    ManutentionnaireARisque v6("Al", "Abordage", 30, "2001", 45, 120);
    cout << bool(v1.calculer_salaire() == 6400) << " | Test Vendeur::calculer_salaire()" << endl;
    cout << bool(v2.calculer_salaire() == 4800) << " | Test Representant::calculer_salaire()" << endl;
    cout << bool(v3.calculer_salaire() == 5000) << " | Test Technicien::calculer_salaire()" << endl;
    cout << bool(v4.calculer_salaire() == 2925) << " | Test Manutentionnaire::calculer_salaire()" << endl;
    cout << bool(v5.calculer_salaire() == 5200) << " | Test TechnicienARisque::calculer_salaire()" << endl;
    cout << bool(v6.calculer_salaire() == 3045) << " | Test ManutentionnaireARisque::calculer_salaire()" << endl;

    cout << endl;

    cout << v1.get_nom() << " | Test Vendeur::get_nom()" << endl;
    cout << v2.get_nom() << " | Test Representant::get_nom()" << endl;
    cout << v3.get_nom() << " | Test Technicien::get_nom()" << endl;
    cout << v4.get_nom() << " | Test Manutentionnaire::get_nom()" << endl;
    cout << v5.get_nom() << " | Test TechnicienARisque::get_nom()" << endl;
    cout << v6.get_nom() << " | Test ManutentionnaireARisque::get_nom()" << endl;
}

void testPersonnel(){
    Personnel p;
    
    p.ajouter_employe(new Vendeur("Pierre", "Business", 45, "1995", 30000));
    p.ajouter_employe(new Representant("Léon", "Vendtout", 25, "2001", 20000));
    p.ajouter_employe(new Technicien("Yves", "Bosseur", 28, "1998", 1000));
    p.ajouter_employe(new Manutentionnaire("Jeanne", "Stocketout", 32, "1998", 45));
    p.ajouter_employe(new TechnicienARisque("Jean", "Flippe", 28, "2000", 1000, 200));
    p.ajouter_employe(new ManutentionnaireARisque("Al", "Abordage", 30, "2001", 45, 120));
    
    p.calculer_salaires();
    cout << "Le salaire moyen dans l'entreprise est de "
         << p.salaire_moyen() << " francs." << endl;
    
    p.licencie();
}
//========================================================
int main() {
    testPersonnel();
    return 0;
}