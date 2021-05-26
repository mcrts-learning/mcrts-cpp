#include <memory>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

typedef string Date;
// ====================================
class Printable {
public:
    virtual const string printString() const = 0;
};
// ----

ostream& operator<<(ostream& ostr, const Printable& instance)
    { return (ostr << instance.printString()); }

// =========================================
class Ouvrage: public Printable {
protected:
    bool available_;
    string owner_;
    Date date_emprunt_;
public:
    Ouvrage();
    virtual const string getKind() const = 0;
    void emprunt(string, Date);
};

//----
Ouvrage::Ouvrage()
    : available_(true), owner_(""), date_emprunt_("") {}
void Ouvrage::emprunt(string owner, Date date)
    {
        available_ = false;
        owner_ = owner;
        date_emprunt_ = date;
    }

// =========================================
typedef shared_ptr<Ouvrage> pOuvrage;

class Bibliotheque {
private:
    vector<pOuvrage> inventory;
public:
    ~Bibliotheque();
    unsigned int ajoute(Ouvrage*);
    void vide();
    void supprime(size_t);
    pOuvrage operator[](size_t);

    void affiche(ostream&) const;
};

//----
Bibliotheque::~Bibliotheque()
    { vide(); }
unsigned int Bibliotheque::ajoute(Ouvrage* inst)
    {
        inventory.push_back(pOuvrage(inst));
        return inventory.size() - 1;
    }
void Bibliotheque::vide()
    {
        for (auto& i : inventory)
            i.reset();
        
        inventory.clear();
    }
void Bibliotheque::supprime(size_t index)
    { inventory.erase(inventory.begin() + index); }

pOuvrage Bibliotheque::operator[](size_t index)
    { return inventory[index]; }

void Bibliotheque::affiche(ostream& ostr) const
    {
        for (size_t i(0); i < inventory.size(); i++) {
            ostr << i << "- " << inventory[i]->getKind() << " :" << endl;
            ostr << *inventory[i] << endl;
        }
    }

// =========================================
class Livre: public Ouvrage {
private:
    string title_, authors_, editor_;
    Date date_parution_;
public:
    Livre(string, string, string, Date);
    virtual const string getKind() const override;
    const string printString() const override;
};

//----
Livre::Livre(string title_, string authors_, string editor_, Date date_parution_)
    : Ouvrage(), title_(title_), authors_(authors_), editor_(editor_), date_parution_(date_parution_) {}
const string Livre::getKind() const
    { return "Livre"; }
const string Livre::printString() const
    {
        stringstream msg;
        msg << "\t" << title_ << endl
            << "\tpar " << authors_ << endl
            << "\tpublie en " << date_parution_ << " par " << editor_ << endl;
        if (available_)
            msg << "Disponible.";
        else
            msg << "Emprunte le " << date_emprunt_ << " par " << owner_;
        return msg.str();
    }

// =========================================
class Journal: public Ouvrage {
private:
    string title_, editor_;
    Date date_parution_;
public:
    Journal(string, string, Date);
    virtual const string getKind() const override;
    const string printString() const override;
};

//----
Journal::Journal(string title_, string editor_, Date date_parution_)
    : Ouvrage(), title_(title_), editor_(editor_), date_parution_(date_parution_) {}
const string Journal::getKind() const
    { return "Journal"; }
const string Journal::printString() const
    {
        stringstream msg;
        msg << "\t" << title_ << " de " << date_parution_ << endl
            << "\tpublie par " << editor_ << endl;
        if (available_)
            msg << "Disponible.";
        else
            msg << "Emprunte le " << date_emprunt_ << " par " << owner_;
        return msg.str();
    }

// =========================================
class LivreExterne: public Livre {
private:
    string origin_;
public:
    LivreExterne(string, string, string, Date, Date, string, string);
    const string printString() const override;
};

//----
LivreExterne::LivreExterne(string title_, string authors_, string editor_, Date date_parution_, Date date_emprunt_, string owner_, string origin_)
    : Livre(title_, authors_, editor_, date_parution_), origin_(origin_)
    { emprunt(owner_, date_emprunt_); }
const string LivreExterne::printString() const
    {
        stringstream msg;
        msg << Livre::printString() << endl;
        msg << "provenant de " << origin_;
        return msg.str();
    }

// =========================================
class Video: public Ouvrage {
private:
    string title_, author_, editor_;
    Date date_parution_;
    unsigned int duration_;
public:
    Video(string, string, string, Date, unsigned int);
    virtual const string getKind() const override;
    const string printString() const override;
};

//----
Video::Video(string title_, string author_, string editor_, Date date_parution_, unsigned int duration_)
    : Ouvrage(), title_(title_), author_(author_), editor_(editor_), date_parution_(date_parution_), duration_(duration_) {}
const string Video::getKind() const
    { return "Video"; }
const string Video::printString() const
    {
        stringstream msg;
        msg << "\t" << title_ << endl
            << "\tpar " << author_ << endl
            << "\tpubliee en " << date_parution_ << " par " << editor_ << endl
            << "\tduree : " << duration_ << " minutes" << endl;
        if (available_)
            msg << "Disponible.";
        else
            msg << "Emprunte le " << date_emprunt_ << " par " << owner_;
        return msg.str();
    }

// ==========================================
int main() {
    Bibliotheque bib;
    unsigned int i0, i1, i2, i3;

    cout << "====" << endl;
    i0 = bib.ajoute(new Livre("Programmation orientee objets en C++ (2nd edition)", "Micheloud et Rieder", "PPUR", "2003"));
    i1 = bib.ajoute(new Journal("Computational Linguistics", "MIT Press", "2003-12"));
    i2 = bib.ajoute(new Video("Nanometers and Gigabucks", "G. E. Moore", "University Video Communications", "1996", 61));
    i3 = bib.ajoute(new LivreExterne("Elements of Information Theory", "Cover and Thomas", "Wiley", "1991", "2004-02-25", "C. Chatnonne", "ETHZ-BC"));
    bib.affiche(cout);
    cout << "====" << endl;

    bib[i0]->emprunt("Laurent", "2021-01-01");
    bib.affiche(cout);

    bib.supprime(i3);
    cout << "====" << endl;
    bib.affiche(cout);
    return 0;
}
