#include <iostream>

struct my_company_struct {
    int data[2];
    my_company_struct(int x, int y) : data{x, y} {}
    virtual void f() {}
};

int main() {
    my_company_struct nk_securities(1, 2);
    int* mcs = (int *)(&nk_securities);
    std::cout << mcs[2] << std::endl;
}
