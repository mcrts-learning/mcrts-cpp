#include <iostream>
#include <string>
using namespace std;

class Fleur {
    private:
        string variete;
        string color;

    public:
        Fleur(string variete, string color)
        : variete(variete), color(color) {
            cout << variete << " fraichement cueillie" << endl;
        }

        Fleur(Fleur const& fleur)
        : variete(fleur.variete), color(fleur.color) {
            cout << "Fragile corolle taillée" << endl;
        }

        void eclore() {
            cout << "veine de " << color << endl;
        }

        ~Fleur() {
            cout << "qu'un simple souffle..." << endl;
        }
};

int main () {
    Fleur f1("Violette", "bleu");
    Fleur f2(f1);
    cout << "dans un cristal ";
    f2.eclore();
    cout << "Donne un poème un peu fleur bleue" << endl
    << "ne laissant plus ";
    return 0;
}
/* 
Violette fraichement cueillie
Fragile corolle taillée
dans un cristal veine de bleu
Donne un poème un peu fleur bleue
ne laissant plus qu'un simple souffle...
qu'un simple souffle...
 */