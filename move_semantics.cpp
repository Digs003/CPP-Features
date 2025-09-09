#include <iostream>

class String{
    private:
        char* data;
        uint32_t size;
    public:
        String(const char* str)
        {
            std::cout<< "Constructor called" << std::endl;
            size = strlen(str);
            data = new char[size];
            memcpy(data,str,size);
        }   
        String(const String& other)
        {
            std::cout<< "Copy constructor called" << std::endl;
            size = other.size;
            data = new char[size];
            memcpy(data,other.data,size);
        }
        String(String&& other) noexcept
        {
            std::cout<< "Move constructor called" << std::endl;
            size = other.size;
            data = other.data;
            other.data = nullptr;
            other.size = 0;
        }
        String& operator=(const String& other)
        {
            std::cout<< "Copy assignment operator called" << std::endl;
            if(this != &other){
                delete[] data;
                size = other.size;
                data = new char[size];
                memcpy(data, other.data, size);
            }
            return *this;
        }
        String& operator=(String&& other) noexcept
        {
            std::cout<< "Move assignment operator called" << std::endl;
            if(this != &other){
                delete[] data;
                size = other.size;
                data = other.data;
                other.data = nullptr;
                other.size = 0;
            }
            return *this;
        }
        void Print() const 
        {
            if(data){
                std::cout << "String: " << data << std::endl;
            } else {
                std::cout << "String: " << std::endl;
            }
        }
        ~String()
        {
            std::cout<< "Destructor called" << std::endl;
            delete[] data;
        }
};

class Entity{
    private:
        String name;
    public:
        Entity(const String& str)
            : name(str)
        {
        }
        Entity(String&& str)
            : name(std::move(str))
        {
        }
        void PrintName() const{
            name.Print();
        }
};

int main(){
    //Entity e("Hello world");
    //e.PrintName();
    String s = "Move semantics in C++";

    s.Print();
    // String t = (String&&)s;
    // String t((String&&)s);
    String t = std::move(s); // Calls move constructor
    s.Print(); // s is now in a valid but unspecified state
    String s2= "Another string";
    s2.Print();
    t = std::move(s2); // Calls move assignment operator
    s2.Print(); // s2 is now in a valid but unspecified state
    t.Print();
    return 0;
}
