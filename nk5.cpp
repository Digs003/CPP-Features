#include <iostream>

int main() {
    int arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int (*ptr)[3] = arr;

    std::cout << *(*(ptr + 1) + 1) << " ";
    std::cout << *(*(ptr + 2) + 0) << " ";
    std::cout << *(*(ptr + 0) + 5) << std::endl;

    return 0;
}
