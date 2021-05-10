#include <iostream>
#include <string>
using namespace std;

char decale(char c, char debut, int decalage);
char code(char c, int decalage);
string code(string s, int decalage);
string decode(string s, int decalage);


char decale(char c, char debut, int decalage) {
    while (decalage < 0) {
        decalage += 26;
    }
    return debut + (((c - debut) + decalage) % 26);
}

char code(char c, int decalage) {
    if (c >= 'a' and c <= 'z') {
        return decale(c, 'a', decalage);
    } else if (c >= 'A' and c <= 'Z') {
        return decale(c, 'A', decalage);
    } else {
        return c;
    }
}

string code(string s, int decalage) {
    string encoded;
    for (auto c : s) {
        encoded += code(c, decalage);
    }
    return encoded;
}

string decode(string s, int decalage) {
    return code(s, -decalage);
}

int main() {
    string s("Avez-vous vu mes 3 chats et mes 2 chiens ?");
    cout << s << endl << code(s, 4) << endl << decode(code(s, 4), 4) << endl;
    return 0;
}