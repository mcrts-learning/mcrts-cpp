#include <iostream>
using namespace std;

class Complexe {
    private:
        double a;
        double b;
    
    public:
        Complexe()
        : a(0), b(0) {}
        Complexe(double const a, double const b)
        : a(a), b(b) {}
    
    public:
        ostream& operator>>(ostream& str) const{
            str << "(" << a << " + " << b << "i" << ")";
            return str;
        }

        friend ostream& operator<<(ostream& cout, Complexe const inst);

        Complexe operator=(Complexe const& other) {
            a = other.a;
            b = other.b;
            return *this;
        }

        bool operator==(Complexe const& other) const{
            return bool(a == other.a and b == other.b);
        }

        Complexe operator+(Complexe const& other) const{
            return Complexe(a + other.a, b + other.b);
        }

        Complexe operator+(double const& reel) const{
            Complexe other(reel, 0);
            return (*this) + other;
        }

        Complexe operator+=(Complexe const& other) {
            (*this) = (*this) + other;
            return *this;
        }

        Complexe operator+=(double const reel) {
            Complexe other(reel, 0);
            return (*this) += other;
        }

        Complexe operator-(Complexe const& other) const{
            return Complexe(a - other.a, b - other.b);
        }

        Complexe operator-=(Complexe const& other) {
            (*this) = (*this) - other;
            return *this;
        }

        Complexe operator*(Complexe const& other) const{
            return Complexe((a * other.a) - (b * other.b), (a * other.b) + (b * other.a));
        }

        Complexe operator*(double const& reel) const{
            Complexe other(reel, 0);
            return (*this) * other;
        }

        Complexe operator*=(Complexe const& other) {
            (*this) = (*this) * other;
            return *this;
        }

        Complexe operator*=(double const& reel) {
            Complexe other(reel, 0);
            return (*this) *= other;
        }

        Complexe operator/(Complexe const& other) const{
            double reel( ((a * other.a) + (b * other.b)) / ((other.a * other.a) + (other.b * other.b)) );
            double imag( ((b * other.a) - (a * other.b)) / ((other.a * other.a) + (other.b * other.b)) );
            return Complexe(reel, imag);
        }

        Complexe operator/(double const& reel) const{
            Complexe other(reel, 0);
            return (*this) / other;
        }

        Complexe operator/=(Complexe const& other) {
            (*this) = (*this) / other;
            return *this;
        }
};

ostream& operator<<(ostream& cout, Complexe const inst) {
    return inst >> cout;
}

Complexe operator+(double const reel, Complexe const inst) {
    return inst + reel;
}

Complexe operator*(double const reel, Complexe const inst) {
    return inst * reel;
}



int main() {
    Complexe defaut;
    Complexe zero(0.0, 0.0);
    Complexe un(1.0, 0.0);
    Complexe i(0.0, 1.0);
    Complexe j;

    cout << zero << " ==? " << defaut;
    if (zero == defaut) cout << " oui" << endl;
    else cout << " non" << endl;

    cout << zero << " ==? " << i;
    if (zero == i) cout << " oui" << endl;
    else cout << " non" << endl;

    j = un + i;
    cout << un << " + " << i << " = " << j << endl;

    Complexe trois(un);
    trois += un;
    trois += 1.0;
    cout << un << " + " << un << " + 1.0 = " << trois << endl;

    Complexe deux(trois);
    deux -= un;
    cout << trois << " - " << un << " = " << deux << endl;

    trois = 1.0 + deux;
    cout << "1.0 + " << deux << " = " << trois << endl;

    Complexe z(i*i);
    cout << i << " * " << i << " = " << z << endl;
    cout << z << " / " << i << " = " << z/i << " = ";
    cout << (z/=i) << endl;

    Complexe k(2.0,-3.0);
    z = k;
    z *= 2.0;
    z *= i;
    cout << k << " * 2.0 * " << i << " = " << z << endl;
    z = 2.0 * k * i / 1.0;
    cout << " 2.0 * " << k << " * " << i << " / 1 = " << z << endl;
    return 0;
    }