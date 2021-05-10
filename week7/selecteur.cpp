#include<iostream>
using namespace std;

int choice() {
    int choix(0);
    do {
        cout << "make a choice (1, 2 or 3) : ";
        cin >> choix;
    } while (choix < 1 or choix > 3);
    return choix;
}

int main() {
    double valeur1(1);
    double valeur2(2);
    double valeur3(3);
    double* choix;
    switch (choice()) {
    case 1:
        choix = &valeur1;
        break;
    case 2:
        choix = &valeur2;
        break;
    case 3:
        choix = &valeur3;
        break;
    default:
        break;
    }
    cout << "Vous avez choisi : " << *choix << endl;
    return 0;
}