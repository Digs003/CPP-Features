#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> mp;
    mp["hello"] = 1;

    for (const std::pair<std::string, int>& p : mp) {
        std::cout << p.second;
        mp[p.first]++;
        std::cout << p.second;
    }

    return 0;
}
