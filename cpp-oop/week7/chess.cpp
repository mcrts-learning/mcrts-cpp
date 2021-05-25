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
struct Position {
    size_t x;
    size_t y;
};

string as_string(Position const& pos)
    {
        stringstream msg;
        msg << "(" << pos.x << ", " << pos.y << ")";
        return msg.str();
    }
enum Color {blanc = 0, noir};
string as_string(Color const& color)
    {
        switch (color) {
        case blanc:
            return "blanc";
        case noir:
            return "noir";
        }
        return "empty";
    }


// ====================================
class Piece: public Printable {
private:
    Position position_;
    Color couleur_;
public:
    Piece(size_t, size_t, Color);
    const string printString() const;
    virtual const string getName() const;
};

// ----
Piece::Piece(size_t x, size_t y, Color c)
    : position_({x, y}), couleur_(c) {}
const string Piece::printString() const
    {
        stringstream msg;
        msg << getName() << " " << as_string(couleur_) << " en " << as_string(position_);
        return msg.str();
    }
const string Piece::getName() const
    { return "Piece"; }

// ====================================
class Pion: public Piece {
using Piece::Piece;
public:
    virtual const string getName() const;
};

// ----
const string Pion::getName() const
    { return "Pion"; }

// ====================================
int main() {
    cout << Pion(0, 0, noir) << endl;
    return 0;
}