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
    Node(int item) {
        key = item;
        left = NULL;
        right = NULL;
    }
};

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

Node* insert(Node* node, int key) {
    //tree is empty
    if (node == NULL) 
        return new Node(key);    
    
    //key is already in the tree
    if (node->key == key) 
        return node;
    
    //key being inserted is greater than the node's key -> insert it in the right subtree
    if (node->key < key) 
        node->right = insert(node->right, key);
    //key being inserted is smaller than the node's key -> insert it in the left subtree
    else 
        node->left = insert(node->left, key);
    return node;
}

int main(){
    Node* root = NULL;
    vector<int> numbers;
    int num = 10;
    int N = 100;

    // Generate random numbers and store them in the vector
    cout << "Generated random numbers: ";
    for (int i = 0; i < num; i++) {
        int randomNumber = rand() % N;
        cout << randomNumber << " ";
        numbers.push_back(randomNumber);  // Store the number in the vector
    }
    cout << endl;

    // Insert the random numbers into the BST
    for (int number : numbers) {
        root = insert(root, number);
    }

    // Print the BST using inorder traversal
    cout << "Inorder traversal of the BST: ";
    inorder(root);
    cout << endl;

    return 0;
}