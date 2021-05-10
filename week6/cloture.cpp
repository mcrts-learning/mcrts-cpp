#include <iostream>
#include <vector>
#include <array>
using namespace std;

/*******************************************
 * Complétez le programme à partir d'ici.
 *******************************************/
typedef vector<vector<int>> Carte;
const string carte_not_convexe("Votre carte du terrain n'est pas convexe par lignes :");
const string carte_not_binary("Votre carte du terrain ne contient pas que des 0 et des 1.");
const string is_not_convexe_pos0("bord extérieur entrant trouvé en position [");
const string is_not_convexe_pos1("][");
const string is_not_convexe_pos2("]");

struct Position{
  size_t i;
  size_t j;
};

bool binaire(Carte const& carte);
void affiche(Carte const& carte);
bool verifie_et_modifie(Carte& carte);
double longueur_cloture(Carte const& carte, double echelle);
void ajoute_unique(vector<int>& ensemble, int valeur);
bool convexite_lignes(Carte& carte, vector<int> const& labels_bords);
bool convexite_lignes(Carte& carte);
void marque_composantes(Carte& carte);


bool binaire(Carte const& carte) {
  bool result(true);
  for (auto row : carte) {
    for (auto cell : row) {
      if (cell != 0 and cell != 1) {
        result = false;
        break;
      }
    }
    if (!result) {
      break;
    }
  }
  return result;
}
void affiche(Carte const& carte) {
  for (auto row : carte) {
    for (auto cell : row) {
      cout << cell;
    }
    cout << endl;
  }
  cout << endl << "----" << endl;
}
bool verifie_et_modifie(Carte& carte) {
  if (!binaire(carte)) {
    cout << carte_not_binary << endl;
    return false;
  } else if (!convexite_lignes(carte)){
    return false;
 } else {
    return true;
  }
}

double longueur_cloture(Carte const& carte, double echelle=2.5) {
  double unit(0);
  /* add number of top fences on first row */
  for (auto cell : carte[0]) {
    if (cell == 1) {
      unit += 1;
    }
  }
  /* add number of bottom fences on last row */
  for (auto cell : carte[carte.size() - 1]) {
    if (cell == 1) {
      unit += 1;
    }
  }
  /* add 2 fences per row */
  unit += 2*carte.size();
  for (size_t i(0); i < carte.size(); i++) {
    for (size_t j(0); j < carte[i].size(); j++) {
      /* compute number of top fences */
      if (carte[i][j] == 0 and i > 0 and carte[i-1][j] == 1) {
        unit += 1;
      }
      /* compute number of bottom fences */
      if (i < carte.size()-1) {
        if (carte[i][j] == 0 and carte[i+1][j] == 1) {
          unit += 1;
        }
      }
    }
  }
  return unit * echelle;
}

bool isin(vector<int> row, int value) {
  for (auto x : row) {
    if (x == value) {
      return true;
    }
  }
  return false;
}

void ajoute_unique(vector<int>& ensemble, int valeur) {
  if (!isin(ensemble, valeur)) {
    ensemble.push_back(valeur);
  }
}

array<size_t, 2> get_boundaries(vector<int> row) {
  size_t left_index(row.size() - 1);
  size_t right_index(0);
  for (size_t i(0); i < row.size(); i++) {
    if (i < row.size()) {
      if (row[i] == 1 and i <= left_index) {
        left_index = i;
      }
      if (row[i] == 1 and i >= right_index) {
        right_index = i;
      }
    }
  }
  return array<size_t, 2>({left_index, right_index});
}

bool convexite_lignes(Carte& carte, vector<int> const& labels_bords) {
  for (size_t i(0); i < carte.size(); i++) {
    vector<int> row(carte[i]);
    array<size_t, 2> boundaries(get_boundaries(row));
    size_t left_index(boundaries[0]);
    size_t right_index(boundaries[1]);
    for (size_t j(left_index + 1); j < right_index; j++) {
      if (row[j] != 1 and isin(labels_bords, row[j])) {
        cout << carte_not_convexe << endl;
        cout << is_not_convexe_pos0 << i
             << is_not_convexe_pos1 << j
             << is_not_convexe_pos2 << endl;
        return false;
      }
    }
  }
  return true;
}

bool convexite_lignes(Carte& carte) {
  marque_composantes(carte);
  vector<int> outside_composantes;
  for (size_t i(0); i < carte.size(); i++) {
    for (size_t j(0); j < carte[i].size(); j++) {
      if (i == 0 or i == carte.size() - 1 or j == 0 or j == carte[i].size() - 1) {
        if (carte[i][j] != 1) {
          ajoute_unique(outside_composantes, carte[i][j]);
        }
      }
    }
  }
  bool result(convexite_lignes(carte, outside_composantes));
  for (auto& row : carte) {
    for (auto& cell : row) {
      if (cell != 1 and isin(outside_composantes, cell)) {
        cell = 0;
      } else if (cell != 1) {
        cell = 1;
      }
    }
  }
  return result;
}

