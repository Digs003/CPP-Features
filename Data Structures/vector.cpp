#include <iostream>


template<typename T>
class Vector {
    private:
        T* data = nullptr;
        size_t size = 0;
        size_t capacity = 0;

        void Resize(size_t new_capacity){
            T* new_data = new T[new_capacity];

            if(new_capacity < size){
                size = new_capacity;
            }

            for(size_t i = 0; i < size; i++){
                new_data[i] = std::move(data[i]);
            }
            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }
    public:
        Vector(){
            Resize(2);
        }
        void PushBack(const T& value){
            if(size >= capacity){
                Resize(capacity + capacity/2);
            }
            data[size] = value;
            size++;
        }
        void PushBack(T&& value){
            if(size >= capacity){
                Resize(capacity + capacity/2);
            }
            data[size] = std::move(value);
            size++;
        }
        size_t Size() const {
            return size;
        }

        T& operator[](size_t index){
            return data[index];
        }
        const T& operator[](size_t index) const {
            return data[index];
        }
};

struct Vector3{
    float x = 0.0f,y = 0.0f,z = 0.0f;
    Vector3() {}
    Vector3(float val): x(val), y(val), z(val) {}
    Vector3(float x,float y,float z): x(x), y(y), z(z) {}
    Vector3(const Vector3& other): x(other.x), y(other.y), z(other.z) {
        std::cout << "Copy constructor called" << std::endl;
    }
    Vector3(Vector3&& other): x(other.x), y(other.y), z(other.z) {
        std::cout << "Move constructor called" << std::endl;
    }
    ~Vector3(){
        std::cout << "Destructor called" << std::endl;
    }
    Vector3& operator=(const Vector3& other){
        if(this != &other){
            std::cout << "Copy assignment operator called" << std::endl;
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }
    Vector3& operator=(Vector3&& other){
        if(this != &other){
            std::cout << "Move assignment operator called" << std::endl;
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }
};



template<typename T>
void PrintVector(const Vector<T>& vec){
    for(size_t i = 0; i< vec.Size(); i++){
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

template<>
void PrintVector(const Vector<Vector3>& vec){
    for(size_t i =0; i < vec.Size(); i++){
        const Vector3& v = vec[i];
        std::cout << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ") "<< std::endl;
    }
}

int main(){
    Vector<Vector3> v;
    v.PushBack(Vector3(1.0f, 2.0f, 3.0f));
    v.PushBack(Vector3(1.1f));
    v.PushBack(Vector3());
    PrintVector(v);
    return 0;
}