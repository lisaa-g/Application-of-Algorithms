#include <iostream>

using namespace std;

struct Node {
    int key;
    int size;
    Node* left;
    Node* right;
    Node* parent;
    
    Node(int key) : key(key), size(1), left(nullptr), right(nullptr), parent(nullptr) {}
};

Node* treeInsert(Node*& root, int key) {
    Node* newNode = new Node(key);
    Node* y = nullptr;
    Node* x = root;
    
    while (x != nullptr) {
        y = x;
        //increase size of node
        x->size++; 
        if (newNode->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    newNode->parent = y;
    if (y == nullptr) {
        root = newNode;
    } else if (newNode->key < y->key) {
        y->left = newNode;
    } else {
        y->right = newNode;
    }

    return newNode;
}

void inOrderTraversal(Node* root) {
    if (root != nullptr) {
        inOrderTraversal(root->left);
        cout << "Key: " << root->key << ", Size: " << root->size << endl;
        inOrderTraversal(root->right);
    }
}

Node* treeMinimum(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

void transplant(Node*& root, Node* u, Node* v) {
    if (u->parent == nullptr) {
        root = v; 
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

void treeDelete(Node*& root, Node* z) {
    Node* deletedNode = nullptr;
    if (z->left == nullptr) {
        transplant(root, z, z->right);
        deletedNode = z->parent;
    } else if (z->right == nullptr) {
        transplant(root, z, z->left);
        deletedNode = z->parent; 
    } else {
        Node* y = treeMinimum(z->right); 
        deletedNode = (y->parent != z) ? y->parent : y; 

        if (y->parent != z) {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
    }

    delete z;

    //update the sizes of nodes after deletion
    while (deletedNode != nullptr) {
        int newSize = 1;
        if (deletedNode->left != nullptr) {
            newSize += deletedNode->left->size;
        }
        if (deletedNode->right != nullptr) {
            newSize += deletedNode->right->size;
        }
        if (newSize == deletedNode->size) {
            break; 
        }
        deletedNode->size = newSize;
        deletedNode = deletedNode->parent;
    }
}

Node* OSSelect(Node* node, int i) {
    int r = (node->left ? node->left->size : 0) + 1;
    if (i == r) {
        return node;
    } else if (i < r) {
        return OSSelect(node->left, i);
    } else {
        return OSSelect(node->right, i - r);
    }
}

int OSRank(Node* root, Node* x) {
    int r = (x->left != nullptr) ? x->left->size + 1 : 1;
    Node* y = x;
    while (y != root) {
        if (y == y->parent->right) {
            r += (y->parent->left != nullptr) ? y->parent->left->size + 1 : 1; 
        }
        y = y->parent;
    }
    return r;
}

Node* OSSearch(Node* root, int key) {
    while (root != nullptr && key != root->key) {
        if (key < root->key) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return root;
}

int main() {
    Node* root = nullptr;
    treeInsert(root, 15);
    treeInsert(root, 10);
    treeInsert(root, 20);
    treeInsert(root, 8);
    treeInsert(root, 12);
    treeInsert(root, 17);
    treeInsert(root, 25);
    treeInsert(root, 16);

    cout << "In-order traversal after inserts:\n";
    inOrderTraversal(root);

    //select the 3rd smallest node
    Node* thirdSmallest = OSSelect(root, 3);
    if (thirdSmallest != nullptr) {
        cout << "\nThe 3rd smallest element is: " << thirdSmallest->key << endl;
    }

    //find the rank of the node with key 17
    Node* nodeWithKey17 = OSSearch(root, 17);
    if (nodeWithKey17 != nullptr) {
        int rank = OSRank(root, nodeWithKey17);
        cout << "\nThe rank of node with key 17 is: " << rank << endl;
    }

    //delete the root node with key 15
    Node* rootNode = OSSearch(root, 15);
    if (rootNode != nullptr) {
        treeDelete(root, rootNode);
    }

    cout << "\nIn-order traversal after deleting the root:\n";
    inOrderTraversal(root);

    return 0;
}
