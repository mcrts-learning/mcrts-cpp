#include <iostream>
#include <array>
using namespace std;

class Point3D {
    public:
        void init(double xpos, double ypos, double zpos) {
            x = xpos;
            y = ypos;
            z = zpos;
        }

        void affiche() {
            cout << "<Point3D x=" << x << " y=" << y << " z=" << z << ">" << endl;
        }

        bool compare(Point3D other) {
            return bool(x == other.x and y == other.y and z == other.z);
        }

    private:
        double x;
        double y;
        double z;
};

int main() {
    Point3D point1;
    Point3D point2;
    Point3D point3;
    Point3D point4;
    point1.init(1.0, 2.0, -0.1);
    point2.init(2.6, 3.5, 4.1);
    point3 = point1;
    point4.init(2.6, 3.5, 4.1);

    cout << "Point 1 :";
    point1.affiche();

    cout << "Point 2 :";
    point2.affiche();

    cout << "Le point 1 est ";
    if (point1.compare(point2)) {
        cout << "identique au";
    } else {
        cout << "différent du";
    }
    cout << " point 2." << endl;

    cout << "Le point 1 est ";
    if (point1.compare(point3)) {
        cout << "identique au";
    } else {
        cout << "différent du";
    }
    cout << " point 3." << endl;

    cout << "Le point 4 est ";
    if (point4.compare(point2)) {
        cout << "identique au";
    } else {
        cout << "différent du";
    }
    cout << " point 2." << endl;
    return 0;
}