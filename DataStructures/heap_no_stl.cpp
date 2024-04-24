#include <iostream>

class MinHeap {
private:
    int* heapArray;
    int capacity;
    int heapSize;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void heapifyUp(int index) {
        int temp = heapArray[index];
        while (index > 0 && temp < heapArray[parent(index)]) {
            heapArray[index] = heapArray[parent(index)];
            index = parent(index);
        }
        heapArray[index] = temp;
    }

    void heapifyDown(int index) {
        int smallest = index;
        while (smallest < heapSize / 2) {
            int left = leftChild(index);
            int right = rightChild(index);

            if (left < heapSize && heapArray[left] < heapArray[smallest]) {
                smallest = left;
            }

            if (right < heapSize && heapArray[right] < heapArray[smallest]) {
                smallest = right;
            }

            if (smallest != index) {
                std::swap(heapArray[index], heapArray[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }

public:
    MinHeap(int cap) : capacity(cap), heapSize(0) {
        heapArray = new int[capacity];
    }

    ~MinHeap() {
        delete[] heapArray;
    }

    void insert(int value) {
        if (heapSize == capacity) {
            std::cout << "Heap Overflow\n";
            return;
        }

        heapSize++;
        int i = heapSize - 1;
        heapArray[i] = value;

        heapifyUp(i);
    }

    void deleteMin() {
        if (heapSize <= 0) {
            std::cout << "Heap Underflow\n";
            return;
        }

        if (heapSize == 1) {
            heapSize--;
            return;
        }

        heapArray[0] = heapArray[heapSize - 1];
        heapSize--;

        heapifyDown(0);
    }

    int getMin() { return heapArray[0]; }

    void displayHeap() {
        std::cout << "Heap elements: ";
        for (int i = 0; i < heapSize; ++i) {
            std::cout << heapArray[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    MinHeap heap(10);
    heap.insert(3);
    heap.insert(2);
    heap.insert(15);
    heap.insert(5);
    heap.insert(4);
    heap.insert(45);

    heap.displayHeap();

    std::cout << "Minimum element: " << heap.getMin() << std::endl;

    heap.deleteMin();
    heap.displayHeap();

    std::cout << "Minimum element after deletion: " << heap.getMin() << std::endl;

    return 0;
}
