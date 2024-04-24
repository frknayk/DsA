//
// Created by Furka on 12/27/2023.
//
#include <iostream>
using namespace std;

struct Node {
    Node* left;
    Node* right;
    int key;
    explicit Node(int key_): key(key_), left(nullptr), right(nullptr) {}
};

class BST {

    private:
        Node* root;

        Node* insertRecursive(Node* root, int key){
            if (root == nullptr){
                return new Node(key);
            }
            if (key < root->key){
                root->left = insertRecursive(root->left, key);
            }
            if (root->key < key){
                root->right = insertRecursive(root->right, key);
            }
            return root;
        }

        Node* searchRecursive(Node* root, int key){
            if (root == nullptr || root->key == key){
                return root;
            }
            if (key < root->key){
                return searchRecursive(root->left, key);
            }
            else if (root->key < key){
                return searchRecursive(root->right, key);
            }
        }

        Node* removeRecursive(Node* root, int key) {
            if (root == nullptr) {
                return root;
            }

            if (key < root->key) {
                root->left = removeRecursive(root->left, key);
            }

            else if (root->key < key) {
                root->right = removeRecursive(root->right, key);
            }

            else {
                if (root->left == nullptr) {
                    Node *temp = root->right;
                    delete root;
                    return temp;
                }
                if (root->right == nullptr) {
                    Node *temp = root->left;
                    delete root;
                    return temp;
                }
                // Find the node with the smallest value in the right subtree
                Node* successor = findMin(root->right);
                root->key = successor->key;
                removeRecursive(root->right, successor->key);
        }
            return root;
        }

        Node* findMin(Node* root){
            while (root->left){
                root = root->left;
            }
            return root;
        }

        void preOrderRecursive(Node* root){
            if(root){
                cout<<root->key<<" ";
                preOrderRecursive(root->left);
                preOrderRecursive(root->right);
            }
        }

        void postOrderRecursive(Node* root){
            if(root){
                postOrderRecursive(root->left);
                postOrderRecursive(root->right);
                cout<<root->key<<" ";
            }
        }

        void inOrderRecursive(Node* root){
            if(root){
                inOrderRecursive(root->left);
                cout<<root->key<<" ";
                inOrderRecursive(root->right);
            }
        }

        int calculateHeight(Node* node){
            if(node == nullptr){
                return 0;
            }
            int left_height = calculateHeight(node->left);
            int right_height = calculateHeight(node->right);
            return max(left_height, right_height) + 1;
        }

    public:
        BST(){
            root = nullptr;
        }

        void insert(int key){
            root = insertRecursive(root, key);
        }

        void search(int key){
            cout<<"\n\nSearching node with key:"<<key<<"\n";

            Node* searched_node = searchRecursive(root, key);
            if(searched_node == nullptr){
                std::cout<<"Searched node could not found \n";
                return;
            }
            cout<<"Found key: "<<searched_node->key << "\n";
        }

        void remove(int key){
            Node* removed_node = removeRecursive(root, key);
            if (removed_node == nullptr){
                std::cout<<"\nThe key does not exist in the tree. \n";
            }
        }

        void preOrderTraversal(){
            std::cout<<"\nPre-order traversal: \n";
            preOrderRecursive(root);
        }

        void postOrderTraversal(){
            std::cout<<"\nPost-order traversal: \n";
            postOrderRecursive(root);
        }

        void inOrderTraversal(){
            std::cout<<"\nIn-order traversal: \n";
            inOrderRecursive(root);
        }

        int getHeight(){
            int height = calculateHeight(root);
            cout<<"Tree height: <<<"<<height<<">>>\n";
        }
};


int main(){
    BST bst;
    bst.insert(6);
    bst.insert(27);
    bst.insert(4);
    bst.insert(3);
    bst.insert(5);
    bst.insert(15);
    bst.insert(7);
    bst.insert(10);
    bst.insert(22);
    bst.insert(8);
    bst.insert(15);
    bst.insert(23);
    bst.insert(21);

    bst.inOrderTraversal();
//    bst.preOrderTraversal();
//    bst.postOrderTraversal();

//    bst.search(25);

    bst.remove(21);
    cout<<"\nAfter deleting 21:";
    bst.inOrderTraversal();
    bst.search(21);

    int height_tree = bst.getHeight();

    return 0;
}

