#include <sstream>
#include <iostream>
#include <string>
#include <set>
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
    int x;
    int y;
};

bool operator==(Position const& lhs, Position const& rhs)
    { return (lhs.x == rhs.x and lhs.y == rhs.y); }
bool operator!=(Position const& lhs, Position const& rhs)
    { return (not (lhs == rhs)); }
const Position operator+(Position const& lhs, Position const& rhs)
    { return Position({lhs.x + rhs.x, lhs.y + rhs.y}); }
const Position operator-(Position const& lhs)
    { return Position({-lhs.x, -lhs.y}); }
const Position operator-(Position const& lhs, Position const& rhs)
    { return lhs + (-rhs); }
bool operator<(Position const& lhs, Position const& rhs)
    { 
        if (lhs.x < rhs.x)
            return true;
        else if (lhs.x == rhs.x and lhs.y < rhs.y)
            return true;
        else
            return false;
    }


string as_string(Position const& pos)
    {
        stringstream msg;
        msg << "(" << pos.x << ", " << pos.y << ")";
        return msg.str();
    }
enum Color {BLANC = 0, NOIR};
string as_string(Color const& color)
    {
        switch (color) {
        case BLANC:
            return "blanc";
        case NOIR:
            return "noir";
        }
        return "empty";
    }


// ====================================
class Piece: public Printable {
protected:
    Position position_;
    Color couleur_;
public:
    Piece(Position const&, Color);
    virtual const string printString() const = 0;
    virtual bool isValid(const Position&) const;
    virtual bool deplace(const Position&);
};

// ----
Piece::Piece(Position const& p, Color c)
    : position_(p), couleur_(c) {}

bool Piece::isValid(const Position& p) const
    { return (position_ != p and p.x >= 1 and p.x <= 8 and p.y >= 1 and p.y <= 8); }
bool Piece::deplace(const Position& p)
    {   
        if (this->isValid(p)) {
            cout << (*this) << " se deplace en " << as_string(p) << " reussite" << endl;
            position_ = p;
            return true;
        } else {
            cout << (*this) << " se deplace en " << as_string(p) << " echec" << endl;
            return false;
        }
    }

// ====================================
class Pion: public Piece {
using Piece::Piece;
public:
    const string printString() const;
    bool isValid(const Position& p) const;
};

// ----
const string Pion::printString() const
    {
        stringstream msg;
        msg << "Pion " << as_string(couleur_) << " en " << as_string(position_);
        return msg.str();
    }
bool Pion::isValid(const Position& p) const
    {
        Position r(p - position_);
        bool result(Piece::isValid(p));
        if (result) {
            if ((couleur_ == NOIR) and (r == Position({1, 1}) or r == Position({-1, 1})))
                result = true;
            else if ((couleur_ == BLANC) and (r == Position({1, -1}) or r == Position({-1, -1})))
                result = true;
            else
                result = false;
        }
        return result;
    }

// ====================================
class Cavalier: public Piece {
using Piece::Piece;
public:
    const string printString() const;
    bool isValid(const Position& p) const;
};

// ----
const string Cavalier::printString() const
    {
        stringstream msg;
        msg << "Cavalier " << as_string(couleur_) << " en " << as_string(position_);
        return msg.str();
    }
bool Cavalier::isValid(const Position& p) const
    {
        Position r(p - position_);
        set<Position> s({
            Position({1, 2}),
            Position({1, -2}),
            Position({-1, 2}),
            Position({-1, -2}),
            Position({2, 1}),
            Position({2, -1}),
            Position({-2, 1}),
            Position({-2, -1}),
        });
        return (Piece::isValid(p) and s.count(r));
    }

// ====================================
class Tour: public Piece {
using Piece::Piece;
public:
    const string printString() const;
    bool isValid(const Position& p) const;
};

// ----
const string Tour::printString() const
    {
        stringstream msg;
        msg << "Tour " << as_string(couleur_) << " en " << as_string(position_);
        return msg.str();
    }
bool Tour::isValid(const Position& p) const
    {
        Position r(p - position_);
        return (Piece::isValid(p) and (r.x == 0 or r.y == 0));
    }

// ====================================
class Fou: public Piece {
using Piece::Piece;
public:
    const string printString() const;
    bool isValid(const Position& p) const;
};

// ----
const string Fou::printString() const
    {
        stringstream msg;
        msg << "Fou " << as_string(couleur_) << " en " << as_string(position_);
        return msg.str();
    }
bool Fou::isValid(const Position& p) const
    {
        Position r(p - position_);
        return (Piece::isValid(p) and (r.x == r.y or r.x == -r.y));
    }

// ====================================
class Reine: public Piece {
using Piece::Piece;
public:
    const string printString() const;
    bool isValid(const Position& p) const;
};

// ----
const string Reine::printString() const
    {
        stringstream msg;
        msg << "Reine " << as_string(couleur_) << " en " << as_string(position_);
        return msg.str();
    }
bool Reine::isValid(const Position& p) const
    {   
        return (Fou(position_, couleur_).isValid(p) or Tour(position_, couleur_).isValid(p));
    }

// ====================================
class Roi: public Piece {
using Piece::Piece;
public:
    const string printString() const;
    bool isValid(const Position& p) const;
};

// ----
const string Roi::printString() const
    {
        stringstream msg;
        msg << "Roi " << as_string(couleur_) << " en " << as_string(position_);
        return msg.str();
    }
bool Roi::isValid(const Position& p) const
    {   
        Position r(p - position_);
        return (Reine(position_, couleur_).isValid(p) and abs(r.x) <= 1 and abs(r.y) <= 1);
    }
// ====================================
int main() {
    {
        Pion p({2, 5}, NOIR);
        cout << p << endl;
        p.deplace({1, 7});
        p.deplace({2, 7});
        p.deplace({3, 6});
        p.deplace({2, 7});
        p.deplace({1, 8});
    }
    {
        Pion p({5, 7}, BLANC);
        cout << p << endl;
        p.deplace({6, 8});
        p.deplace({6, 6});
        p.deplace({5, 5});
        p.deplace({4, 4});
    }
    {
        Cavalier p({5, 5}, BLANC);
        cout << p << endl;
        p.deplace({6, 8});
        p.deplace({6, 7});
    }
    {
        Tour p({5, 5}, BLANC);
        cout << p << endl;
        p.deplace({6, 8});
        p.deplace({5, 8});
        p.deplace({2, 8});
    }
    {
        Fou p({5, 5}, BLANC);
        cout << p << endl;
        p.deplace({5, 6});
        p.deplace({7, 7});
    }
    {
        Reine p({5, 5}, BLANC);
        cout << p << endl;
        p.deplace({6, 7});
        p.deplace({7, 7});
        p.deplace({3, 7});
    }
    {
        Roi p({5, 5}, BLANC);
        cout << p << endl;
        p.deplace({5, 7});
        p.deplace({6, 6});
        p.deplace({6, 5});
    }
    return 0;
}