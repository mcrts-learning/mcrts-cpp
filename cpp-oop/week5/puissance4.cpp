#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <memory>
using namespace std;

enum Couleur {jaune, rouge, vide};

class Jeu {
    private:
        vector<vector<Couleur>> table;
    
    public:
        Jeu(unsigned int size=8)
        : table({size, vector<Couleur>({size, vide})}) {}

        bool jouer(unsigned int col, Couleur couleur) {
            return false;
        }

        Couleur gagnant() const {
            return vide;
        }
};

class Joueur{
    protected:
        string nom;
        Couleur couleur;

    public:
        Joueur(string nom, Couleur couleur)
        : nom(nom), couleur(couleur) {}
        Joueur(Joueur const& joueur)
        : nom(nom), couleur(couleur) {}
        virtual void jouer(Jeu& jeu) const = 0;
        virtual unique_ptr<Joueur> copie() const = 0;
};

class Partie {
    private:
        array<unique_ptr<Joueur>, 2> joueurs;
        Jeu jeu;
    
    public:
        Partie(Joueur const& j1, Joueur const& j2, unsigned int size=8)
        : jeu(size) {
            joueurs = {j1.copie(), j2.copie()}; 
        }
};

class JoueurHumain : public Joueur {
    using Joueur::Joueur;

    public:
        void jouer(Jeu& jeu) const {
            cout << "joueur humain joue" << endl;
        }
        unique_ptr<Joueur> copie() const {
            return unique_ptr<Joueur>(*this);
        }
};

class JoueurComputer : public Joueur {
    using Joueur::Joueur;

    public:
        void jouer(Jeu& jeu) const {
            cout << "joueur computer joue" << endl;
        }
        unique_ptr<Joueur> copie() const {
            return unique_ptr<Joueur>(*this);
        }
};

int main() {

    JoueurHumain j1("Martin", rouge);
    JoueurComputer j2("Computer", jaune);
    Partie partie(j1, j2, 8);

    return 0;
}

