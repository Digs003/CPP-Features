#include <iostream>

// This program demonstrates reading an integer and a string from standard input
// If i dont use std::ws, it will consume the newline character left in the input buffer after reading the integer
int main(){
    int num;
    std::cin >> num;
    std::cout << "You entered: " << num << std::endl;
    std::cout << "Enter a string: ";
    std::string str;
    getline(std::cin>>std::ws, str);
    std::cout << str << std::endl;
    return 0;
}