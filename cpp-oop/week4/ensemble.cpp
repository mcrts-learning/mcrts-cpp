#include <iostream>
#include <vector>
using namespace std;


int pgcd(int a, int b) {
    int u_(1), u(0);
    int v_(0), v(1);
    int x(a);
    int y(b);

    while (y != 1) {
        int q(x / y);
        int r(x % y);
        int u_next(u_ - u * q);
        int v_next(v_ - v * q);

        x = y;
        y = r;
        u_ = u;
        u = u_next;
        v_ = v;
        v = v_next;
    }
    return (u + b) % b;
}


// --------------------------------------------------------------------

class EnsembleFini {
    protected:
        int p;
    
    public:
        EnsembleFini(int p): p(p) {}
};

//=====================================================================

class Groupe: public EnsembleFini{
    using EnsembleFini::EnsembleFini;
    public:
        unsigned int add(unsigned int a, unsigned int b) {
            return (a + b) % p;
        }
};

//=====================================================================

class Anneau: public Groupe{
    using Groupe::Groupe;
    public:
        unsigned int mult(unsigned int a, unsigned int b) {
            return (a * b) % p;
        }
};

//=====================================================================

class Corps: public Anneau{
    using Anneau::Anneau;
    public:
        unsigned int inv(unsigned int x) {
            if (x != 0)
                return pgcd(x, p);
            else
                return 0;
        }

        unsigned int div(unsigned int x) {
            return x * inv(x);
        }
};

//=====================================================================

int main() {
    Corps k(5);
    cout << "0 + 1 = " << k.add(0, 1) << endl;
    cout << "3 + 3 = " << k.add(3, 3) << endl;
    cout << "3 * 2 = " << k.mult(3, 2) << endl;
    cout << "1 / 2 = " << k.inv(2) << endl;
    cout << "3 * 4 = " << k.mult(3, 4) << endl;

    return 0;
}