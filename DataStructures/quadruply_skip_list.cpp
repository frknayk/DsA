#include <iostream>
#include <cstdlib>
#include <random>

using namespace std;

// Node structure for the Skip List
struct Node {
    int data;
    Node *next;
    Node *prev;
    Node *below;
    Node *above;

    Node(int val) : data(val), next(nullptr), prev(nullptr), below(nullptr), above(nullptr) {}
};

class SkipList {
private:
    Node *head;
    int maxLevel;
    int currentLevel;

public:
    SkipList() {
        head = new Node(INT_MIN); // Head node with the minimum integer value
        maxLevel = 1;
        currentLevel = 1;
    }

    // Insert a new element into the Skip List
    void insert(int val) {
        Node *curr = head;
        Node *insertedNode = nullptr;
        Node *prevLevelNode = nullptr;

        /*
        * Step-1: Start by top-left node and this line to find where value is suitable
        * Step-2: If top line is not suitable look for the lower line, continue this 
        * until finding the right place. 
        * Step-3: If right place is found, create new node for given value and 
        * re-arrange nodes accordingly.
        * Step-4:
        */
        while (curr) {
            // Find the node where the value is fitted
            while (curr->next && curr->next->data < val) {
                curr = curr->next;
            }
            // Update node level (line)
            if (curr->below) {
                prevLevelNode = curr;
                curr = curr->below;
            }

            // Reached most bottom line.
            else {
                insertedNode = new Node(val);
                insertedNode->next = curr->next;
                insertedNode->prev = curr;
                if (curr->next) {
                    curr->next->prev = insertedNode;
                }
                curr->next = insertedNode;

                if (prevLevelNode && insertedNode) {
                    insertedNode->above = insertedNode;
                    insertedNode->above->below = insertedNode;
                }

                break;
            }
        }
    }

    void insert_furkan(int val){
        // Start with top-left node
        Node* curr = head;
        Node* level = nullptr;


        while(curr != nullptr){
            while(curr->next!=nullptr && curr->data < val){
               curr = curr->next; 
            }

            if(curr->below != nullptr){
                level = curr;
                curr = curr->below;
            }

            // Reached top-bottom line.
            else {
                Node *newNode = new Node(val);
                newNode->next = curr->next;
                newNode->prev = curr;
                newNode->above = nullptr;
                newNode->below = nullptr;

                if(curr->next != nullptr) {
                    curr->next->prev = newNode;
                }

                // While adding existing node to above,
                // This could potentially lead bug!
                if(level!=nullptr && newNode!=nullptr){
                    newNode->above = newNode;
                    newNode->above->below = newNode;
                }

                break;            
            }




        }



    }

    // Remove a node from the Skip List
    bool remove(int val) {
        Node *curr = head;

        while (curr) {
            while (curr->next && curr->next->data < val) {
                curr = curr->next;
            }

            if (curr->next && curr->next->data == val) {
                Node *toRemove = curr->next;
                curr->next = toRemove->next;
                if (toRemove->next) {
                    toRemove->next->prev = curr;
                }

                while (curr->above) {
                    curr = curr->above;
                    Node *temp = curr;
                    while (temp->next && temp->next != toRemove) {
                        temp = temp->next;
                    }
                    temp->next = toRemove->next;
                    if (toRemove->next) {
                        toRemove->next->prev = temp;
                    }
                    toRemove = toRemove->above;
                }

                delete toRemove; // Free memory
                return true;
            }

            if (curr->below) {
                curr = curr->below;
            } else {
                break;
            }
        }

        return false; // Node with given value not found
    }

    // Print the Skip List structure
    void print() {
        Node *curr = head;
        while (curr->below) {
            curr = curr->below;
        }

        while (curr) {
            Node *temp = curr;
            while (temp) {
                cout << temp->data << " -> ";
                temp = temp->next;
            }
            cout << "NULL" << endl;
            curr = curr->below;
        }
    }

};

int main() {
    // SkipList skipList;
    // skipList.insert(3);
    // skipList.insert(7);
    // skipList.insert(5);
    // skipList.insert(9);
    // skipList.insert(4);
    // skipList.insert(6);
    // skipList.print();


    SkipList skipList;

    // Initialize random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(1, 25); // Change the range as needed

    // Generate and insert random integers into the skip list
    for (int i = 0; i < 20; ++i) {  // Insert 10 random integers, change the count as needed
        int randomNumber = distribution(gen);
        skipList.insert(randomNumber);
        cout << "Inserted: " << randomNumber << endl;
    }

    // Print the skip list to visualize the structure after random insertions
    skipList.print();

    return 0;
}
