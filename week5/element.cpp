#include <iostream>
#include <vector>
using namespace std;

vector<int> elements_en_indice(vector<int> tab) {
    vector<int> newtab(tab.size() / 2);
    for (size_t i(0); i < tab.size(); i += 2) {
        newtab[tab[i+1]] = tab[i];
    }
    return newtab;
}

void affiche_vector(const vector<int>& u) {
    cout << "[ ";
    for (auto x : u) {
        cout << x << " ";
    }
    cout << "]" << endl;
}

int main() {
    vector<int> tab({4, 2, 8, 0, 7, 1});
    affiche_vector(elements_en_indice(tab));

    return 0;
}