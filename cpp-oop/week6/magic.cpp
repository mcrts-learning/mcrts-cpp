#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

enum Color {ROUGE=0, BLEU, NOIR, VERT, BLANC};

string to_string(Color c) {
    switch (c) {
        case ROUGE:
            return "rouge";
        case BLEU:
            return "bleu";
        case NOIR:
            return "noir";
        case VERT:
            return "vert";
        case BLANC:
            return "blanc";
    }
    return "color not found";
}
//==============================================
typedef unsigned int Cost;

class Carte {
protected:
    Cost cost;
public:
    Carte(Cost cost=0)
    : cost(cost) {}
    virtual ~Carte() {}
    virtual string as_string() const = 0;
};
//==============================================
class Terrain: public virtual Carte {
protected:
    Color color;
public:
    Terrain(Color color)
    : color(color) {}
    virtual ~Terrain() {}
    string as_string() const override {
        return "Un terrain " + to_string(color);
    }
};
//==============================================
class Creature: public virtual Carte {
protected:
    string name;
    int pv, att;
public:
    Creature(Cost cost, string name, int att, int pv)
    : Carte(cost), name(name), pv(pv), att(att) {}
    virtual ~Creature() {}
    string get_power() const {
        return to_string(att) + "/" + to_string(pv);
    }
    string as_string() const override {
        return "Une créature " + name + " " + get_power() + " de coût " + to_string(cost);
    }
};
//==============================================
class Sortilege: public virtual Carte {
protected:
    string name, description;
public:
    Sortilege(Cost cost, string name, string description)
    : Carte(cost), name(name), description(description) {}
    virtual ~Sortilege() {}
    string as_string() const override {
        return "Un sortilège " + name + " de coût " + to_string(cost);
    }
};
//==============================================
class CreatureTerrain: public Creature, public Terrain {
public:
    CreatureTerrain(Cost cost, string name, int att, int pv, Color color)
    : Carte(cost), Creature(cost, name, att, pv), Terrain(color) {}
    virtual ~CreatureTerrain() {}
    string as_string() const override {
        return "Une créature/terrain " + to_string(color) + " " + name + " " + get_power() + " de coût " + to_string(cost);
    }
};
//==============================================
typedef unique_ptr<Carte> Carte_ptr;

class Main {
private:
    vector<Carte_ptr> hand;
public:
    ~Main() {
        vider();
    }

    void ajoute(Carte* card) {
        hand.push_back(Carte_ptr(card));
    }
    void afficher() const {
        cout << "Là, j'ai en stock :" << endl;
        for (auto& c : hand)
            cout << " + " << c->as_string() << endl;
    }

    void vider() {
        cout << "Je jette ma main." << endl;
        for (auto& c : hand)
            c.reset();
        hand.clear();
    }
};
//==============================================
void test() {
    Main h;
    h.ajoute(new Terrain(BLEU));
    h.ajoute(new Creature(6, "Golem", 4, 6));
    h.ajoute(new Sortilege(1, "Croissance Gigantesque", "La créature ciblée gagne +3/+3 jusqu'à la fin du tour"));
    h.ajoute(new CreatureTerrain(2, "Ondine", 1, 1, BLEU));
    h.afficher();
}

//==============================================
int main() {
    test();
    return 0;
}