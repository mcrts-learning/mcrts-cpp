#include <iostream>
using namespace std;

class Apero {
    public:
        Apero() {
            cout << "L'heure de l'apéro a sonné !" << endl;
        }

        void bis() {
            cout << "Encore une ?" << endl;
        }

        ~Apero() {
            cout << "À table !" << endl;
        }
};

int main() {
    Apero bic;
    cout << "Super !" << endl;
    bic.bis();
    cout << "Non merci." << endl;
    return 0;
}


/* 
L'heure de l'apéro a sonné !
Super !
Encore une ?
Non merci.
À table !
*/