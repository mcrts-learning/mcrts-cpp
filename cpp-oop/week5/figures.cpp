#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Figure {
    public:
        virtual void affiche() const = 0;
        virtual unique_ptr<Figure> copie() const = 0;
        virtual ~Figure() {cout << "Une <Figure id=" << &(*this) << "> de moins !" << endl;};
};

class Cercle: public Figure {
    private:
        double radius;

    public:
        Cercle(double radius=1)
        :radius(radius) {}
        Cercle(Cercle const& other)
        :Figure(other), radius(other.radius) {
            cout << "Copie : ";
            affiche();
        }

        ~Cercle() override {
            cout << "Destuction Cercle : ";
            affiche();
        }

        unique_ptr<Figure> copie() const override {
            return unique_ptr<Figure>(new Cercle(*this));
        }

        void affiche() const override {
            cout
                << "<Cercle id=" << &(*this)
                << " radius=" << radius
                << ">" << endl;
        }
};

class Carre: public Figure {
    private:
        double width;

    public:
        Carre(double width=1)
        :width(width) {}
        Carre(Carre const& other)
        :Figure(other), width(other.width) {
            cout << "Copie : ";
            affiche();
        }

        ~Carre() override {
            cout << "Destuction Carre : ";
            affiche();
        }

        unique_ptr<Figure> copie() const override {
            return unique_ptr<Figure>(new Carre(*this));
        }


        void affiche() const override {
            cout
                << "<Carre id=" << &(*this)
                << " width=" << width
                << ">" << endl;
        }
};

class Triangle: public Figure {
    private:
        double base;
        double height;

    public:
        Triangle(double base=1, double height=1)
        :base(base), height(height) {}
        Triangle(Triangle const& other)
        :Figure(other), base(other.base), height(other.height) {
            cout << "Copie : ";
            affiche();
        }

        ~Triangle() override {
            cout << "Destruction Triangle : ";
            affiche();
        }

        unique_ptr<Figure> copie() const override {
            return unique_ptr<Figure>(new Triangle(*this));
        }

        void affiche() const override {
            cout
                << "<Triangle id=" << &(*this)
                << " base=" << base
                << " height=" << height
                << ">" << endl;
        }
};


class Dessin {
    private:
        vector<unique_ptr<Figure>> figures;
    
    public:
        ~Dessin() {
            cout << "Destruction Dessin" << endl;
            while (!figures.empty()) {
                figures.pop_back();
            }
        }

        void ajouteFigure(Figure const& figure) {
            figures.push_back(figure.copie());
            cout << "Ajout Figure : ";
            figures.back()->affiche();
        }

        void affiche() const {
            for(auto& fig: figures) {
                fig->affiche();
            }
        }
};


int main() {
    Dessin dessin;
    dessin.ajouteFigure(Cercle(10));
    dessin.ajouteFigure(Carre(5));
    dessin.ajouteFigure(Triangle(10, 20));

    cout << endl << "Affichage" << endl;
    dessin.affiche();

    cout << endl << "Destruction" << endl;
    return 0;
}