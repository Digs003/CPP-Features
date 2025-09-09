#include <iostream>

template<typename T>
class Vector{
private:
    T* data;
    size_t size;
    size_t capacity;

    void reallocate(size_t newCapacity){
        T* new_data = new T[newCapacity];
        for(size_t i = 0; i<size; i++){
            new_data[i] = std::move(data[i]);
        }
        delete[] data;
        data = new_data;
        capacity = newCapacity;
    }

public:
    Vector() : data(nullptr), size(0), capacity(0) {}
    explicit Vector(int n) : data(n? new T[n]: nullptr), size(n), capacity(n) {} 

    Vector(std::initializer_list<T> init)
        : data(init.size()? new T[init.size()]: nullptr), size(init.size()), capacity(init.size()) 
    {
        std::copy(init.begin(), init.end(), data);
    }

    Vector(const Vector& other)
        : data(other.size?new T[other.size]: nullptr), size(other.size), capacity(other.capacity)
    {
        std::copy(other.data, other.data + other.size, data);
    }

    Vector(Vector&& other) noexcept
        : data(other.data), size(other.size), capacity(other.capacity)
    {
        other.data = nullptr;
        other.size = 0;
        other.capcity = 0;
    }

    Vector& operator=(const Vector& other){
        if(this!=&other){
            T* newData = other.capacity ? new T[other.capacity] : nullptr;
            std::copy(other.data, other.data + other.size, newData);
            delete[] data;
            data = newData;
            size = other.size;
            capcity = other.capacity;
        }
        return *this;
    }

    Vector& operator=(Vector&& other){
        if(this!=&other){
            delete[] data;
            data = other.data;
            size = other.size;
            capacity = other.capacity;
            other.data = nullptr;
            other.size = other.capacity = 0;
        }
        return *this;
    }

    ~Vector(){
        delete [] data;
    }

    T& operator[](size_t idx){
        return data[idx];
    }
    const T& operator[](size_t idx) const {
        return data[idx];
    }

    size_t Size() const {
        return size;
    }
    size_t Capacity() const {
        return capacity;
    }

    void clear(){
        size = 0;
    }

    void reserve(size_t newCapacity){
        if(newCapacity > capacity){
            reallocate(newCapacity);
        }
    }

    void push_back(const T& value){
        if(size == capacity){
            reserve(capacity? capacity*2 : 1);
        }
        data[size++] = value;
    }

    void push_back(T&& value){
        if(size == capacity){
            reserve(capacity? capacity*2 : 1);
        }
        data[size++] = std::move(value);//static_cast<T&&>(value)
    }



};