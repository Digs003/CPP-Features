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
    using Base::print; // make all Base::print() functions eligible for overload resolution
    void print(double) { std::cout << "Derived::print(double)\n"; }
};


int main()
{
    Derived d{};
    d.print(5); // calls Base::print(int), which is the best matching function visible in Derived

    return 0;
}