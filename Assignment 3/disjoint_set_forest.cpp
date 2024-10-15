#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>

using namespace std;
using namespace chrono;

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

// Function to record time for union and find operations
void recordTime(int size, ofstream& csv_file) {
    vector<Node*> nodes;
    double totalTime = 0.0; // Variable to accumulate the total time
    const int runs = 10; // Number of runs to average
    
    for (int run = 0; run < runs; ++run) {
        auto start = high_resolution_clock::now();
        //create n sets
        for (int i = 1; i <= size; ++i) {
            nodes.push_back(makeSet(i));
        }

        //union all sets with the first set
        for (int i = 0; i < size - 1; i += 2) {
            unionSets(nodes[i], nodes[i + 1]);
        }
        auto end = high_resolution_clock::now();
        duration<double, micro> timeTaken = end - start;

        totalTime += timeTaken.count();
    }

    // Calculate average time
    double averageTime = totalTime / runs;
    csv_file << size << "," << averageTime << "\n";
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

    int sizes[] = {100, 1000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};

    ofstream csv_file("partA2.csv");
    csv_file << "Number of Sets,Time (microseconds)\n";

    for (int size : sizes) {
        recordTime(size, csv_file);
    }

    csv_file.close();

    return 0;
}