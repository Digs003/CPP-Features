#include <initializer_list>
#include <algorithm>
#include <utility>

template<typename T>
class Vector{
    T* data;
    size_t size;
    size_t capacity;
    void reallocate(size_t new_capactiy){
        T* new_data =new T[new_capactiy];
        for(size_t i = 0; i < size; i++){
            new_data[i] = std::move(data[i]);
        }
        delete[] data;
        data = new_data;
        capacity = new_capactiy;
    }
public:
    Vector() : data(nullptr), size(0), capacity(0) {}

    explicit Vector(size_t n)
        : data(n? new T[n]: nullptr), size(n), capacity(n) {}
    // Because of explcit, vector<int> v = 5;//error
    // vector<int> v(5); // ok

    Vector(std::initializer_list<T> init)
        : data(init.size() ? new T[init.size()] : nullptr),
            size(init.size()), capacity(init.size()) 
    {
        std::copy(init.begin(), init.end(), data);
    }

    Vector(const Vector& other)
        : data(other.capacity ? new T[other.capacity] : nullptr),
          size(other.size), capacity(other.capacity) 
    {
        std::copy(other.data, other.data + other.size, data);
    }

    Vector(Vector&& other) noexcept
        : data(other.data), size(other.size), capacity(other.capaciy)
    {
        other.data = nullptr;
        other.size = other.capacity = 0;
    }

    // Vector<int> d = std::move(a); // move‐ctor: “steal” a’s buffer
    /*
        Vector<int> makeVec() {
        Vector<int> tmp{1,2,3};
        return tmp;            // often elided (no copy/move), but if not:
                                // move‐ctor (since C++11) will be used
        }
        auto v = makeVec();      // v is constructed via move‐ctor (or via RVO, no ctor)
    */

    Vector& operator=(const Vector& other){
        if(this != &other){
            T* newData = other.capacity ? new T[other.capacity] : nullptr;
            std::copy(other.data,other.data +other.size, newData);
            delete[] data;
            data = newData;
            size = other.size;
            capacity = other.capacity;
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if(this != &other){
            delete[] data;
            data =other.data;
            size = other.size;
            capacity = other.capacity;
            other.data = nullptr;
            other.size = other.capacity = 0;
        }
        return *this;
    }

    ~Vector() {
        delete[] data;
    }

    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }

    T& front() { return data[0]; }
    const T& front() const { return data[0]; }
    T& back() { return data[size - 1]; }
    const T& back() const { return data[size - 1]; }

    // iterator begin() { return data; }
    // const_iterator begin() const { return data; }
    // iterator end() { return data + size; }
    // const_iterator end() const { return data + size; }

    bool empty() const { return size == 0; }
    size_t Size() const { return size; }
    size_t Capacity() const { return capacity; }

    void reserve(size_t new_capacity) {
        if(new_capacity > capacity){
            reallocate(new_capacity);
        }
    }

    void shrink_to_fit() {
        if(size < capacity){
            reallocate(size);
        }
    }

    void clear() { size = 0; }

    void push_back(const T& value){
        if(size == capacity){
            reserve(capacity ? capacity*2 : 1);
        }
        data[size++] = value;
    }

    void push_back(T&& value){
        if(size==capacity){
            reserve(capacity ? capacity*2 : 1);
        }
        data[size++] = std::move(value);
    }
    // emplace_back: construct T in-place from arbitrary args
    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (size == capacity) {
            reserve(capacity ? capacity * 2 : 1);
        }
        data[size] = T(std::forward<Args>(args)...);
        ++size;
    }

    void pop_back(){
        if(size > 0) --size;
    }    
};