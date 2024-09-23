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

// Function to compute the height of the tree
int treeHeight(Node* node) {
    if (node == nullptr) return 0;
    return 1 + max(treeHeight(node->left), treeHeight(node->right));
}

int main(){
    srand(time(0));
    int n = 5;
    vector<int> keys;
    for (int i = 0; i < n; i++) {
        keys.push_back(i + 1);
    }

    random_shuffle(keys.begin(), keys.end());
    for (int key : keys) {
        cout << key << " ";
    }
    cout << endl;

    auto start = chrono::high_resolution_clock::now(); // Start timer
    BST tree;
    for (int key : keys) {
        tree.treeInsert(key);
    }
    auto end = chrono::high_resolution_clock::now(); // End timer
    chrono::duration<double, micro> elapsed = end - start;
    cout << "Time taken to build tree for n = " << n << ": " << elapsed.count() << " microseconds" << endl;

    int height = treeHeight(tree.root);
    cout << "Tree height for n = " << n << " is " << height << endl;

    cout << "In-order traversal of the tree: ";
    tree.inorder(tree.root);
    cout << endl;

    start = chrono::high_resolution_clock::now(); // Start timer
    while (tree.root != nullptr) {
        treeDelete(tree, tree.root); // Delete the root node repeatedly
    }
    end = chrono::high_resolution_clock::now(); // End timer
    elapsed = end - start;
    cout << "Time taken to destroy the tree: " << elapsed.count() << " microseconds" << endl;

    cout << "In-order traversal of the tree: ";
    tree.inorder(tree.root);
    cout << endl;

    return 0;
}