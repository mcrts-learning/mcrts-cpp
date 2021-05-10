#include <iostream>
#include <cmath>
using namespace std;

struct Position {
    double x;
    double y;
};

class Cercle {
    private:
        Position center;
        double radius;

    public:
        Position getCenter() const { return center; }
        void setCenter(Position p) { center = p;}
        void setCenter(double x, double y) { center = Position({x, y}); }

        double getRadius() const { return radius; }
        void setRadius(double r) { radius = r; }

        double surface() const {
            return 2 * M_PI * pow(radius, 2);
        }

        bool estInterieur(Position p) const {
            return estInterieur(p.x, p.y);
        }
        bool estInterieur(double x, double y) const {
            double distance(sqrt( pow(center.x - x, 2) + pow(center.y - y, 2) ));
            return bool(distance <= radius);
        }
};

void test() {
    Position center({0, 0});
    cout << "<Position x=" << center.x << " y=" << center.y << ">" << endl;

    Cercle c;
    c.setCenter(center);
    c.setRadius(5);
    cout << "<Cercle x=" << c.getCenter().x << " y=" << c.getCenter().y << ">" << endl;

    Position p(c.getCenter());
    p.x = 10;
    cout << "<Position x=" << center.x << " y=" << center.y << ">" << endl;
    cout << "<Cercle x=" << c.getCenter().x << " y=" << c.getCenter().y << ">" << endl;

    c.setCenter(10, 0);
    cout << "<Position x=" << center.x << " y=" << center.y << ">" << endl;
    cout << "<Cercle x=" << c.getCenter().x << " y=" << c.getCenter().y << ">" << endl;

    cout << endl;
}


int main() {
    test();
    Cercle c;
    c.setCenter(0, 0);
    c.setRadius(5);
    Position p(c.getCenter());

    cout << "x=" << p.x << " y=" << p.y << endl;

    c.setCenter(Position({10, 5}));
    p = c.getCenter();
    cout << "x=" << p.x << " y=" << p.y << endl;

    cout << "surface=" << c.surface() << endl;
    cout << boolalpha << "x=2 y=5 est à l'interieur : "  << c.estInterieur(2, 5) << endl;
    cout << boolalpha << "x=16 y=5 est à l'interieur : "  << c.estInterieur(16, 5) << endl;
    cout << boolalpha << "x=5 y=5 est à l'interieur : "  << c.estInterieur(p) << endl;
    
    return 1;
}