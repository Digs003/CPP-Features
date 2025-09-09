#include <iostream>
#include <cstddef>

template<typename T>
class DynamicArray {
    T* m_data;
    int m_length;
    void alloc(int length){
        m_data = new T[static_cast<std::size_t>(length)];
        m_length = length;
    }
    public:
    DynamicArray(int length){
        alloc(length);
    }
    ~DynamicArray(){
        delete[] m_data;
    }
    DynamicArray(const DynamicArray& arr){
        alloc(arr.m_length);
        std::copy_n(arr.m_data, m_length, m_data);
        std::cout << "Copy constructor called\n";
    }
    DynamicArray(DynamicArray&& arr) noexcept
        :m_data(arr.m_data), m_length(arr.m_length) {
            arr.m_length = 0;
            arr.m_data = nullptr;
            std::cout << "Move constructor called\n";
    }
    DynamicArray& operator=(const DynamicArray& arr){
        std::cout << "Copy assignment operator called\n";
        if(this == &arr){
            return *this;
        }
        delete[] m_data;
        alloc(arr.m_length);
        std::copy_n(arr.m_data, m_length, m_data);
        return *this;
    }
    DynamicArray& operator=(DynamicArray&& arr) noexcept {
        std::cout << "Move assignment operator called\n";
        if(this == &arr){
            return *this;
        }
        delete[] m_data;
        m_data = arr.m_data;
        m_length = arr.m_length;
        arr.m_length = 0;
        arr.m_data = nullptr;
        return *this;
    }
    int getLength() const {
        return m_length;
    }
    T& operator[](int index){
        return m_data[index];
    }
    const T& operator[](int index) const {
        return m_data[index];
    }
};

DynamicArray<int> cloneAndDouble(const DynamicArray<int>& arr) {
    DynamicArray<int> newArr(arr.getLength());
    for(int i = 0; i < arr.getLength(); i++){
        newArr[i] = arr[i] * 2;
    }
    return newArr;
}

int main() {
    DynamicArray<int> arr(20);
    for(int i=0;i < arr.getLength(); i++){
        arr[i] = i;
    }

    arr = cloneAndDouble(arr);

    for(int i = 0; i< arr.getLength(); i++){
        std::cout<< arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}