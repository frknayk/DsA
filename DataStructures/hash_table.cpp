#include <iostream>

class Node {
public:
    int key;
    Node* next;
    int value;
    Node(int key_, int value_){
        value = value_;
        key = key_;
        next = nullptr;
    }
};

class HashTable {
private:
    size_t size;
    Node** table;

public:
    HashTable(size_t initial_size){
        size = initial_size;
        table = new Node*[initial_size]; //!DO NOT FORGET THIS LINE
        for (size_t i=0;i<size;++i){
            table[i] = nullptr;
        }
    }

    size_t hashFunction(int key) {
        return key % size;
    }

    void insert(int key, int value) {
        size_t index = hashFunction(key);
        Node* current = table[index];
        // Inserting a node to this key for the first time.
        if(current == nullptr){
            table[index] = new Node(key, value);
            return;
        }
        // Key is already exists, add to linked-list.
        while(current->next){
            current = current->next;
        }
        current->next = new Node(key, value);;
    }

    int search(int key) {
        size_t index = hashFunction(key);
        Node* current = table[index];
        while(current){
            if(current->key == key){
                return true;
            }
            current = current->next;
        }
        return -1; // Not found
    }

    void remove(int key) {
        size_t index = hashFunction(key);
        Node* current = table[index];
        Node* prev;
        while (current)
        {
            if(current->key == key){
                if(prev== nullptr){
                    table[index] = current->next;
                }
                else{
                    prev->next = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    ~HashTable() {
        Node* current;
        for(size_t i=0; i<size; ++i)
        {
            current = table[i];
            while (current)
            {
                Node* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
        delete[] table;
    }

};

int main() {
    size_t size_table = 250;
    HashTable hash(size_table);

    hash.insert(5, 50);
    hash.insert(5, 29);
    hash.insert(15, 150);
    hash.insert(25, 250);
    hash.insert(25, 251);
    std::cout << "Value for key 15: " << hash.search(15) << std::endl;
    hash.remove(15);
    std::cout << "Value for key 15 after removal: " << hash.search(15) << std::endl;
    std::cout << "Value for key 25: " << hash.search(25) << std::endl;

    return 0;
}
