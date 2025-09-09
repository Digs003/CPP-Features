#include <iostream>
#include <list>

template <typename K,typename V>
class UnorderedMapProbing {
private:
    static const int defaultSize = 10;
    std::pair<K, V>* table;
    int capacity;
    int count;
    bool* occupied;

    int hash(const K& key) const {
        return key % capacity;
    }
public:
    UnorderedMapProbing(int size = defaultSize): capacity(size), count(0){
        table = new std::pair<K, V>[capacity];
        occupied = new bool [capacity]();// Initialize occupied array to false
    }
    ~UnorderedMapProbing() {
        delete[] table;
        delete[] occupied;
    }
    void insert(const K& key, const T& value){
        int hashedKey = hash(key);
        while(occupied[hashedKey] && table[hashedKey].first != key){
            hashedKey = (hashedKey + 1) % capacity;
        }
        if(!occupied[hashedKey]){
            occupied[hashedKey] = true;
            count++;
        }
        table[hashedKey] = std::make_pair(key, value);
    }

    bool get(const K& key, V& value) const {
        int hashedKey = hash(key);
        int start = hashedKey; // Store the starting point to avoid infinite loop
        while(occupied[hashedKey] && table[hashedKey].first != key){
            hashedKey = (hashedKey + 1)%capacity;
            if(start == hashedKey){
                return false;
            }
        }
        if(occupied[hashedKey]){
            value = table[hashedKey].second;
            return true;
        }
        return false;
    }

    bool erase(const K& key){
        int hashedKey = hash(key);
        int start = hashedKey; // Store the starting point to avoid infinite loop
        while(occupied[hashedKey] && table[hashedKey].first != key){
            hashedKey = (hashedKey + 1)%capacity;
            if(start == hashedKey){
                return false;
            }
        }
        if(occupied[hashedKey]){
            occupied[hashedKey] = false; 
            count--;
            value = table[hashedKey].second;
            return true;
        }
        return false;
    }
};