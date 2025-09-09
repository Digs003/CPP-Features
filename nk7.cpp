#include <iostream>
using namespace std;

class Base1 {
protected:
    int value = 10;
public:
    virtual void show() { cout << "Base1: " << value << endl; }
};

class Base2 {
protected:
    int value = 20;
public:
    virtual void show() { cout << "Base2: " << value << endl; }
    void display() { cout << "Base2 display" << endl; }
};

class Derived : public Base1, private Base2 {
public:
    void show() override {
        cout << "Derived: " << Base1::value << ", " << Base2::value << endl;
    }

    using Base2::display;  // Make display() public

    void test() {
        Base1::show();      // Line 1
        Base2::show();      // Line 2
        display();          // Line 3
    }
};

void externalTest() {
    Derived d;
    d.show();              // Line 4
    d.display();           // Line 5

    Base1* ptr1 = &d;
    ptr1->show();          // Line 6

    //Base2* ptr2 = &d;   // Line 7 - Invalid: Base2 is privately inherited
}

int main() {
    externalTest();
    return 0;
}
