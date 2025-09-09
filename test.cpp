#include <iostream>
struct T{
    T(){
        std::cout << "Default constructor called" << std::endl;
    }   
    T(int){
        std::cout << "Parameterized constructor called" << std::endl;
    }
    T(const T&){
        std::cout << "Copy constructor called" << std::endl;
    }
    T(T&&){
        std::cout << "Move constructor called" << std::endl;
    }
};

T foo(int x){
    T temp(x);        // parameterized constructor
    T temp2(temp);    // copy constructor
    return temp2;     // move constructor
}

int main(){
    int i = 4;
    T x = foo(i);
}