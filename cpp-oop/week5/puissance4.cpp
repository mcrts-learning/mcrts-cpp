#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <memory>
using namespace std;

enum Couleur {vide=0, jaune, rouge};

string colorCode(Couleur c) {
    if (c == jaune)
        return "j";
    else if (c == rouge)
        return "r";
    else
        return " ";
} 

class Vector2D {
    private:
        vector<vector<Couleur>> vector2d;
        const size_t size;
    
    public:
        Vector2D(size_t size)
        : vector2d({size, vector<Couleur>(size, vide)}), size(size) {}

        const vector<Couleur> getRow(size_t idx) const {
            vector<Couleur> row;
            for (auto c : vector2d)
                row.push_back(c[idx]);
            return row;
        }

        const vector<Couleur> getLDiag(size_t idx) const {
            vector<Couleur> row;
            size_t x(0);
            size_t y(idx);
            for (size_t i(0); i <= idx; i++) {
                row.push_back(vector2d[x][y]);
                x++;
                y--;
            }
            return row;
        }

        const vector<Couleur> getRDiag(size_t idx) const {
            vector<Couleur> row;
            size_t x(0);
            size_t y(size - idx);
            for (size_t i(0); i <= idx; i++) {
                row.push_back(vector2d[x][y]);
                x++;
                y++;
            }
            return row;
        }

        const vector<Couleur>& getColumn(size_t idx) const {
            return vector2d[idx];
        }

        const vector<vector<Couleur>> getAllRows() const {
            vector<vector<Couleur>> rows;
            for (size_t x(0); x < size; x++) {
                rows.push_back(getColumn(x));
                rows.push_back(getRDiag(x));
                rows.push_back(getLDiag(x));
                rows.push_back(getRow(x));
            }
            return rows;
        }

        Couleur getCell(size_t col, size_t row) const {
            if (col < size and row < size)
                return vector2d[col][row];
            else
                return vide;
        }

        size_t getSize() const {
            return size;
        }

        bool add(size_t col, Couleur couleur) {
            for (auto& c : vector2d[col]) {
                if (c == vide) {
                    c = couleur;
                    return true;
                }
            }
            return false;
        }
};

class Jeu {
    private:
        Vector2D grid;
    
    public:
        Jeu(size_t size=8)
        : grid(size) {}
        
        const size_t getSize() const { return grid.getSize(); }

        static bool isConnect4(vector<Couleur> row, Couleur couleur) {
            unsigned int count(0);
            for (auto c : row) {
                if (c == couleur)
                    count++;
                else
                    count = 0;
                
                if (count >= 4)
                    return true;
            }
            return false;
        }

        bool jouer(size_t col, Couleur couleur) {
            return grid.add(col, couleur);
        }

        Couleur gagnant() const {
            for (auto row : grid.getAllRows()) {
                if (isConnect4(row, jaune))
                    return jaune;
                if (isConnect4(row, rouge))
                    return rouge;
            }
            return vide;
        }

        ostream& print(ostream& strm) const {
            strm << string(getSize() + 2, '=') << endl;
            for (size_t y(getSize()); y > 0; y--) {
                strm << " ";
                for (auto c : grid.getRow(y-1))
                    strm << colorCode(c);
                strm << " " << endl;
            }
            strm << " ";
            for (size_t x(0); x < getSize(); x++)
                strm << x;
            strm << " " << endl;
            return strm;
        }
};

ostream& operator<<(ostream& strm, Jeu const& inst) {
    inst.print(strm);
    return strm;
}

class Joueur{
    protected:
        string nom;
        Couleur couleur;

    public:
        Joueur(string nom, Couleur couleur)
        : nom(nom), couleur(couleur) {}
        Joueur(Joueur const& other)
        : nom(other.nom), couleur(other.couleur) {}

        virtual void jouer(Jeu& jeu) const = 0;
        virtual unique_ptr<Joueur> copie() const = 0;
        string getNom() const {return nom;}
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

        ostream& print(ostream& strm) const {
            strm << jeu;
            return strm;
        }

        void lancer() {
            for(size_t i(0); i < 31; i++) {
                joueurs[1]->jouer(jeu);
                if (jeu.gagnant()) {
                    cout << jeu << endl;
                    cout << "La partie est finie : " << joueurs[1]->getNom() << " gagne !" << endl;
                    break;
                }
                joueurs[0]->jouer(jeu);
                if (jeu.gagnant()) {
                    cout << jeu << endl;
                    cout << "La partie est finie : " << joueurs[0]->getNom() << " gagne !" << endl;
                    break;
                }
            }
        }
};

ostream& operator<<(ostream& strm, Partie const& inst) {
    inst.print(strm);
    return strm;
}


class JoueurHumain : public Joueur {
    using Joueur::Joueur;

    public:
        void jouer(Jeu& jeu) const {
            cout << "Tour du joueur " << nom << endl;
            cout << jeu << endl;

            unsigned int col;
            do {
                cout << "Choisir une colonne [0 - " << jeu.getSize() - 1 << "] : ";
                cin >> col;
            } while (col > jeu.getSize() or !jeu.jouer(col, couleur));


        }
        unique_ptr<Joueur> copie() const {
            return unique_ptr<Joueur>(new JoueurHumain(*this));
        }
};

class JoueurComputer : public Joueur {
    using Joueur::Joueur;

    public:
        void jouer(Jeu& jeu) const {
            cout << "joueur computer joue" << endl;
            for (size_t i(0); i < jeu.getSize(); i++) {
                if (jeu.jouer(i, couleur))
                    break;
            }
        }
        unique_ptr<Joueur> copie() const {
            return unique_ptr<Joueur>(new JoueurComputer(*this));
        }
};

int main() {
    JoueurHumain j1("Martin", rouge);
    JoueurComputer j2("Computer", jaune);
    Partie partie(j1, j2);

    partie.lancer();
    return 0;
}

