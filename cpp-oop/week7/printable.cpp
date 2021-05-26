#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// ===========================================================
class Printable {
public:
    virtual const string printString() const = 0;
};

ostream& operator<<(ostream& ostr, const Printable& instance)
    { return (ostr << instance.printString()); }

// ===========================================================

class Employee: public Printable {
private:
    string nom;
    int anciennete;
    double salaire;
public:
    Employee(string nom, int anciennete, double salaire)
        : nom(nom), anciennete(anciennete), salaire(salaire) {}
    double getPrime() const { return salaire * 0.02 * anciennete; }
    double getFullSalary() const { return salaire + getPrime(); }
    const string printString() const {
        stringstream msg;
        msg << nom << " employé depuis " << anciennete << " années, reçoit cette année un salaire de " << getFullSalary() << " €.";
        return msg.str();
    };
};


class Livre: public Printable {
private:
    string nom;
    bool bestseller;
    double base_price;
public:
    Livre(string nom, bool bestseller, double base_price)
        : nom(nom), bestseller(bestseller), base_price(base_price) {}
    double getPrice() const { return base_price * (1 + 0.25 * bestseller); }
    const string printString() const {
        stringstream msg;
        if (bestseller)
            msg << nom << " un bestseller de " <<  getPrice() << " €.";
        else
            msg << nom << " un livre de " <<  getPrice() << " €.";

        return msg.str();
    };
};

int main() {
    Employee e("Lucas", 5, 2800);
    Livre l1("La chute", true, 20);
    Livre l2("Picsou magasine", false, 20);
    cout << e << endl;
    cout << l1 << endl;
    cout << l2 << endl;

}