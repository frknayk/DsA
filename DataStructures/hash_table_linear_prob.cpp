#include <iostream>
#include <vector>

class HashTableLinearProbing {
private:
    struct KeyValue {
        int key;
        int value;
        bool occupied;

        KeyValue() : key(-1), value(-1), occupied(false) {}
    };

    std::vector<KeyValue> table;
    size_t size;

public:
    HashTableLinearProbing(size_t initialSize) : size(initialSize) {
        table.resize(size);
    }

    size_t hashFunction(int key) {
        return key % size;
    }

    void insert(int key, int value) {
        size_t index = hashFunction(key);

        while (table[index].occupied) {
            index = (index + 1) % size; // Move to the next slot
        }

        table[index].key = key;
        table[index].value = value;
        table[index].occupied = true;
    }

    int search(int key) {
        size_t index = hashFunction(key);
        size_t originalIndex = index;

        while (table[index].key != key) {
            if (!table[index].occupied || index == (originalIndex - 1) % size) {
                return -1; // Key not found
            }
            index = (index + 1) % size; // Move to the next slot
        }

        return table[index].value; // Return the value associated with the key
    }

    void remove(int key) {
        size_t index = hashFunction(key);
        size_t originalIndex = index;

        while (table[index].key != key) {
            if (!table[index].occupied || index == (originalIndex - 1) % size) {
                return; // Key not found
            }
            index = (index + 1) % size; // Move to the next slot
        }

        table[index].key = -1;
        table[index].value = -1;
        table[index].occupied = false;
    }
};

int main() {
    HashTableLinearProbing hash(10);

    hash.insert(5, 50);
    hash.insert(15, 150);
    hash.insert(25, 250);

    std::cout << "Value for key 15: " << hash.search(15) << std::endl;

    hash.remove(15);

    std::cout << "Value for key 15 after removal: " << hash.search(15) << std::endl;

    return 0;
}
