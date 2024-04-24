#include<iostream>
using namespace std;

#define MAX 1000 //max size for stack

class Stack
{
    private:
        int top = -1;
        int arr[MAX];
    public:
        bool push(int item);
        int pop();
        bool isEmpty();
        bool isFull();
        int peek();
        void clear();
};

bool Stack::push(int item){
    if(isFull()){
       return false; 
    }
    cout<<"item: "<<item<<" is pushed.\n";
    arr[++top] = item;
    return true;
}

int Stack::pop(){
    if(isEmpty()){
        return -1;
    }
    int item = arr[top];
    cout<<"item: "<<item<<" is pushed.\n";
    top--;
    return item;
}

bool Stack::isEmpty(){
    if(top==-1){
        return true;
    }
    return false;
}

bool Stack::isFull(){
    if(top==MAX-1){
        return true;
    }
    return false;
}

int Stack::peek() {
    if(isEmpty()){
        return -1;
    }
    return arr[top];
}

void Stack::clear() {top=-1;}

// main program to demonstrate stack functions
int main()
{
    Stack stack;
    cout<<"The Stack Push "<<endl;
    stack.push(2);
    stack.push(4);
    stack.push(6);
    cout<<"The Stack Pop : "<<endl;
    while(!stack.isEmpty())
    {
        stack.pop();
    }
    return 0;
}