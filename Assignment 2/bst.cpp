#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>  // For file operations

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

    //in-order walk
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

int main() {
    srand(time(0));
    int trials = 5;

    // Open CSV file for writing results
    ofstream file("bst_results.csv");
    file << "n,average_build_time,average_destroy_time,average_height\n";

    // Loop through every value from 1 to 10000
    for (int n = 10; n <= 100000; n=n+10) {
        double totalBuildTime = 0;
        double totalDestroyTime = 0;
        double totalHeight = 0;

        for (int t = 0; t < trials; t++) {
            vector<int> keys;
            for (int i = 0; i < n; i++) {
                keys.push_back(i + 1);
            }

            random_shuffle(keys.begin(), keys.end());

            //measure time to build the tree
            auto start = high_resolution_clock::now();
            BST tree;
            for (int key : keys) {
                tree.treeInsert(key);
            }
            auto end = high_resolution_clock::now();
            duration<double, micro> buildTime = end - start;
            totalBuildTime += buildTime.count();

            //measure tree height
            int height = treeHeight(tree.root);
            totalHeight += height;

            //measure time to destroy the tree
            start = high_resolution_clock::now();
            while (tree.root != nullptr) {
                treeDelete(tree, tree.root);  // Delete the root node repeatedly
            }
            end = high_resolution_clock::now();
            duration<double, micro> destroyTime = end - start;
            totalDestroyTime += destroyTime.count();
        }

        //write results to the CSV file
        file << n << "," << (totalBuildTime / trials) << "," << (totalDestroyTime / trials) << "," << (totalHeight / trials) << "\n";
    }

    file.close();
    
    cout << "Experiment completed and results saved to bst_results.csv" << endl;

    return 0;
}