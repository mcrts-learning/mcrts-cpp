#include <iostream>
using namespace std;

int demander_annee() {
    int a(0);
    do {
        cout << "Entrez une annee (1583-4000) : ";
        cin >> a;
    } while (a < 1583 or a > 4000);
    return a;
}

void affiche_date(int year, int jour) {
    cout << "Date de Paques en " << year << " : ";
    if (jour <= 31) {
        cout << jour << " mars" << endl;
    } else {
        cout << jour - 31 << " avril" << endl;
    }
}

int date_Paques(int year) {
    int siecle(year / 100);
    int p((13 + (8 * siecle)) / 25);
    int q(siecle / 4);
    int m((15 - p + siecle - q) % 30);
    int n((4 + siecle - q) % 7);
    int d((m + (19 * (year % 19))) % 30);
    int e((2 * (year % 4) + 4 * (year % 7) + 6 * d + n) % 7);

    int jour(e + d + 22);
    if (e == 6 and (d == 29 or (d == 28 and ((11 * (m + 1)) % 30 < 19 )))) {
        jour -= 7;
    }
    return jour;
}

int main() {
    int year(demander_annee());
    affiche_date(year, date_Paques(year));
    return 0;
}