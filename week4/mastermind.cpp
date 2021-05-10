#include <iostream>
#include <ctime>

// pour les nombres aléatoires
#include <random>
#include <cstring> // strlen

using namespace std;

// ======================================================================
// Couleur au hasard
std::uniform_int_distribution<int> distribution;
std::default_random_engine generateur(time(NULL)); /* NOT using std::random_device since not
                                                    * all compilers seems to support it :-( */

char tirer_couleur()
{
  static const char* const couleurs = ".RGBCYM";
  static const int nb = strlen(couleurs) - 1;

  return couleurs[distribution(generateur,
                               std::uniform_int_distribution<int>::param_type {0, nb})];
}

// ======================================================================
char poser_question()
{
  char lu(' ');
  cout << "Entrez une couleur : ";
  cin >> lu;
  return lu;
}

// ---- prototype -------------------------------------------------------
bool couleur_valide(char c);

// ======================================================================
char lire_couleur()
{
  char lu(poser_question());
  while (not couleur_valide(lu)) {
    cout << "'" << lu << "' n'est pas une couleur valide." << endl;
    cout << "Les couleurs possibles sont : ., R, G, B, C, Y ou M." << endl;
    lu = poser_question();
  }
  return lu;
}

// ======================================================================
void afficher_couleurs(char c1, char c2, char c3, char c4)
{
  cout << ' ' << c1 << ' ' << c2 << ' ' << c3 << ' ' << c4;
}

// ======================================================================
void afficher(int nb, char c)
{
  while (nb-- > 0) {
    cout << c;
  }
}

// ---- prototype -------------------------------------------------------
void afficher_reponses(char c1, char c2, char c3, char c4,
                       char r1, char r2, char r3, char r4);

// ======================================================================
void afficher_coup(char c1, char c2, char c3, char c4,
                   char r1, char r2, char r3, char r4)
{
  afficher_couleurs(c1, c2, c3, c4);
  cout << " : ";
  afficher_reponses(c1, c2, c3, c4,
                    r1, r2, r3, r4);
  cout << endl;
}

// ======================================================================
void message_gagne(int nb_coups)
{
  cout << "Bravo ! Vous avez trouvé en " << nb_coups << " coups." << endl;
}

// ======================================================================
void message_perdu(char c1, char c2, char c3, char c4)
{
  cout << "Perdu :-(" << endl;
  cout << "La bonne combinaison était : ";
  afficher_couleurs(c1, c2, c3, c4);
  cout << endl;
}

/*****************************************************
 * Compléter le code à partir d'ici
 *****************************************************/

// ======================================================================
bool couleur_valide(char c) {
  if (c == '.' or c == 'R' or c == 'G' or c == 'B' or c == 'C' or c == 'Y' or c == 'M')
    return true;
  else
    return false;
}

// ======================================================================
bool verifier(char c, char& r, int& score) {
  if (c == r) {
    r = '_';
    score += 1;
    return true;
  } else {
    return false;
  }
}

// ======================================================================
void apparier(char c, char& r1, char& r2, char& r3, int& score) {
  if (verifier(c, r1, score)) {
  } else if (verifier(c, r2, score)) {
  } else if (verifier(c, r3, score)) {
  }
}

// ======================================================================
void afficher_reponses(char c1, char c2, char c3, char c4,
                       char r1, char r2, char r3, char r4) {
  int match_score(0);
  bool match1(false);
  bool match2(false);
  bool match3(false);
  bool match4(false);
  match1 = verifier(c1, r1, match_score);
  match2 = verifier(c2, r2, match_score);
  match3 = verifier(c3, r3, match_score);
  match4 = verifier(c4, r4, match_score);
  afficher(match_score, '#');
  int guess_score(0);
  if (!match1) {
    apparier(c1, r2, r3, r4, guess_score);
  }
  if (!match2) {
    apparier(c2, r1, r3, r4, guess_score);
  }
  if (!match3) {
    apparier(c3, r1, r2, r4, guess_score);
  }
  if (!match4) {
    apparier(c4, r1, r2, r3, guess_score);
  }
  afficher(guess_score, '+');
  afficher(4 - match_score - guess_score, '-');
}

// ======================================================================
bool gagne(char c1, char c2, char c3, char c4,
           char r1, char r2, char r3, char r4) {
  if (c1 == r1 and c2 == r2 and c3 == r3 and c4 == r4) {
    return true;
  } else {
    return false;
  }
}

// ======================================================================
void jouer(int maxturn=8) {
  int turn(0);
  char r1(tirer_couleur());
  char r2(tirer_couleur());
  char r3(tirer_couleur());
  char r4(tirer_couleur());

  char c1('_');
  char c2('_');
  char c3('_');
  char c4('_');
  
  do {
    turn++;
    c1 = lire_couleur();
    c2 = lire_couleur();
    c3 = lire_couleur();
    c4 = lire_couleur();

    afficher_coup(c1, c2, c3, c4, r1, r2, r3, r4);
  } while (!gagne(c1, c2, c3, c4, r1, r2, r3, r4) and turn < maxturn);

  if (gagne(c1, c2, c3, c4, r1, r2, r3, r4)) {
    message_gagne(turn);
  } else {
    message_perdu(r1, r2, r3, r4);
  }
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  jouer();
  return 0;
}
