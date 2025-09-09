#include <iostream>

template<typename T, size_t S>
class Array {
    private:
        T arr[S];
    public:
        size_t Size() const {
            return S;
        }
        T& operator[](size_t index){
            return arr[index];
        }
        const T& operator[](size_t index) const{
            return arr[index];
        }
        T* Data() {
            return arr;
        }
        const T* Data() const {
            return arr;
        }
};



int main(){
    Array<int, 5> a;
    std::cout << "Size of array: " << a.Size() << std::endl;
    for(int i = 0; i < a.Size(); i++){
        a[i] = i * 10; 
        std::cout << "Element at index " << i << ": " << a[i] << std::endl;
    }

    const auto& b = a;
    for(int i = 0; i < b.Size(); i++){
        std::cout << "Element at index " << i << " in const reference: " << b[i] << std::endl;
    }

    memset(a.Data(), 0, a.Size() * sizeof(int));

    return 0;

}