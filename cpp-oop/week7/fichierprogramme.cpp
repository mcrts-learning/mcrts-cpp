#include <sstream>
#include <iostream>
#include <string>
using namespace std;


// ====================================
class Printable {
public:
    virtual const string printString() const = 0;
};
// ----

ostream& operator<<(ostream& ostr, const Printable& instance)
    { return (ostr << instance.printString()); }

// ====================================
class Document: public virtual Printable {
private:
    string nom, extension;
    int taille;
public:
    Document(string, string, int);
    ~Document();
    const string printString() const;
};

// ----
Document::Document(string nom, string extension, int taille)
    : nom(nom), extension(extension), taille(taille)
    { cout << "creation d'un document" << endl; }
Document::~Document()
    { cout << "destruction d'un document" << endl; }
const string Document::printString() const
    {
        stringstream msg;
        msg << "Je suis le fichier " << nom << "." << extension << endl;
        msg << "ma taille est de : " << taille << "Kb";
        return msg.str();
    }
// ====================================
class Programme: public virtual Printable {
private:
    string langage, auteur, descriptif;
public:
    Programme(string, string, string);
    ~Programme();
    const string printString() const;
};

// ----
Programme::Programme(string langage, string auteur, string descriptif)
    : langage(langage), auteur(auteur), descriptif(descriptif)
    { cout << "creation d'un programme" << endl; }
Programme::~Programme()
    { cout << "destruction d'un programme" << endl; }
const string Programme::printString() const
    {
        stringstream msg;
        msg << "Je suis ecrit en : " << langage << endl;
        msg << "mon auteur est : " << auteur << endl;
        msg << "Je fais du : " << descriptif;
        return msg.str();
    }
// ====================================

class FichierCPP: public Document, public Programme {
public:
    FichierCPP(string, int, string, string);
    ~FichierCPP();
    const string printString() const;
};

FichierCPP::FichierCPP(string nom, int taille, string auteur, string descriptif)
    : Document(nom, "cc", taille), Programme("C++", auteur, descriptif)
    { cout << "creation d'un fichier C++" << endl; }
FichierCPP::~FichierCPP()
    { cout << "destruction d'un fichier C++" << endl; }
const string FichierCPP::printString() const
    {
        stringstream msg;
        msg << Document::printString() << endl;
        msg << Programme::printString();
        return msg.str();
    }

int main() {
    FichierCPP f("numeric", 1600, "Martin Courtois", "calcul numerique");
    cout << f << endl;
}