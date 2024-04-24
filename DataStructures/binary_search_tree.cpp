#include <iostream>
using namespace std;

/* Binary Search Tree Complexities

 Time Complexity
Operation	Best Case Complexity	Average Case Complexity	Worst Case Complexity
Search	O(log n)	O(log n)	O(n)
Insertion	O(log n)	O(log n)	O(n)
Deletion	O(log n)	O(log n)	O(n)

Space Complexity
The space complexity for all the operations is O(n).

Binary Search Tree Applications
- In multilevel indexing in the database
- For dynamic sorting
- For managing virtual memory areas in Unix kernel
 */

// Node definition for the binary search tree
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};


class BinarySearchTree{
private:
    Node* root_node;
public:
    BinarySearchTree();
    Node* insert(Node* root, int key);
    Node* remove(Node* root, int key);
    Node* search(Node* root, int key);
    void printBSTInOrder(Node* root, int space);
    void inorder(Node* root);
    int getHeight();
    Node* getRoot();
    Node* createNewNode(int key);
};

// A utility function to do inorder traversal of BST
void BinarySearchTree::inorder(Node* root)
{
    if (root != nullptr) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

Node *BinarySearchTree::createNewNode(int key) {
    Node* new_node;
    new_node->data = key;
    new_node->right = nullptr;
    new_node->left = nullptr;
    return new_node;
}

/* insert a new node in BST with given key  */
Node* BinarySearchTree::insert(Node* root, int value) {
    if(root == nullptr){
        return new Node(value);
    }
    if(value < root->data){
        root->left = insert(root->left, value);
    }
    if(value >= root->data){
        root->right = insert(root->right, value);
    }
    return root;
}

Node* BinarySearchTree::remove(Node* root, int key)
{
    // CASE-1: the node to be deleted is the leaf node

    // CASE-2: the node to be deleted lies has a single child node
    /// Step=-1:Replace that node with its child node.
    /// Step=-2:Remove the child node from its original position.

    // CASE-3: the node to be deleted has two children
    /// Step-1: Get the inorder successor of that node.
    /// Step-2: Replace the node with the inorder successor.
    /// Step-3: Remove the inorder successor from its original position.

    // Base case
    if (root == nullptr)
        return root;

    // Recursive calls for ancestors of
    // node to be deleted
    if (root->data > key) {
        root->left = remove(root->left, key);
        return root;
    }
    else if (root->data < key) {
        root->right = remove(root->right, key);
        return root;
    }

    // We reach here when root is the node
    // to be deleted.

    // If one of the children is empty
    if (root->left == nullptr) {
        Node* temp = root->right;
        delete root;
        return temp;
    }
    else if (root->right == nullptr) {
        Node* temp = root->left;
        delete root;
        return temp;
    }

        // If both children exist
    else {

        Node* succParent = root;

        // Find successor
        Node* succ = root->right;
        while (succ->left != nullptr) {
            succParent = succ;
            succ = succ->left;
        }

        // Delete successor.  Since successor
        // is always left child of its parent
        // we can safely make successor's right
        // right child as left of its parent.
        // If there is no succ, then assign
        // succ->right to succParent->right
        if (succParent != root)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;

        // Copy Successor Data to root
        root->data = succ->data;

        // Delete Successor and return root
        delete succ;
        return root;
    }
}

Node *BinarySearchTree::search(Node* root, int key) {
    if (root == nullptr || root->data == key){
        return root;
    }
    if(key < root->data){
        return search(root->left, key);
    }
    return search(root->right, key);
}

int BinarySearchTree::getHeight() {
    return 0;
}

// Function to print spaces for formatting
void printSpaces(int count) {
    for (int i = 0; i < count; ++i) {
        std::cout << " ";
    }
}

void BinarySearchTree::printBSTInOrder(Node* root, int space) {
    const int spacesCount = 5;

    if (root == nullptr) {
        return;
    }

    space += spacesCount;

    // Process the right child first
    printBSTInOrder(root->right, space);

    // Print the current node after space calculation
    std::cout << std::endl;
    printSpaces(space - spacesCount);
    std::cout << root->data << "\n";

    // Process the left child
    printBSTInOrder(root->left, space);
}

BinarySearchTree::BinarySearchTree() {

}


void ex_search(){
    BinarySearchTree bst = BinarySearchTree();
    Node* root = nullptr;
    root = bst.insert(root, 40);
    bst.insert(root, 30);
    bst.insert(root, 60);
    bst.insert(root, 65);
    bst.insert(root, 70);
    Node* node_70 = bst.search(root, 70);
    std::cout << "Binary Search Tree (In-order traversal): \n";
    bst.printBSTInOrder(root, 0);
    std::cout << "\n";
}

void ex_remove(){
        /* Let us create following BST
          50
       /     \
      30      70
     /  \    /  \
   20   40  60   80 */
    BinarySearchTree bst = BinarySearchTree();
    Node* root = nullptr;
    root = bst.insert(root, 50);
    bst.insert(root, 30);
    bst.insert(root, 20);
    bst.insert(root, 40);
    bst.insert(root, 70);
    bst.insert(root, 60);

    printf("Original BST: ");
    bst.inorder(root);
   
    printf("\n\nDelete a Leaf Node: 20\n");
    root = bst.remove(root, 20);
    printf("Modified BST tree after deleting Leaf Node:\n");
    bst.inorder(root);
 
    printf("\n\nDelete Node with single child: 70\n");
    root = bst.remove(root, 70);
    printf("Modified BST tree after deleting single child Node:\n");
    bst.inorder(root);
 
    printf("\n\nDelete Node with both child: 50\n");
    root = bst.remove(root, 50);
    printf("Modified BST tree after deleting both child Node:\n");
    bst.inorder(root);
}


int main() {
    
    return 0;
}