//
// Created by Furkan on 11/5/2023.
//

#include <iostream>
using namespace std;

struct Node{
    struct Node* next;
    struct Node* prev;
    int data;
};


// Get the latest node(tail)
    Node* getTail(Node* head_ptr){
        // Find latest node
        struct Node* tail = head_ptr;
        while(tail->next!=nullptr){
            tail = tail->next;
        }
        return tail;
}

// Add new node top of the linked-list
void push(Node** head_ptr, int data){
    //Node** head_ptr means ==> struct Node** head_ptr = &head;
    struct Node* new_node = new Node;
    new_node->data = data;
    new_node->prev = nullptr;
    new_node->next = *head_ptr;
    *head_ptr = new_node;
}

// Add new node end of the linked-list
void append(Node** head_ptr, int data){
    // Find latest node
    struct Node* tail = getTail(*head_ptr);
    struct Node* tail_new = new Node;
    tail_new->prev = tail;
    tail_new->next = nullptr;
    tail_new->data = data;
    tail->next = tail_new;
}

// Insert new node after given node
void insertAfter(Node* node_ptr, int data){
    struct Node* node_new = new Node;
    node_new->data = data;
    node_new->prev = node_ptr;
    node_new->next = node_ptr->next;
    node_ptr->next = node_new;
}

// Insert new node before given node
void insertBefore(Node** node_ptr, int data){
    struct Node* node_new = new Node;
    node_new->prev = (*node_ptr)->prev;

    
}

// Remove given node from the top of the linked-list
void removeHead(Node** node_ptr);

// Remove given node from the tail of the linked-list
void removeTail(Node** head_ptr);

// Print all linked-list 
void displayLinkedList(Node** head_ptr){
    struct Node* node_current = *head_ptr;
    cout<<"===== Linked-List ======"<<endl;
    cout<<node_current->data<<", ";
    while(node_current->next==nullptr){
        cout<<node_current->data<<", ";
    }
    cout<<"----- END of the Linked-List-----"<<endl;
}




int main(){
//     Create linked-list
    struct Node* head = nullptr;
    struct Node** head_ptr = &head;
    push(&head, 1);
//    int a = 5;
//    int *ptr = &a;
//    int **ptr2 = &ptr;
//    bool is_equal_1 = *ptr2 == &a;
//    cout << is_equal_1 << endl;
//
//    append(&head, 2);
//    append(&head, 3);
//    append(&head, 4);
//    displayLinkedList(&head);

    // // Insert manually to check insert after
    // struct Node* node_5 = new Node;node_5->data=5;
    // struct Node* node_6 = new Node;node_6->data=6;
    // struct Node* node_7 = new Node;node_7->data=7;
    // struct Node* node_tail = getTail(&head);
    // node_tail->next = node_5;
    // node_5->next = node_6;
    // node_6->next = node_7;
    // node_7->next = nullptr;
    // insertAfter(node_6, -3);
    // displayList(&head);
    // cout<<"After deletion of first node:"<<endl;
    // removeFirstNode(&head);
    // displayList(&head);
    // removeLastNode(&head);
    // cout<<"After deletion of the latest node(tail):"<<endl;
    // displayList(&head);
    return 0;
}