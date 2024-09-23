#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <chrono>

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

    //insert key into the BST
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
            root = z;  //tree is empty, new node becomes root
        } else if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
    }

    //inorder walk
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

//delete a node from the BST
void transplant(BST& tree, Node* u, Node* v) {
    if (u->parent == nullptr) {
        tree.root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

void treeDelete(BST& tree, Node* z) {
    if (z->left == nullptr) {
        transplant(tree, z, z->right);
    } else if (z->right == nullptr) {
        transplant(tree, z, z->left);
    } else {
        Node* y = treeMinimum(z->right);
        if (y->parent != z) {
            transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    delete z;
}

// Find a node with a specific key in the tree
Node* search(Node* node, int key) {
    if (node == nullptr || node->key == key) {
        return node;
    }
    if (key < node->key) {
        return search(node->left, key);
    } else {
        return search(node->right, key);
    }
}

int main(){
    int n = 5;
    
    cout << "Testing with n = " << n << endl;
    vector<int> keys;
    for (int i = 0; i < n; i++) {
        keys.push_back(i + 1);
    }

    random_shuffle(keys.begin(), keys.end());

    BST tree;
    //insert shuffled keys into the BST
    for (int key : keys) {
        tree.treeInsert(key); 
    }

    cout << "In-order traversal of the tree: ";
    tree.inorder(tree.root);
    cout << endl;

    int deleteKey = 3;
    Node* nodeToDelete = search(tree.root, deleteKey);

    if (nodeToDelete != nullptr) {
        //delete the node
        treeDelete(tree, nodeToDelete);
        cout << "Node with key " << deleteKey << " deleted." << endl;
    } else {
        cout << "Node with key " << deleteKey << " not found!" << endl;
    }

    // Print the in-order traversal again to check after deletion
    cout << "In-order traversal of the tree after deletion: ";
    tree.inorder(tree.root);
    cout << endl;

    return 0;
}