void marque_composantes(Carte& carte) {
  vector<Position> positions;
  int composante(1);

  for (size_t i(0); i < carte.size(); i++) {
    for (size_t j(0); j < carte[i].size(); j++) {
      if (carte[i][j] == 0) {
        composante += 1;
        vector<Position> positions({Position({i, j})});
        while (!positions.empty()) {
          Position pos(positions.back());
          positions.pop_back();
          if (carte[pos.i][pos.j] == 0) {
            carte[pos.i][pos.j] = composante;
            if (pos.i > 0) {
              positions.push_back(Position({pos.i - 1, pos.j}));
            }
            if (pos.i < carte.size() - 1) {
              positions.push_back(Position({pos.i + 1, pos.j}));
            }
            if (pos.j > 0) {
              positions.push_back(Position({pos.i, pos.j - 1}));
            }
            if (pos.j < carte[pos.i].size() - 1) {
              positions.push_back(Position({pos.i, pos.j +1 }));
            }
          }
        }
      }
    }
  }
}
/*
void test(){
  bool res(false);
  vector<int> v1({0, 1, 2});
  vector<int> v1_res({0, 1, 2});
  ajoute_unique(v1, 2);
  cout << boolalpha << (v1 == v1_res) << " | ajoute_unique {0, 1, 2}, 2 == {0, 1, 2}" << endl;

  vector<int> v2;
  vector<int> v2_res({2});
  ajoute_unique(v2, 2);
  cout << boolalpha << (v2 == v2_res) << " | ajoute_unique {}, 2 == {2}" << endl;

  vector<int> v3({1});
  vector<int> v3_res({1, 2});
  ajoute_unique(v3, 2);
  cout << boolalpha << (v3 == v3_res) << " | ajoute_unique {1}, 2 == {1, 2}" << endl;

  vector<int> v4({2});
  vector<int> v4_res({2, 1});
  ajoute_unique(v4, 1);
  cout << boolalpha << (v4 == v4_res) << " | ajoute_unique {2}, 1 == {2, 1}" << endl;

  Carte c1 = {
    {0,1,1,1,0},
    {0,1,0,1,0},
    {0,1,1,1,0},
  };
  Carte c1_mod = {
    {0,1,1,1,0},
    {0,1,1,1,0},
    {0,1,1,1,0},
  };
  cout << boolalpha << (binaire(c1) == true) << " | binaire c1 == true" << endl;
  cout << boolalpha << (verifie_et_modifie(c1) == true) << " | verifie_et_modifie c1 == true" << endl;
  cout << boolalpha << (c1 == c1_mod) << " | verifie_et_modifie c1 == c1_mod" << endl;
  cout << boolalpha << (longueur_cloture(c1_mod) == 30.0) << " | longueur_cloture c1 == 30.0" << endl;
  res = convexite_lignes(c1);
  cout << boolalpha << (res == true) << " | convexite_lignes c1 == true" << endl;

  Carte c2 = {
    {1,1,1},
    {0,0,1},
    {1,1,1},
  };
  Carte c2_mod = {
    {1,1,1},
    {0,0,1},
    {1,1,1},
  };
  cout << boolalpha << (binaire(c2) == true) << " | binaire c2 == true" << endl;
  cout << boolalpha << (verifie_et_modifie(c2) == true) << " | verifie_et_modifie c2 == true" << endl;
  cout << boolalpha << (c2 == c2_mod) << " | verifie_et_modifie c2 == c2" << endl;
  cout << boolalpha << (longueur_cloture(c2) == 40.0) << " | longueur_cloture c2 == 40.0" << endl;
  res = convexite_lignes(c2);
  cout << boolalpha << (res == true) << " | convexite_lignes c2 == true" << endl;

  Carte c3 = {{1}};
  cout << boolalpha << (binaire(c3) == true) << " | binaire c3 == true" << endl;
  cout << boolalpha << (longueur_cloture(c3) == 10.0) << " | longueur_cloture c3 == 10.0" << endl;
  res = convexite_lignes(c3);
  cout << boolalpha << (res == true) << " | convexite_lignes c3 == true" << endl;

  Carte c4 = {{1,1}, {1,1}};
  cout << boolalpha << (binaire(c4) == true) << " | binaire c4 == true" << endl;
  cout << boolalpha << (longueur_cloture(c4) == 20.0) << " | longueur_cloture c4 == 20.0" << endl;
  cout << boolalpha << (longueur_cloture(c4, 5) == 40.0) << " | longueur_cloture c4, 5 == 40.0" << endl;
  cout << boolalpha << (longueur_cloture(c4, 1) == 8.0) << " | longueur_cloture c4, 1 == 8.0" << endl;
  res = convexite_lignes(c4);
  cout << boolalpha << (res == true) << " | convexite_lignes c4 == true" << endl;

  Carte c5 = {{5,1}};
  cout << boolalpha << (binaire(c5) == false) << " | binaire c5 == false" << endl;
  cout << boolalpha << (verifie_et_modifie(c5) == false) << " | verifie_et_modifie c5 == false" << endl;
  res = convexite_lignes(c5);
  cout << boolalpha << (res == true) << " | convexite_lignes c5 == true" << endl;

  Carte c6 = {
    {1,0,1},
    {1,0,1},
    {1,1,1},
  };
  cout << boolalpha << (binaire(c6) == true) << " | binaire c6 == true" << endl;
  cout << boolalpha << (verifie_et_modifie(c6) == false) << " | verifie_et_modifie c6 == false" << endl;


  Carte carte = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  };
  res = convexite_lignes(carte);
  cout << boolalpha << (res == false) << " | convexite_lignes carte == false" << endl;
}
*/
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  Carte carte = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  };

  cout << "Carte au départ :" << endl;
  affiche(carte);
  if (verifie_et_modifie(carte)) {
    cout << "Carte après modification :" << endl;
    affiche(carte);
    cout << "Il vous faut " << longueur_cloture(carte)
         << " mètres de clôture pour votre terrain."
         << endl;
  }
  
  return 0;
}
