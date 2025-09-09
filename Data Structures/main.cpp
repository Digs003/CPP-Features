#include <iostream>
#include "vector3.h"

int main() {
    Vector<int> v = {1, 2, 3};
    v.push_back(4);
    v.push_back(5);

    std::cout << "Contents:";
    for (int i = 0; i < v.Size(); ++i) {
        std::cout << ' ' << v[i];
    }
    std::cout << "\nSize: " << v.Size()
              << ", Capacity: " << v.Capacity() << std::endl;

    v.pop_back();
    std::cout << "After pop_back(), size: " << v.Size() << std::endl;
    return 0;
}