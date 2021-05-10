#include <iostream>
#include <vector>
using namespace std;

typedef size_t Degre;
struct DivisionEuclidienne;

class Polynome {
    public:
        Polynome(double coef = 0.0, Degre degre = 0);

        Degre degre() const { return p.size()-1; }
        double top() const { return p[degre()]; }

        void affiche_coef(ostream& out, Degre puissance, bool signe = true) const;
        Polynome& operator*=(const Polynome& q);
        Polynome& operator*=(double);
    private:
        vector<double> p;
        friend const Polynome operator*(Polynome p, const Polynome& q);
        friend const Polynome operator/(Polynome p, const Polynome& q);
        friend const Polynome operator%(Polynome p, const Polynome& q);
        friend const Polynome operator+(Polynome p, const Polynome& q);
        friend const Polynome operator-(Polynome p, const Polynome& q);
        friend const bool operator==(Polynome p, const Polynome& q);
        friend const bool operator!=(Polynome p, const Polynome& q);

        void simplifie() {
            for (Degre i(degre()); i > 0; i--) {
                if (p[i] == 0)
                    p.pop_back();
                else
                    break;
            }
        }
        DivisionEuclidienne divise(const Polynome& p) const;
};

struct DivisionEuclidienne {
    const Polynome q;
    const Polynome r;
};

// opérateurs externes
const Polynome operator*(Polynome p, const Polynome& q);
const Polynome operator*(Polynome p, double x);
const Polynome operator*(double x, const Polynome& p);
const Polynome operator+(Polynome p, const Polynome& q);
const Polynome operator-(Polynome p, const Polynome& q);
const bool operator==(Polynome p, const Polynome& q);
const bool operator!=(Polynome p, const Polynome& q);
const Polynome operator/(Polynome p, const Polynome& q);
const Polynome operator%(Polynome p, const Polynome& q);
// ======================================================================
// définition des méthodes
// ----------------------------------------------------------------------
Polynome::Polynome(double coef, size_t deg)
: p(deg+1, 0.0) {
    p[deg] = coef;
}
// ----------------------------------------------------------------------
Polynome& Polynome::operator*=(const Polynome& q) {
/* On définit ici exceptionnellement l'opérateur interne avec
l'opérateur externe (au lieu de faire le contraire) car on aurait
de toutes façon besoin d'un polynôme supplémentaire pour
effectuer ce calcul.
*/
    return (*this = *this * q);
}
// ----------------------------------------------------------------------
Polynome& Polynome::operator*=(double x) {
    for (Degre i(0); i <= degre(); ++i)
        p[i] *= x;
    return *this;
}
// ======================================================================
// fonctions intermédiaires et opérateurs externes
// ----------------------------------------------------------------------
const Polynome operator*(Polynome p, double x) {
    return p *= x;
}
// ----------------------------------------------------------------------
const Polynome operator*(double x, const Polynome& p) {
    return Polynome(p) *= x;
}

// ----------------------------------------------------------------------
const Polynome operator*(Polynome p, const Polynome& q) {
    const Degre dp(p.degre());
    const Degre dq(q.degre());
    // Prépare la place pour le polynome résultat (de degre p.degre()+q.degre()).
    Polynome r(0.0, dp + dq);
    // fait le calcul
    for (Degre i(0); i <= dp; ++i)
        for (Degre j(0); j <= dq; ++j)
            r.p[i+j] += p.p[i] * q.p[j];
    // retourne le resultat
    return r;
}

