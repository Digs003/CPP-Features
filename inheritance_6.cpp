#include <iostream>

class Base
{
public:
    void print(int)    { std::cout << "Base::print(int)\n"; }
    void print(double) { std::cout << "Base::print(double)\n"; }
};

class Derived: public Base
{
public:
    void print(double) { std::cout << "Derived::print(double)"; } // this function added
};


int main()
{
    Derived d{};
    d.print(5); // calls Derived::print(double), not Base::print(int)

    return 0;
}