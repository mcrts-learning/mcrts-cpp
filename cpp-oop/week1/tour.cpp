#include <iostream>
using namespace std;

struct Papier {
    int age;
    int francs;
};

class Spectateur {
    public:
        void askAge() {
            age = 0;
            do {
                cout << "Quel âge ai-je ? ";
                cin >> age;
            } while (age <= 0 );
        }
        void askFrancs() {
            francs = 0;
            do {
                cout << "Combien d'argent ai-je en poche (<100) ? ";
                cin >> francs;
            } while (francs < 0 or francs >= 100);
        }
        void goOnStage() {
            cout << "[Spectateur] (j'entre en scène)" << endl;
            askAge();
            askFrancs();
            cout << "[Spectateur] (je suis là)" << endl;
        }

        Papier writeOnPaper() {
            cout << "[Spectateur] (j'écris le papier)" << endl
                 << "[Spectateur] (je montre le papier)" << endl;
            return Papier({age, francs});
        }
    private:
        int age;
        int francs;
};

class Assistant {
    public:
        int readPaper(Papier paper) {
            cout << "[Assistant] (je lis le papier)" << endl
                 << "[Assistant] (je calcule mentalement)" << endl;
            return (((paper.age * 2) + 5) * 50) + paper.francs - 365 + 115;
        }
};

class Magicien {
    public:
        void playATrick() {
            Spectateur s;
            s.goOnStage();
            cout << "[Magicien] un petit tour de magie..." << endl;
            Assistant a;
            int secret(a.readPaper(s.writeOnPaper()));
            secret = secret - 115 + 365;
            int francs(secret % 100);
            if (francs < 50) {
                francs += 50;
            } else {
                francs -= 50;
            }
            int age(secret / 50);
            age = age - 5;
            age = age / 2;
            cout << "[Magicien]" << endl
                 << "  - hum... je vois que vous êtes agé de " << age << " ans" << endl
                 << "    et que vous avez " << francs << " francs en poche !" << endl;
        }
};

int main() {
    Magicien m;
    m.playATrick();
}