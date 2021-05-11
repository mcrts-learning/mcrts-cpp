#include <iostream>
#include <array>
#include <cmath>
using namespace std;

/*
Point3D class definition
*/

class Point3D {
    protected:
        double x;
        double y;
        double z;

    public:
        Point3D(double x, double y, double z)
        : x(x), y(y), z(z) {}

        bool compare(Point3D& other) const{
            return bool(x == other.x and y == other.y and z == other.z);
        }

        double distance(Point3D& other) const{
            return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2));
        }

        ostream& print(ostream& cout) const{
            cout << "<Point3D x=" << x
            << " y=" << y
            << " z=" << z
            << ">";
            return cout;
        }
};

ostream& operator<<(ostream& cout, Point3D const inst) {
    return inst.print(cout);
}


/*
Vecteur class definition
*/

class Vecteur : public Point3D {
    public:
        Vecteur(double x, double y, double z)
        : Point3D(x, y, z) {}
        
        Vecteur add(Vecteur const& other) const {
            return Vecteur((x + other.x),  (y + other.y), (z + other.z));
        }

        Vecteur multiply(double const& n) const {
            Vecteur v(0, 0, 0);
            for (size_t i(0); i < n; i++)
                v = v.add(*this);
            return v;
        }

        double product(Vecteur const& other) const {
            double scalar(0);
            scalar += x * other.x;
            scalar += y * other.y;
            scalar += z * other.z;
            return scalar;
        }

        double norme() const {
            return sqrt(this->product(*this));
        }

        const Vecteur operator-() const {
            return Vecteur(-x, -y, -z);
        }

        ostream& print(ostream& cout) const{
            cout << "(" << x << " " << y << " " << z << ")";
            return cout;
        }

        
};

const Vecteur operator+(Vecteur v1, Vecteur const& v2) {
    return v1.add(v2);
}

const Vecteur operator-(Vecteur v1, Vecteur const& v2) {
    return v1 + (-v2);
}

const Vecteur operator*(double n, Vecteur const& v) {
    return v.multiply(n);
}

const double operator*(Vecteur v1, Vecteur const& v2) {
    return v1.product(v2);
}


ostream& operator<<(ostream& cout, Vecteur const inst) {
    return inst.print(cout);
}

double angle(Vecteur const& v1, Vecteur const& v2) {
    return acos((v1 * v2) / (v1.norme() * v2.norme()));
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

    return 0;
}