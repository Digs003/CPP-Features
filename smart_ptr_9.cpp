#include <iostream>
#include <memory>
#include <utility> 

class Resource {
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource released\n"; }
};

int main(){
    std::unique_ptr<Resource> res1{new Resource()};
    std::unique_ptr<Resource> res2;

    std::cout << "res1 is " << (res1 ? "not null\n" : "null\n");
	std::cout << "res2 is " << (res2 ? "not null\n" : "null\n");

    res2 = std::move(res1);

    std::cout << "res1 is " << (res1 ? "not null\n" : "null\n");
	std::cout << "res2 is " << (res2 ? "not null\n" : "null\n");

    return 0;
}