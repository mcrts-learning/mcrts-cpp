#include <string>
#include <iostream>
using namespace std;

//========================================
class Animal {
protected:
    string nom, continent;

public:
    Animal(string, string);
    ~Animal();
    virtual ostream& affiche(ostream&) const;
};

Animal::Animal(string nom, string continent)
: nom(nom), continent(continent) {
    cout << "Nouvel animal protégé" << endl;
}
Animal::~Animal() {
    cout << "Je ne suis plus protégé" << endl;
}


ostream& Animal::affiche(ostream& ostr=cout) const {
    ostr << "Je suis un " << nom << " et je vis en " << continent << ".";
    return ostr;
}
//========================================
class EnDanger {
protected:
    int nombre;

public:
    EnDanger(int);
    ~EnDanger();
    ostream& affiche(ostream&) const;
};

EnDanger::EnDanger(int nombre)
: nombre(nombre) {
    cout << "Nouvel animal en danger" << endl;
}
EnDanger::~EnDanger() {
    cout << "ouf! Je ne suis plus en danger" << endl;
}


ostream& EnDanger::affiche(ostream& ostr=cout) const {
    ostr << "Il ne reste que " << nombre << " individus de mon espèce sur Terre !";
    return ostr;
}
//========================================
class Gadget {
protected:
    string nom;
    double prix;

public:
    Gadget(string, double);
    ~Gadget();
    ostream& affiche(ostream&) const;
    ostream& affiche_prix(ostream&) const;
    
};

Gadget::Gadget(string nom, double prix)
: nom(nom), prix(prix) {
    cout << "Nouveau gadget" << endl;
}
Gadget::~Gadget() {
    cout << "Je ne suis plus un gadget" << endl;
}

ostream& Gadget::affiche(ostream& ostr=cout) const {
    ostr << "Mon nom est " << nom << ".";
    return ostr;
}

ostream& Gadget::affiche_prix(ostream& ostr=cout) const {
    ostr << "Achetez-moi pour " << prix << " francs et vous contribuerez à me sauver !";
    return ostr;
}
//========================================
class Peluche: public Animal, public EnDanger, public Gadget {
public:
    Peluche(string, string, string, int, double);
    ostream& etiquette(ostream&) const;
};

Peluche::Peluche(string nom_animal, string nom_gadget, string continent, int nombre, double prix)
: Animal(nom_animal, continent), EnDanger(nombre), Gadget(nom_gadget, prix) {}

ostream& Peluche::etiquette(ostream& ostr=cout) const {
    ostr << "Hello," << endl;
    Gadget::affiche(ostr);
    ostr << endl;
    Animal::affiche(ostr);
    ostr << endl;
    EnDanger::affiche(ostr);
    ostr << endl;
    Gadget::affiche_prix(ostr);
    ostr << endl;
    return ostr;
}
//========================================


int main() {
    Peluche panda("Panda","Ming","Asie", 200, 20.0);
    Peluche serpent("Cobra","Ssss","Asie", 500, 10.0);
    Peluche toucan("Toucan","Bello","Amérique", 1000, 15.0);
    panda.etiquette();
    serpent.etiquette();
    toucan.etiquette();

    return 0;
}