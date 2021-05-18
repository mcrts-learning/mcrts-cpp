#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

// ==================================================================================================
class Livre {
protected:
    string titre, auteur;
    int pages;
    bool bestseller;
public:
    Livre(string titre, string auteur, int pages, bool bestseller);
    virtual ~Livre();
    virtual ostream& afficher(ostream& strm) const;
    virtual double calculer_prix() const;
};

Livre::Livre(string titre, string auteur, int pages, bool bestseller)
: titre(titre), auteur(auteur), pages(pages), bestseller(bestseller) {}
Livre::~Livre() {}
double Livre::calculer_prix() const {
    return pages * 0.3 + 50 * bestseller;
}

ostream& Livre::afficher(ostream& strm) const {
    strm<< "titre=" << titre << endl
        << "auteur=" << auteur << endl
        << "pages=" << pages << endl
        << "bestseller=" << boolalpha << bestseller << noboolalpha << endl
        << "prix=" << calculer_prix() << endl;
    return strm;
}

void testLivre() {
    Livre l1("titre", "auteur", 5, true);
    cout << boolalpha << true << " | test Livre" << endl;
    cout << boolalpha << bool(l1.calculer_prix() == 51.5) << " | test Livre::calculer_prix bestseller" << endl;
    Livre l2("titre", "auteur", 5, false);
    cout << boolalpha << bool(l2.calculer_prix() == 1.5) << " | test Livre::calculer_prix" << endl;
}
// ==================================================================================================
class Roman : public Livre {
protected:
    bool biographie;
public:
    Roman(string titre, string auteur, int pages, bool bestseller, bool biographie);
    virtual ~Roman();
    ostream& afficher(ostream& strm) const override;
};
Roman::Roman(string titre, string auteur, int pages, bool bestseller, bool biographie)
: Livre(titre, auteur, pages, bestseller), biographie(biographie) {}
Roman::~Roman() {}

ostream& Roman::afficher(ostream& strm) const {
    Livre::afficher(strm);
    if (biographie)
        strm << "Ce roman est une biographie" << endl;
    else
        strm << "Ce roman n'est pas une biographie" << endl;
    return strm;
}

void testRoman() {
    Roman l1("titre", "auteur", 5, true, true);
    cout << boolalpha << true << " | test Roman" << endl;
    cout << boolalpha << bool(l1.calculer_prix() == 51.5) << " | test Roman::calculer_prix Romanbestseller" << endl;
    Roman l2("titre", "auteur", 5, false, false);
    cout << boolalpha << bool(l2.calculer_prix() == 1.5) << " | test Roman::calculer_prix" << endl;
}
// ==================================================================================================
class Policier : public Roman {
using Roman::Roman;
public:
    virtual ~Policier();
    double calculer_prix() const;
};
Policier::~Policier() {}
double Policier::calculer_prix() const {
    return max(Livre::calculer_prix() - 10, 1.0);
}

void testPolicier() {
    Policier l1("titre", "auteur", 5, true, true);
    cout << boolalpha << true << " | test Policier" << endl;
    cout << boolalpha << bool(l1.calculer_prix() == 41.5) << " | test Policier::calculer_prix bestseller" << endl;
    Policier l2("titre", "auteur", 5, false, false);
    cout << boolalpha << bool(l2.calculer_prix() == 1) << " | test Policier::calculer_prix" << endl;
}
// ==================================================================================================
class BeauLivre : public Livre {
using Livre::Livre;
public:
    virtual ~BeauLivre();
    double calculer_prix() const;
};
BeauLivre::~BeauLivre() {}
double BeauLivre::calculer_prix() const {
    return Livre::calculer_prix() + 30;
}

void testBeauLivre() {
    BeauLivre l1("titre", "auteur", 5, true);
    cout << boolalpha << true << " | test BeauLivre" << endl;
    cout << boolalpha << bool(l1.calculer_prix() == 81.5) << " | test BeauLivre::calculer_prix bestseller" << endl;
    BeauLivre l2("titre", "auteur", 5, false);
    cout << boolalpha << bool(l2.calculer_prix() == 31.5) << " | test BeauLivre::calculer_prix" << endl;
}
// ==================================================================================================
typedef unique_ptr<Livre> Livre_ptr;

class Librairie {
private:
    vector<Livre_ptr> livres;
public:
    void ajouter_livre(Livre*);
    ostream& afficher(ostream& strm) const;
    void vider_stock();
};
void Librairie::ajouter_livre(Livre* livre) {
    livres.push_back(Livre_ptr(livre));
}
void Librairie::vider_stock() {
    while (not livres.empty())
        livres.pop_back();
}

ostream& Librairie::afficher(ostream& strm) const {
    for (auto& l : livres) {
        l->afficher(strm);
        strm << endl;
    }
    return strm;
}

void testLibrairie() {
    Librairie l;
    l.ajouter_livre(new Policier("Le chien des Baskerville", "A.C.Doyle", 221, false, false));
    l.ajouter_livre(new Policier("Le Parrain ", "A.Cuso", 367, true, false));
    l.ajouter_livre(new Roman("Le baron perché", "I. Calvino", 283, false, false));
    l.ajouter_livre(new Roman ("Mémoires de Géronimo", "S.M. Barrett", 173, false, true));
    l.ajouter_livre(new BeauLivre ("Fleuves d'Europe", "C. Osborne", 150, false));
    l.afficher(cout);
    l.vider_stock();
}
// ==================================================================================================
void test() {
    testLivre();
    cout << endl;
    testRoman();
    cout << endl;
    testPolicier();
    cout << endl;
    testBeauLivre();
    cout << endl;
    testLibrairie();
}

int main() {
    test();
    return 0;
}