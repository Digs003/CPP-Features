#include <iostream>
#include <cstring>

class String{
private:
    char* data;
    size_t length;
public:
    String() : data(new char[1]{'\0'}), length(0) {}

    String(const char* str) {
        length = std::strlen(str);
        data = new char[length + 1];
        std::strcpy(data, str);
    }

    String(const String& other){
        length = other.length;
        data = new char[length + 1];
        std::strcpy(data, other.data);
    }

    String(String&& other) noexcept: data(other.data), length(other.length){
        other.data = nullptr;
        other.length = 0;
    }

    String& operator=(const String& other){
        if(this != &other){
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            std::strcpy(data, other.data);
        }
        return *this;
    }

    String& operator=(String&& other) noexcept{
        if(this!=&other){
            delete[] data;
            data = other.data;
            length = other.length;
            other.data = nullptr;
            other.length = 0;
        }
        return *this;
    }

    ~String(){
        delete[] data;
    }

    char& operator[](size_t idx){
        return data[idx];
    }
    const char& operator[](size_t idx) const {
        return data[idx];
    }
    size_t size() const{
        return length;
    }

    void push_back(char c){
        char* new_data = new char[length + 2];
        std::strcpy(new_data, data);
        new_data[length] = c;
        new_data[length + 1] = '\0';
        delete[] data;
        data = new_data;
        ++length;
    }
};