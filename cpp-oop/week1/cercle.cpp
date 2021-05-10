#include <iostream>
#include <cmath>

class Cercle {
    private:
        double posx;
        double posy;
        double radius;

    public:
        void getCenter(double& x, double& y) { x = posx; y = posy; }
        void setCenter(double x, double y) { posx = x; posy = y; }
        double getRadius(double r) const { return radius; }
        void setRadius(double r) { radius = r; }
        double surface() const {
            return 2 * M_PI * pow(radius, 2);
        }

        bool estInterieur(double x, double y) const {
            double distance(sqrt( pow(posx - x, 2) + pow(posy - y, 2) ));
            return bool(distance <= radius);
        }
};


int main() {
    Cercle c;
    double x(0);
    double y(0);
    c.setCenter(x, y);
    c.setRadius(5);
    c.getCenter(x, y);

    std::cout << "x=" << x << " y=" << y << std::endl;

    c.setCenter(10, 5);
    c.getCenter(x, y);
    std::cout << "x=" << x << " y=" << y << std::endl;

    std::cout << "surface=" << c.surface() << std::endl;
    std::cout << std::boolalpha << "x=2 y=5 est à l'interieur : "  << c.estInterieur(2, 5) << std::endl;
    std::cout << std::boolalpha << "x=5 y=5 est à l'interieur : "  << c.estInterieur(16, 5) << std::endl;
    
    return 1;
}