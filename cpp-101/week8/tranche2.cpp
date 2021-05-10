#include <iostream>
#include <vector>
#include <memory>
using namespace std;

typedef size_t Position;
typedef vector<int> Sequence;

struct SousSequence {
    Sequence& sequence;
    Position debut;
    Position fin;
    int somme;
};

int evaluate(Sequence const& sequence, size_t debut, size_t fin) {
    int somme(0);
    for (size_t i(debut); i <= fin; i++) {
        somme += sequence[i];
    }
    return somme;
}

SousSequence greedy (Sequence& sequence) {
    int best_somme(sequence[0]);
    size_t best_debut(0);
    size_t best_fin(0);
    for (size_t debut(0); debut < sequence.size(); debut++) {
        for (size_t fin(debut); fin < sequence.size(); fin++) {
            int somme = evaluate(sequence, debut, fin);
            if (somme > best_somme) {
                best_somme = somme;
                best_debut = debut;
                best_fin = fin;
            }
        }

    }
    return SousSequence({sequence, best_debut, best_fin, best_somme});
}

SousSequence greedy2 (Sequence& sequence) {
    int best_somme(sequence[0]);
    size_t best_debut(0);
    size_t best_fin(0);
    for (size_t debut(0); debut < sequence.size(); debut++) {
        int somme(0);
        for (size_t fin(debut); fin < sequence.size(); fin++) {
            somme += sequence[fin];
            if (somme > best_somme) {
                best_somme = somme;
                best_debut = debut;
                best_fin = fin;
            }
        }

    }
    return SousSequence({sequence, best_debut, best_fin, best_somme});
}

SousSequence linear (Sequence& sequence) {
    int best_somme(sequence[0]);
    size_t debut(0);
    size_t best_fin(0);
    int somme(0);
    for (size_t fin(0); fin < sequence.size(); fin++) {
        somme += sequence[fin];
        if (somme > best_somme) {
            best_somme = somme;
            best_fin = fin;
        }
        if (somme <= 0) {
            debut = fin + 1;
            somme = 0;
        }
    }
    return SousSequence({sequence, debut, best_fin, best_somme});
}


void affiche(Sequence const& sequence) {
    cout << "<Sequence {";
    for (size_t i(0); i < sequence.size() - 1; i++) {
        cout << sequence[i] << ", ";
    }
    cout << sequence.back() << "}>" << endl;
}

void affiche(SousSequence const& sous_sequence) {
    cout << "<SousSequence debut=" << sous_sequence.debut
         << " fin=" << sous_sequence.fin
         << " somme=" << sous_sequence.somme
         << ">" << endl;

    cout << "<Sequence {";
    for (size_t i(sous_sequence.debut); i < sous_sequence.fin; i++) {
        cout << sous_sequence.sequence[i] << ", ";
    }
    cout << sous_sequence.sequence[sous_sequence.fin] << "}>" << endl;
}

int main() {
    vector<Sequence> sequences({
        {11, 13, -4, 3, -26, 7, -13, 25, -2, 17, 5, -8, 1},
        {-3, -4, -1, -2, -3},
        {-1, -4, -3, -2, -3},
        {3, -1, -1, -1, 5},
        {3, 4, 1, 2, -3},
        {3, 4, 1, 2, 3},
        {-5, -4, 1, 1, 1},
    });
    for (auto sequence : sequences) {
        affiche(sequence);
        SousSequence res(linear(sequence));
        affiche(res);
        cout << endl;
    }


    return 0;
}