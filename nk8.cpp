#include <iostream>
using namespace std;

class Base {
    int baseData = 100;
public:
    virtual void show() { cout << "Base: " << baseData; }
    virtual ~Base() = default;
};

class Derived1 : virtual public Base {
    int d1Data = 200;
public:
    void show() override { cout << "D1: " << d1Data; }
};

class Derived2 : virtual public Base {
    int d2Data = 300;
public:
    void show() override { cout << "D2: " << d2Data; }
};

class Multiple : public Derived1, public Derived2 {
    int mData = 400;
public:
    void show() override { cout << "Multiple: " << mData; }
};

void processBase(Base obj) {  // ❗ Passed by value — this causes slicing
    obj.show();
}

int main() {
    Multiple m;
    processBase(m);  // ❓ What happens here?
}
