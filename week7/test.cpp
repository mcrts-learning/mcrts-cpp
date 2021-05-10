#include<iostream>
#include<memory>
using namespace std;

int construct(){
    int a(10);
    cout << "in constructor <adr=" << &a << " value=" << a << ">" << endl;
    return a;
}

int main() {
    int a(construct());
    cout << "in main        <adr=" << &a << " value=" << a << ">" << endl;
    return 0;
}