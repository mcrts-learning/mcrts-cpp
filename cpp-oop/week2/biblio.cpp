#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*******************************************
 * Completez le programme a partir d'ici.
 *******************************************/

class Auteur {
     private:
          string name;
          bool award;
     
     public:
          Auteur(string name, bool award=false)
          : name(name), award(award) {}
          Auteur(Auteur const& auteur) = delete;

          string getNom() const { return name; }
          bool getPrix() const { return award; }
};

class Oeuvre {
     private:
          string title;
          Auteur const& auteur;
          string language;

     public:
          Oeuvre(string title, Auteur& auteur, string language)
          : title(title), auteur(auteur), language(language) {}
          Oeuvre(Oeuvre const&  oeuvre) = delete;
          ~Oeuvre() {
               cout << "L'oeuvre "<< '"' << getInfos()<< '"' << " n'est plus disponible." << endl;
          }

          string getTitre() const {return title;}
          Auteur const& getAuteur() const {return auteur;}
          string getLangue() const {return language;}
          string getInfos() const {
                string s(
                    title + ", " +  auteur.getNom() + ", en " + language
               );
               return s;
          }

          void affiche() const {
               cout << getInfos() << endl;
          }

};

class Exemplaire {
     private:
          Oeuvre const& oeuvre;

     public:
          Exemplaire(Oeuvre const& oeuvre)
          : oeuvre(oeuvre) {
               cout << "Nouvel exemplaire de : " << oeuvre.getInfos() << endl;
          }
          Exemplaire(Exemplaire const&  exemplaire)
          : oeuvre(exemplaire.oeuvre) {
               cout << "Copie d'un exemplaire de : " << oeuvre.getInfos() << endl;
          }
          ~Exemplaire() {
               cout << "Un exemplaire de " << '"' << oeuvre.getInfos() << '"' << " a été jeté !" << endl;
          }

          Oeuvre const& getOeuvre() const {return oeuvre;}
          string getLangue() const {return oeuvre.getLangue();}
          Auteur const& getAuteur() const {return oeuvre.getAuteur();}
          void affiche() const {
               cout << "Exemplaire de : " << oeuvre.getInfos();
          }

};

class Bibliotheque {
     private:
          string name;
          vector<Exemplaire*> exemplaires;

     public:
          Bibliotheque(string name)
          : name(name) {
               vector<Exemplaire*> exemplaires(0);
               cout << "La bibliothèque "<< name << " est ouverte !" << endl;
          }
          ~Bibliotheque() {
               cout << "La bibliothèque " << name << " ferme ses portes," << endl
                    << "et détruit ses exemplaires :" << endl;
               for (size_t i(0); i < exemplaires.size(); i++) {
                    delete exemplaires[i];
               }
          }

          string getNom() const {return name;}
          void stocker(Oeuvre& oeuvre, size_t quantite=1) {
               for (size_t i(0); i < quantite; i++) {
                    Exemplaire* e = new Exemplaire(oeuvre);
                    exemplaires.push_back(e);
               }
          }
          void lister_exemplaires(string langue="") const {
               for (auto e : exemplaires) {
                    if (langue == "" or (*e).getLangue() == langue) {
                         (*e).affiche();
                         cout << endl;
                    }
               }
          }
          int compter_exemplaires(Oeuvre& oeuvre) const {
               int count(0);
               for (auto e : exemplaires) {
                    if (&oeuvre == &((*e).getOeuvre())) {
                         count++;
                    }
               }
               return count;
          }
          void afficher_auteurs(bool award=false) const {
               for (auto e : exemplaires) {
                    if (!award or (*e).getAuteur().getPrix()) {
                         cout << (*e).getAuteur().getNom() << endl;
                    }
               }
          }

};

/*******************************************
 * Ne rien modifier apres cette ligne.
 *******************************************/

int main()
{
  Auteur a1("Victor Hugo"),
         a2("Alexandre Dumas"),
         a3("Raymond Queneau", true);

  Oeuvre o1("Les Misérables"           , a1, "français" ),
         o2("L'Homme qui rit"          , a1, "français" ),
         o3("Le Comte de Monte-Cristo" , a2, "français" ),
         o4("Zazie dans le métro"      , a3, "français" ),
         o5("The Count of Monte-Cristo", a2, "anglais" );

  Bibliotheque biblio("municipale");
  biblio.stocker(o1, 2);
  biblio.stocker(o2);
  biblio.stocker(o3, 3);
  biblio.stocker(o4);
  biblio.stocker(o5);

  cout << "La bibliothèque " << biblio.getNom()
       << " offre les exemplaires suivants :" << endl;
  biblio.lister_exemplaires();

  const string langue("anglais");
  cout << " Les exemplaires en "<< langue << " sont :" << endl;
  biblio.lister_exemplaires(langue);

  cout << " Les auteurs à succès sont :" << endl;
  biblio.afficher_auteurs(true);

  cout << " Il y a " << biblio.compter_exemplaires(o3) << " exemplaires de "
       << o3.getTitre() << endl;

  return 0;
}
