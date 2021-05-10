#include <iostream>
#include <vector>
using namespace std;

typedef size_t Position;
typedef vector<int> Sequence;

struct SousSequence {
    Position debut;
    Position fin;
    int somme;
};

SousSequence evaluate(Sequence const& sequence, size_t debut, size_t fin) {
    int somme(0);
    for (size_t i(debut); i <= fin; i++) {
        somme += sequence[i];
    }
    return SousSequence({debut, fin, somme});
}

SousSequence greedy (Sequence const& sequence) {
    SousSequence result({0, 0, sequence[0]});
    for (size_t debut(0); debut < sequence.size(); debut++) {
        for (size_t fin(debut); fin < sequence.size(); fin++) {
            SousSequence ss = evaluate(sequence, debut, fin);
            if (result.somme < ss.somme) {
                result = ss;
            }
        }

    }
    return result;
}

SousSequence greedy2 (Sequence const& sequence) {
    SousSequence result({0, 0, sequence[0]});
    for (size_t debut(0); debut < sequence.size(); debut++) {
        int somme(0);
        for (size_t fin(debut); fin < sequence.size(); fin++) {
            somme += sequence[fin];
            SousSequence ss({debut, fin, somme});
            if (result.somme < ss.somme) {
                result = ss;
            }
        }

    }
    return result;
}

SousSequence linear (Sequence const& sequence) {
    SousSequence result({0, 0, sequence[0]});
    size_t debut(0);
    int somme(0);
    for (size_t fin(0); fin < sequence.size(); fin++) {
        somme += sequence[fin];
        SousSequence ss({debut, fin, somme});
        if (ss.somme > result.somme) {
            result = ss;
        }
        if (ss.somme <= 0) {
            debut = fin + 1;
            somme = 0;
        }
    }
    return result;
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
}

void affiche(Sequence const& sequence, SousSequence const& sous_sequence) {
    affiche(sous_sequence);
    cout << "<Sequence {";
    for (size_t i(sous_sequence.debut); i < sous_sequence.fin; i++) {
        cout << sequence[i] << ", ";
    }
    cout << sequence[sous_sequence.fin] << "}>" << endl;
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
        SousSequence res(greedy(sequence));
        affiche(sequence, res);
        cout << endl;
    }


    return 0;
}