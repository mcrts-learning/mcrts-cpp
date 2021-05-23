#include <iostream>
using namespace std;

class Base {
public:
    virtual void print() const = 0;
};

class A : public Base {
public:
    void print() const {cout << "A";}
};

class B : public Base {
public:
    void print() const {cout << "B";}
};

class Actor {
public:
    const Base& base;
    Actor(Base const& base): base(base) {}
    void print() const {base.print(); cout << endl;}
};

int main(){
    A a;
    B b;
    Actor a1(a);
    Actor a2(b);
    a1.print();
    a2.print();
    return 0;
}