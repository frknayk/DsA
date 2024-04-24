#include <iostream>
#define MAX_SIZE 50

using namespace std;

class Queue{
    private:
        int front=0;
        int back=-1;
        int num_items=0;
        int arr[MAX_SIZE];

    public:
        bool enqueue(int item);
        int dequeue();
        bool isFull() const;
        bool isEmpty() const;
        void clear();
        int peek_front();
        int peek_back();
        void displayQueue();

};

bool Queue::enqueue(int item) {
    if(this->isFull())
    {
        return false;
    }
    back = (back+1) % MAX_SIZE;
    arr[back] = item;
    num_items++;
    return true;
}

int Queue::dequeue() {
    if(this->isEmpty()){
        return -1;
    }
    int item = arr[front];
    front = (front+1) % MAX_SIZE;
    num_items--;
    return item;
}

bool Queue::isFull() const{
    if(front == MAX_SIZE-1){
        std::cout<<"Queue is full.\n";
        return true;
    }
    return false;
}

bool Queue::isEmpty() const {
    if(num_items==0){
        std::cout<<"Queue is empty.\n";
        return true;
    }
    return false;
}

void Queue::displayQueue(){
    std::cout<<"Queue: \n";
    for(int i=front;i<=back;i++){
        std::cout<<arr[i]<<',';
    }
    std::cout<<'\n';
}

int Queue::peek_back() {
    if(isEmpty()){
        return -1;
    }
    return arr[back];
}

int Queue::peek_front() {
    if(isEmpty()){
        return -1;
    }
    return arr[front];
}


int main()
{
    Queue queue;
    queue.dequeue();      //deQueue
    cout<<"Queue created:"<<endl;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);
    queue.enqueue(50); //enqueue 60 => queue is full
    queue.enqueue(60);
    queue.displayQueue();

    //deQueue =>removes 10
    queue.dequeue();

    //queue after dequeue
    queue.displayQueue();

    return 0;
}