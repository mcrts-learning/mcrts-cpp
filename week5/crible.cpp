#include <iostream>
#include <vector>
using namespace std;

void affiche_vector(const vector<int>& u) {
    cout << "[ ";
    for (auto x : u) {
        cout << x << " ";
    }
    cout << "]" << endl;
}

int main() {
    vector<bool> supprimes(1000, false);
    for (size_t i(0); i < supprimes.size(); i++) {
        if (i == 0 or i == 1) {
            supprimes[i] = true;
        } else if (!supprimes[i]) {
            for (size_t v(2*i); v < supprimes.size(); v+=i) {
                supprimes[v] = true;
            }
        }
    }
    for (size_t i(0); i < supprimes.size(); i++) {
        if (!supprimes[i]) {
            cout << i << endl;
        }
    }
    return 0;
}