const Polynome operator+(Polynome p, const Polynome& q) {
    const Degre dp(p.degre());
    const Degre dq(q.degre());
    const Degre d(max(dp, dq));
    Polynome r(0.0, d);
    for (Degre i(0); i <= dp; ++i) {
        r.p[i] = p.p[i];
    }
    for (Degre i(0); i <= dq; ++i) {
        r.p[i] += q.p[i];
    }
    r.simplifie();
    return r;
}
const Polynome operator-(Polynome p, const Polynome& q) {
    const Degre dp(p.degre());
    const Degre dq(q.degre());
    const Degre d(max(dp, dq));
    Polynome r(0.0, d);
    for (Degre i(0); i <= dp; ++i) {
        r.p[i] = p.p[i];
    }
    for (Degre i(0); i <= dq; ++i) {
        r.p[i] -= q.p[i];
    }
    r.simplifie();
    return r;
}
const bool operator==(Polynome p, const Polynome& q) {
    return (p.p == q.p);
}
const bool operator!=(Polynome p, const Polynome& q) {
    return !(p == q);
}
// ----------------------------------------------------------------------
void Polynome::affiche_coef(ostream& out, Degre puissance, bool signe) const{
double const c(p[puissance]);
    if (c != 0.0) {
        if (signe and (c > 0.0))
            out << "+";
        out << c;

        if (puissance > 1)
            out << "*X^" << puissance;
        else if (puissance == 1)
            out << "*X";
    } else if (degre() == 0) {
    // degré 0 : afficher quand même le 0 si rien d'autre
        out << 0;
    }
}
// ----------------------------------------------------------------------
ostream& operator<<(ostream& sortie, const Polynome& polynome) {
// plus haut degré : pas de signe + devant
    Degre i(polynome.degre());
    sortie << "(";
    polynome.affiche_coef(sortie, i, false);
    // degré de N à 0 : +a*X^i
    
    if (i > 0) {
        for (--i; i > 0; --i)
            polynome.affiche_coef(sortie, i);
        polynome.affiche_coef(sortie, 0);
    }
    sortie << ")";
    return sortie;
}
// ======================================================================

DivisionEuclidienne Polynome::divise(const Polynome& d) const{
    Polynome r(*this);
    Polynome q(0, 0);
    Polynome zero(0, 0);
    int delta(r.degre() - d.degre());
    while (delta >= 0 and r != zero) {
        double a(r.top() / d.top());
        Polynome pa(a, delta);
        q = q + pa;
        r = r - (pa * d);
        delta = r.degre() - d.degre();
    }
    DivisionEuclidienne res({q, r});
    return res;
}
const Polynome operator/(Polynome p, const Polynome& q) {
    DivisionEuclidienne res(p.divise(q));
    return res.q;
}
const Polynome operator%(Polynome p, const Polynome& q) {
    DivisionEuclidienne res(p.divise(q));
    return res.r;
}
// ======================================================================


int main() {
    Polynome p(3.2, 4);
    cout << "p=" << p << endl;
    Polynome q(1.1, 2), r;
    r = p * q;
    cout << p << " * " << q << " = " << r << endl;
    r *= 2.0;
    cout << p * q << " * 2 = " << r << endl;
    
    {
        Polynome p0(10.0, 3);
        Polynome p1(10.0, 3);
        cout << p0  << " + " << p1  << " = " << p0 + p1 << endl;
        cout << p0  << " - " << p1  << " = " << p0 - p1 << endl;
    }

    {
        Polynome p0(10.0, 0);
        Polynome p1(10.0, 0);
        Polynome p2(2.0, 2);
        Polynome p3(10.0, 1);
        Polynome p4(2.0, 0);
        cout << p0  << " == " << p1  << " : " << boolalpha << (p0 == p1) << endl;
        cout << p0  << " == " << p2  << " : " << boolalpha << (p0 == p2) << endl;
        cout << p0  << " == " << p3  << " : " << boolalpha << (p0 == p3) << endl;
        cout << p0  << " == " << p4  << " : " << boolalpha << (p0 == p4) << endl;
        cout << endl;
        cout << p0  << " != " << p1  << " : " << boolalpha << (p0 != p1) << endl;
        cout << p0  << " != " << p2  << " : " << boolalpha << (p0 != p2) << endl;
        cout << p0  << " != " << p3  << " : " << boolalpha << (p0 != p3) << endl;
        cout << p0  << " != " << p4  << " : " << boolalpha << (p0 != p4) << endl;

    }
    {
        Polynome p0(10.0, 0);
        Polynome p1(10.0, 1);
        Polynome p2(2.0, 2);
        Polynome p3(-10.0, 1);
        cout << p0  << " top " << p0.top() << endl;
        cout << p1  << " top " << p1.top() << endl;
        cout << p2  << " top " << p2.top() << endl;
        cout << p3  << " top " << p3.top() << endl;
    }
    {
        Polynome p0(10.0, 3);
        Polynome p1(2.0, 1);
        Polynome p2(3.0, 2);
        cout << p0 << " / " << (p1 + p2) << " = " << p0 / (p1 + p2) << endl;
        cout << p0 << " % " << (p1 + p2) << " = " << p0 % (p1 + p2) << endl;
    }
    return 0;
}
