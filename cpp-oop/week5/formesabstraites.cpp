#include <iostream>
#include <cmath>
#include <string>

using namespace std;

class Forme {
    public:
        virtual void description() const {
            cout << "Ceci est une forme !" << endl;
        }
        virtual double aire() const = 0;
};

class Cercle: public Forme {
    private:
        double rayon;
    public:
        Cercle(double rayon=5)
        : rayon(rayon) {}

        void description() const override {
            cout << "Ceci est un cercle (rayon=" << rayon << ") !"<< endl;
        }

        double aire() const {
            return M_PI * 2 * rayon;
        };
};

class Triangle: public Forme {
    private:
        double base, hauteur;
    public:
        Triangle(double base=5, double hauteur=5)
        : base(base), hauteur(hauteur) {}

        void description() const override {
            cout << "Ceci est un triangle (base=" << base << ", hauteur=" << hauteur << ") !" << endl;
        }

        double aire() const {
            return base * hauteur / 2;
        };
};

void affichageDesc(Forme& f) {
    f.description();
    cout << "    Aire = " << f.aire() << endl;
}

int main() {
    Cercle c(5);
    Triangle t(5, 10);
    affichageDesc(c);
    affichageDesc(t);

    return 0;
}