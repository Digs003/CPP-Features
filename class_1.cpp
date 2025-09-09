#include <iostream>
#include <string>
#include <string_view>

class Employee {
    private:
        std::string m_name;
    public:
        void setName(std::string_view name){
            m_name = name;
        }
        const std::string& getName() const {
            return m_name;
        }
};

Employee createEmployee(std::string_view name) {
    Employee emp;
    emp.setName(name);
    return emp; // rvalue is returned
}

int main() {
    //Case 1
    std::cout << createEmployee("John Doe").getName() << std::endl; 

    //Case 2
    const std::string& name = createEmployee("Jane Doe").getName(); // ❌ Error: dangling reference
    std::cout << name << std::endl; // This will lead to undefined behavior

    //Case 3
    std:: string name2 = createEmployee("Alice Smith").getName(); // OK: a copy is made
    std::cout << name2 << std::endl; // This is safe

    return 0;
}