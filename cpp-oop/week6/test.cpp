#include <iostream>
using namespace std;

class Vehicle {
public:
    virtual void honk() = 0;
};

class Car : public Vehicle {
public:
    void honk() { cout << "Beep!"; }
};

class Boat : public Vehicle {
public:
    void honk() { cout << "Toot!"; }
};

class Hovercraft : public Car, public Boat {
public:
    using Car::honk;
};

int main(){
    Hovercraft h;
    h.honk();
    return 0;
}