#include <iostream>

class PriorityQueue {
private:
    int* heap;
    int capacity;
    int size;

    // Helper functions for heap operations
    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap[parentIndex] > heap[index]) {
                std::swap(heap[parentIndex], heap[index]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int smallest = index;
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;

        if (leftChild < size && heap[leftChild] < heap[smallest]) {
            smallest = leftChild;
        }

        if (rightChild < size && heap[rightChild] < heap[smallest]) {
            smallest = rightChild;
        }

        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    explicit PriorityQueue(int capacity) : capacity(capacity), size(0) {
        heap = new int[capacity];
    }

    ~PriorityQueue() {
        delete[] heap;
    }

    void enqueue(int value) {
        if (size == capacity) {
            std::cerr << "Queue is full!" << std::endl;
            return;
        }

        heap[size] = value;
        heapifyUp(size);
        size++;
    }

    int dequeue() {
        if (size == 0) {
            std::cerr << "Queue is empty!" << std::endl;
            return -1; // Or any suitable default value
        }

        int front = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        return front;
    }

    bool isEmpty() {
        return size == 0;
    }
};

int main() {
    PriorityQueue pq(5);
    
    pq.enqueue(3);
    pq.enqueue(2);
    pq.enqueue(5);
    pq.enqueue(1);

    while (!pq.isEmpty()) {
        std::cout << pq.dequeue() << " ";
    }
    
    return 0;
}
