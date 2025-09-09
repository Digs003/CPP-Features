#include <iostream>

struct Foo {
    Foo(int x = 0) { std::cout << "Constructor called\n"; }
};

int main() {
    Foo foo1{};  // ✅ prints "Constructor called"
    Foo foo2;    // ✅ prints "Constructor called"
    Foo foo3();  // ❌ no constructor call — declares a function!
    Foo(1);    // Function-style cast of literal 1, returns temporary Foo (similar to `Foo { 1 }`)
    Foo(bar);  // Defines variable bar of type Foo (inconsistent with `Foo { bar }` and `Foo(1)`)
}
