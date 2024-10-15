#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//node structure representing each element in the disjoint-set
struct Node {
    int data;
    Node* parent;
    int rank;
};

//create a set
Node* makeSet(int x) {
    Node* node = new Node;
    node->data = x;
    node->parent = node; //node is its own parent
    node->rank = 0; //rank is 0 when the set is created
    return node;
}

//FIND-SET with path compression
Node* findSet(Node* x) {
    if (x != x->parent) {
        x->parent = findSet(x->parent); //point directly to the root
    }
    return x->parent;
}

//link sets x and y by rank
void link(Node* x, Node* y) {
    if (x->rank > y->rank) {
        y->parent = x; //add ys tree to x
    } else {
        x->parent = y; //add xs tree to y
        if (x->rank == y->rank) {
            y->rank++; //increment y rank if the ranks are equal
        }
    }
}

//union two sets by linking their representatives
void unionSets(Node* x, Node* y) {
    link(findSet(x), findSet(y));
}

//print the represenattive of the set that x belongs to
void printSetRepresentative(Node* x) {
    Node* rep = findSet(x);
    cout << "Representative of " << x->data << " is " << rep->data << endl;
}

int main() {
    //creates sets
    Node* node1 = makeSet(1);
    Node* node2 = makeSet(2);
    Node* node3 = makeSet(3);
    Node* node4 = makeSet(4);

    cout << "Initial representatives:" << endl;
    printSetRepresentative(node1);
    printSetRepresentative(node2);
    printSetRepresentative(node3);
    printSetRepresentative(node4);
    
    cout << "\nUnion of set 1 and set 2:" << endl;
    unionSets(node1, node2);
    printSetRepresentative(node1);
    printSetRepresentative(node2);
    
    cout << "\nUnion of set 3 and set 4:" << endl;
    unionSets(node3, node4);
    printSetRepresentative(node3); 
    printSetRepresentative(node4);
    
    cout << "\nUnion of set 1+2 and set 3+4:" << endl;
    unionSets(node1, node3);
    printSetRepresentative(node1);
    printSetRepresentative(node2);
    printSetRepresentative(node3);
    printSetRepresentative(node4);

    return 0;
}