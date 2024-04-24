//
// Created by Furka on 11/2/2023.
//

/*
 ******************************======= Arrays vs Linked Lists =======******************************
 * Arrays have fixed size	                            vs 	Linked list size is dynamic
 * Insertion of new element is expensive	            vs  Insertion/deletion is easier
 * Random access is allowed                             vs  Random access not possible
 * Elements are at contiguous location	                vs 	Elements have non-contiguous location
 * No extra space is required for the next pointer	    vs 	Extra memory space required for next pointer
 *
******************************======= Some of the applications for linked lists are as follows: =======******************************
* A linked list can be used to implement stacks and queues.
* A linked list can also be used to implement graphs whenever we have to represent graphs as adjacency lists.
* A mathematical polynomial can be stored as a linked list.
* In the case of hashing technique, the buckets used in hashing are implemented using the linked lists.
* Whenever a program requires dynamic allocation of memory, we can use a linked list as linked lists work more efficiently in this case.

 */

#include <iostream>
using namespace std;

// Define linked list node
struct Node{
    int data;
    struct Node* next;
};



void displayList(struct Node** head){
    // Traverse list to display node
    struct Node* current_node = *head;
    cout<<"Node data: "<<current_node->data<<endl;
    while(current_node->next != nullptr){
        current_node = current_node->next;
        cout<<"Node data: "<<current_node->data<<endl;
    }
}

// Insert a new node in front of the list, (updates head)
void push(struct Node** head_ptr, int node_data){
    struct Node* temp_node = new Node; // create and allocate node
    temp_node->data = node_data; // assign data to node
    temp_node->next = *head_ptr; // set next of new node as head
    *head_ptr = temp_node;
};

// Insert a new node in front of the list, (updates head)
void push2(struct Node* head_ptr, int node_data){
    struct Node* temp_node = new Node; // create and allocate node
    temp_node->data = node_data; // assign data to node
    temp_node->next = head_ptr; // set next of new node as head
    head_ptr = temp_node;
//    head_ptr->data=-999;
};

// Insert a new node at the end of the list
void append(struct Node** head_ptr, int node_data){
    // create the new node
    struct Node* new_node = new Node; // == nullptr
    new_node->next = nullptr;
    new_node->data = node_data;
    // Iterate until finding the latest node
    struct Node* last_node = *head_ptr;
    /* if list is empty, new node becomes first node */
    if (*head_ptr == nullptr)
    {
        *head_ptr = new_node;
        return;
    }
    while(last_node->next != nullptr){
        last_node = last_node->next;
    }
    last_node->next = new_node; // Point next node as new node.
};

//insert new node after a given node
void insertAfter(struct Node* node_ptr, int node_data){
    // Create new node
    struct Node* new_node = new Node;
    new_node->data = node_data;
    new_node->next = node_ptr->next;
    node_ptr->next = new_node;
}


Node* getTail(struct Node** head_ptr){
    struct Node* last_node = *head_ptr;
    while(last_node->next != nullptr){
        last_node = last_node->next;
    }
    return last_node;
}

Node* removeFirstNode(struct Node** head_ptr){
    struct Node* temp_node = *head_ptr;
    *head_ptr = temp_node->next;
    return *head_ptr;
}

Node* removeLastNode(struct Node** head){
    struct Node* node_latest_pre = *head;
    while((node_latest_pre->next)->next!=nullptr){
        node_latest_pre = node_latest_pre->next;
    }
    node_latest_pre->next = nullptr;
    return node_latest_pre;
}



int main(){
    // Create linked-list
    struct Node* head = nullptr;
    push(&head, 1);

    struct Node* head2 = new Node;
    head2->data = 0;
    head2->next= nullptr;
    push2(head2, -9999);

    append(&head, 2);
    append(&head, 3);
    append(&head, 4);
    // Insert manually to check insert after
    struct Node* node_5 = new Node;node_5->data=5;
    struct Node* node_6 = new Node;node_6->data=6;
    struct Node* node_7 = new Node;node_7->data=7;
    struct Node* node_tail = getTail(&head);
    node_tail->next = node_5;
    node_5->next = node_6;
    node_6->next = node_7;
    node_7->next = nullptr;

    displayList(&head);

//    insertAfter(node_6, -3);
//    displayList(&head);
//
//    cout<<"After deletion of first node:"<<endl;
//    removeFirstNode(&head);
//    displayList(&head);
//
//    cout<<"After deletion of the latest node(tail):"<<endl;
//    removeLastNode(&head);
//    displayList(&head);

}