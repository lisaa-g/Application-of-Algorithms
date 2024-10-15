#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>

using namespace std;
using namespace chrono;

class Node {
public:
    int value;
    Node* next;
    class DisjointSet* set_ptr;  // Pointer to the set that contains this node

    Node(int v) : value(v), next(nullptr), set_ptr(nullptr) {}
};

class DisjointSet {
public:
    Node* head;
    Node* tail;
    int size;

    DisjointSet(Node* n) : head(n), tail(n), size(1) {
        n->set_ptr = this;  // Each node knows which set it belongs to
    }
};

// Creates a new set with a single element
DisjointSet* makeSet(int x) {
    Node* newNode = new Node(x);
    DisjointSet* newSet = new DisjointSet(newNode);
    return newSet;
}

// Finds the set containing x and returns the corresponding DisjointSet
DisjointSet* findSet(Node* x) {
    return x->set_ptr;
}

// Add 2 sets together with weighted-union heuristic
void Union(Node* x, Node* y) {
    DisjointSet* set1 = findSet(x);
    DisjointSet* set2 = findSet(y);
    
    if (set1 == set2) return;  // If they are already in the same set

    // Always append the smaller set to the larger one
    if (set1->size < set2->size) {
        swap(set1, set2);
    }

    // Append set2's list to set1's list
    set1->tail->next = set2->head;
    set1->tail = set2->tail; 
    set1->size += set2->size;  // Update the size of set1

    // Update the set_ptr for all nodes in set2
    Node* temp = set2->head;
    while (temp != nullptr) {
        temp->set_ptr = set1; // All nodes in set2 now point to set1
        temp = temp->next;
    }

    // Clean up the set2 to avoid memory leaks
    delete set2; // Optionally free the set2 memory
}

// Print values in a set
void printSet(DisjointSet* set) {
    Node* current = set->head;
    while (current != nullptr) {
        cout << current->value;
        if (current->next != nullptr) {
            cout << " <- ";
        }
        current = current->next;
    }
    cout << endl;
}

void recordTime(int size, ofstream& csv_file) {
    vector<Node*> nodes(size);
    double totalTime = 0.0; // Variable to accumulate the total time
    const int runs = 10; // Number of runs to average

    for (int run = 0; run < runs; ++run) {
        // Start time
        auto start = high_resolution_clock::now();

        // Create n sets
        for (int i = 0; i < size; i++) {
            nodes[i] = new Node(i);
        }

        vector<DisjointSet*> sets;
        for (Node* node : nodes) {
            sets.push_back(makeSet(node->value));
        }
        
        // Union all sets with the first set
        for (int i = 1; i < size; i++) {
            Union(nodes[0], nodes[i]);
        }

        // Stop time
        auto end = high_resolution_clock::now();
        duration<double, micro> timeTaken = end - start;

        totalTime += timeTaken.count(); // Accumulate the time
        // Clean up memory for this run
        for (auto set : sets) {
            delete set; // Clean up each disjoint set
        }
        for (auto node : nodes) {
            delete node; // Clean up each node
        }
    }

    // Calculate average time
    double averageTime = totalTime / runs;
    csv_file << size << "," << averageTime << "\n"; // Write average time to CSV
}

int main() {
    // Create sets
    vector<DisjointSet*> sets;
    for (int i = 1; i <= 6; ++i) {
        sets.push_back(makeSet(i));
    } 

    cout << "Union of 1 and 2: " << endl;
    Union(sets[0]->head, sets[1]->head);  // Union of {1} and {2}
    printSet(sets[0]);

    cout << "Union of 3 and 4: " << endl;
    Union(sets[2]->head, sets[3]->head);  // Union of {3} and {4}
    printSet(sets[2]);

    cout << "Union of 1 and 3: " << endl;
    Union(sets[0]->head, sets[2]->head);  // Union of {1, 2} and {3, 4}
    printSet(sets[0]);

    cout << "Union of 4 and 5: " << endl;
    Union(sets[4]->head, sets[5]->head);  // Union of {5} and {6}
    printSet(sets[4]);   

    int sizes[] = {100, 1000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};

    ofstream csv_file("partA1.csv");
    csv_file << "Number of Sets,Time (microseconds)\n";

    for (int size : sizes) {
        recordTime(size, csv_file);
    }

    csv_file.close();
    return 0;
}