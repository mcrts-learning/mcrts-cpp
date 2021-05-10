#include <iostream>
#include <array>
#include <vector>
using namespace std;

constexpr size_t DIM(10);

void affiche(array<array<bool, DIM>, DIM> grille);

bool remplitGrille(array<array<bool, DIM>, DIM>& grille,
                   unsigned int ligne,
                   unsigned int colonne,
                   char direction,
                   unsigned int longueur);

array<array<bool, DIM>, DIM> new_grille(bool value);

//

void affiche(array<array<bool, DIM>, DIM> grille) {
    cout << "  " << "0123456789" << endl;
    size_t i(0);
    for (auto row : grille) {
        cout << i++ << "|";
        for (auto x : row) {
            if (!x)
                cout << " ";
            else
                cout << "X";
        }
        cout << "|" << endl;
    }
}

array<array<bool, DIM>, DIM> new_grille(bool value) {
    array<bool, DIM> row;
    std::fill(row.begin(), row.end(), value);

    array<array<bool, DIM>, DIM> grille;
    std::fill(grille.begin(), grille.end(), row);
    return grille;
}

bool remplitGrille(array<array<bool, DIM>, DIM>& grille,
                   unsigned int ligne,
                   unsigned int colonne,
                   char direction,
                   unsigned int longueur) {          
    vector<bool> arr(longueur);

    if (direction == 'E' and colonne+longueur > DIM) {
        return false;
    } else if (direction == 'O' and colonne+1 < longueur) {
        return false;
    } else if (direction == 'S' and ligne+longueur > DIM) {
        return false;
    } else if (direction == 'N' and ligne+1 < longueur ) {
        return false;
    }

    if (direction == 'E') {
        for (size_t index(0); index < arr.size(); index++) {
            arr[index] = grille[ligne][colonne+index];
        }
    } else if (direction == 'O') {
        for (size_t index(0); index < arr.size(); index++) {
            arr[index] = grille[ligne][colonne-longueur+1+index];
        }
    } else if (direction == 'S') {
        for (size_t index(0); index < arr.size(); index++) {
            arr[index] = grille[ligne+index][colonne];
        }
    } else if (direction == 'N') {
        for (size_t index(0); index < arr.size(); index++) {
            arr[index] = grille[ligne-longueur+1+index][colonne];
        }
    }


    bool res(true);
    for (auto x : arr) {
        if (x) {
            res = false;
            break;
        }
    }

    if (res) {
        if (direction == 'E') {
            for (size_t index(0); index < longueur; index++) {
                grille[ligne][colonne+index] = true;
            }
        } else if (direction == 'O') {
            for (size_t index(0); index < longueur; index++) {
                grille[ligne][colonne-longueur+1+index] = true;
            }
        } else if (direction == 'S') {
            for (size_t index(0); index < longueur; index++) {
                grille[ligne+index][colonne] = true;
            }
        } else if (direction == 'N') {
            for (size_t index(0); index < longueur; index++) {
                grille[ligne-longueur+1+index][colonne] = true;
            }
        }
    }

    return res;
}

int main() {
    array<array<bool, DIM>, DIM> grille(new_grille(false));
    affiche(grille);
    
    cout << endl;
    bool res;
    unsigned int row(2);
    unsigned int col(8);
    char dir('E');
    unsigned int size(2);
    res = remplitGrille(grille, row, col, dir, size);
    cout << "  row : " << row << endl
         << "  col : " << col << endl
         << "  direction : " << dir << endl
         << "  taille : " << size << endl
         << "  success : " << boolalpha << res << endl;

    cout << endl;
    row = 0;
    col = 8;
    dir = 'S';
    size = 5;
    res = remplitGrille(grille, row, col, dir, size);
    cout << "  row : " << row << endl
         << "  col : " << col << endl
         << "  direction : " << dir << endl
         << "  taille : " << size << endl
         << "  success : " << boolalpha << res << endl;

    cout << endl;
    row = 0;
    col = 9;
    dir = 'O';
    size = 5;
    res = remplitGrille(grille, row, col, dir, size);
    cout << "  row : " << row << endl
         << "  col : " << col << endl
         << "  direction : " << dir << endl
         << "  taille : " << size << endl
         << "  success : " << boolalpha << res << endl;

    cout << endl;
    row = 0;
    col = 0;
    dir = 'S';
    size = 5;
    res = remplitGrille(grille, row, col, dir, size);
    cout << "  row : " << row << endl
         << "  col : " << col << endl
         << "  direction : " << dir << endl
         << "  taille : " << size << endl
         << "  success : " << boolalpha << res << endl;

    cout << endl;
    row = 7;
    col = 2;
    dir = 'S';
    size = 4;
    res = remplitGrille(grille, row, col, dir, size);
    cout << "  row : " << row << endl
         << "  col : " << col << endl
         << "  direction : " << dir << endl
         << "  taille : " << size << endl
         << "  success : " << boolalpha << res << endl;

    cout << endl;
    affiche(grille);
    return 0;
}