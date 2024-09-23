#include <iostream>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;
using namespace chrono;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node* parent;

    Node(int key) : key(key), left(nullptr), right(nullptr), parent(nullptr) {}
};


class BST {
public:
    Node* root;

    BST() : root(nullptr) {}

    // Tree-Insert: Insert key into the BST
    void treeInsert(int key) {
        Node* z = new Node(key);
        Node* y = nullptr;
        Node* x = root;

        while (x != nullptr) {
            y = x;
            if (z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;

        if (y == nullptr) {
            root = z;  // Tree was empty, new node becomes root
        } else if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
    }

    // In-order traversal (to verify the tree structure)
    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->key << " ";
            inorder(node->right);
        }
    }
};

//find the minimum node
Node* treeMinimum(Node* x) {
    while (x->left != nullptr) {
        x = x->left;
    }
    return x;
}

int main(){
    Node* root = NULL;
    vector<int> keys;
    int num = 10;
    int N = 100;

    // Generate random numbers and store them in the vector
    cout << "Generated random numbers: ";
    for (int i = 0; i < num; i++) {
        int randomNumber = rand() % N;
        cout << randomNumber << " ";
        keys.push_back(randomNumber);  // Store the number in the vector
    }
    cout << endl;

    BST tree;
    for (int key : keys) {
        tree.treeInsert(key); // Insert shuffled keys into the BST
    }

    // Print the in-order traversal to verify the tree structure
    cout << "In-order traversal of the tree: ";
    tree.inorder(tree.root);
    cout << endl;

    Node* minNode = treeMinimum(tree.root);
    if (minNode != nullptr) {
        cout << "The minimum key in the tree is: " << minNode->key << endl;
    } else {
        cout << "The tree is empty." << endl;
    }

    return 0;
}