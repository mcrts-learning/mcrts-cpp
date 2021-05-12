#include <iostream>
#include <vector>
using namespace std;


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
            return x;
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