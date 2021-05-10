#include <iostream>
#include <array>
#include <cmath>
using namespace std;

class Point3D {
    private:
        double x;
        double y;
        double z;

    public:
        void init(double xpos, double ypos, double zpos) {
            x = xpos;
            y = ypos;
            z = zpos;
        }

        bool compare(Point3D other) {
            return bool(x == other.x and y == other.y and z == other.z);
        }

        double distance(Point3D other) {
            return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2));
        }

        ostream& operator>>(ostream& str) const {
            str << "<Point3D x=" << x
            << " y=" << y
            << " z=" << z
            << ">";
            return str;
        }

        friend ostream& operator<<(ostream& cout, Point3D const p);
};

ostream& operator<<(ostream& cout, Point3D const inst) {
    return inst >> cout;
}


class Triangle {
    private:
        Point3D a;
        Point3D b;
        Point3D c;

    public:
        void init(Point3D pointa, Point3D pointb, Point3D pointc) {
            a = pointa;
            b = pointb;
            c = pointc;
        }
        double perimeter() {
            return a.distance(b) + b.distance(c) + c.distance(a);
        }
        bool isocele() {
            double ab = a.distance(b);
            double bc = b.distance(c);
            double ca = c.distance(a);
            return bool(ab == bc or ab == ca or bc == ca);
        }

        ostream& operator>>(ostream& str) const {
            str << "<Triangle" << endl
                << "  " << a << endl
                << "  " << b << endl
                << "  " << c << endl
                << ">";
            return str;
        }
        
        friend ostream& operator<<(ostream& cout, Triangle const t);
};

ostream& operator<<(ostream& cout, Triangle const inst) {
    return inst >> cout;
}

int main() {
    Point3D p1; p1.init(0, 0, 0);
    Point3D p2; p2.init(2.5, 2.5, 0);
    Point3D p3; p3.init(0, 5, 0);
    Triangle t; t.init(p1, p2, p3);
    cout << p1 << endl;
    cout << t << endl;
    cout << "Périmètre : " << t.perimeter() << endl;
    cout << boolalpha << "Isocele : " << t.isocele() << endl;
    return 0;
}