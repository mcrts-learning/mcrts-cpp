#include <iostream>
#include <array>
#include <cmath>
using namespace std;

//
// Point3D
//
// --------------------------------------------------------------------
class Point3D {
    public:
        Point3D(): x(0.0), y(0.0), z(0.0){}

        Point3D(double x, double y, double z): x(x), y(y), z(z){}

        bool operator==(const Point3D& autre) const;
        
        double get_x() const {return x;}
        double get_y() const {return y;}
        double get_z() const {return z;}
    
    protected:
        double x, y, z;
};
// --------------------------------------------------------------------
bool Point3D::operator==(const Point3D& p) const {
    return (p.x == x) and (p.y == y) and (p.z == z);
}
// --------------------------------------------------------------------
ostream& operator<<(ostream& cout, const Point3D& p) {
    cout << '(' << p.get_x() << ", " << p.get_y() << ", " << p.get_z() << ')';
    return cout;
}
// ====================================================================


//
// Vecteur
//
// --------------------------------------------------------------------
class Vecteur :public Point3D {
    public:
        Vecteur(): Point3D(){} 
        Vecteur(double x, double y, double z): Point3D(x, y, z){}

        // opérateurs
        Vecteur& operator+=(const Vecteur& autre) {
            x += autre.x;
            y += autre.y;
            z += autre.z;
            return*this;
        }
        Vecteur& operator-=(const Vecteur& autre){
            x -= autre.x;
            y -= autre.y;
            z -= autre.z;
            return*this;
        }
        const Vecteur operator-() const{
            return Vecteur(-x, -y, -z);
        }
        Vecteur& operator*=(double scal) {
            x *= scal;
            y *= scal; 
            z *= scal;
            return*this;
        }
        double norme() const;
};
// --------------------------------------------------------------------
const Vecteur operator+(Vecteur un, const Vecteur& autre) {
    un += autre;
    return un;
}
const Vecteur operator-(Vecteur un, const Vecteur& autre) {
    un -= autre;
    return un;
}
double operator*(const Vecteur& un, const Vecteur& autre) {
    return un.get_x() * autre.get_x() + un.get_y() * autre.get_y() + un.get_z() * autre.get_z();
}
const Vecteur operator*(Vecteur un, double x) {
    un *= x;
    return un;
}
const Vecteur operator*(double x, Vecteur const& v) {
    return v * x;
}
double Vecteur::norme() const {
    return sqrt(*this * *this);
}
double angle(const Vecteur& un, const Vecteur& autre) {
    return acos((un * autre) / (un.norme() * autre.norme()));
}
// ====================================================================





class VecteurUnitaire :public Vecteur {
    public:
        VecteurUnitaire(): Vecteur(1, 0, 0){} 
        VecteurUnitaire(double x, double y, double z): Vecteur(x, y, z) {
            double norme(Vecteur::norme());
            this->x = x / norme;
            this->y = y / norme;
            this->z = z / norme;
        }
        Vecteur& normalize() {
            
        }
};

double angle(VecteurUnitaire const& v1, VecteurUnitaire const& v2) {
    return acos(v1 * v2);
}

int main() {
    Vecteur v1(1, 2, -0.1);
    Vecteur v2(2.6, 3.5, 4.1);
    cout << v1 << " + " << v2 << " = " << v1 + v2 << endl;
    cout << v2 << " + " << v1 << " = " << v2 + v1 << endl;

    Vecteur v3(0, 0, 0);
    cout << v1 << " + " << v3 << " = " << v1 + v3 << endl;
    cout << v3 << " + " << v1 << " = " << v3 + v1 << endl;


    cout << v1 << " - " << v2 << " = " << v1 - v2 << endl;
    cout << v2 << " - " << v2 << " = " << v2 - v2 << endl;


    cout << "-" << v1 << " = " << -v1 << endl;
    cout << "-" << v2 << " + " << v1 << " = " << -v2 + v1 << endl;

    cout << "3*" << v1 << " = " << 3*v1 << endl;
    cout << v1 << " * " << v2 << " = " << v1 * v2 << endl;
    cout << v2 << " * " << v1 << " = " << v2 * v1 << endl;

    cout << "||" << v1 << " ||" << " = " << v1.norme() << endl;
    cout << "||" << v2 << " ||" << " = " << v2.norme() << endl;
    cout << "angle(" << v2 << ", " << v1 << ")" << " = " << angle(v1, v2) << endl;

    
    VecteurUnitaire v4(1, 2, 3);
    VecteurUnitaire v5(1, 1, 1);
    cout << "||" << v4 << " ||" << " = " << v4.norme() << endl;
    cout << "||" << v5 << " ||" << " = " << v5.norme() << endl;
    cout << "angle(" << v4 << ", " << v5 << ")" << " = " << angle(v4, v5) << endl;
    return 0;
}