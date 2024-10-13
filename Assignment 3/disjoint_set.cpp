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

//creates a new set with a single element
DisjointSet* makeSet(int x) {
    Node* newNode = new Node(x);
    DisjointSet* newSet = new DisjointSet(newNode);
    return newSet;
}

//finds set containing x
Node* findSet(Node* x) {
    return x->set_ptr->head;
}

//add 2 sets together with weighted-union heuristic
void Union(DisjointSet* set1, DisjointSet* set2) {
    //if set1 is bigger than set 2, add set2 to set1
    if (set1->size >= set2->size) {
        set1->tail->next = set2->head;
        set1->tail = set2->tail; 
        set1->size = set1->size + set2->size;  //update the size of set1

        //update the set_ptr for all nodes in set2
        Node* temp = set2->head;
        while (temp != nullptr) {
            temp->set_ptr = set1;
            temp = temp->next;
        }
    } else {
        Union(set2, set1);
    }
}

//print values in a set
void printSet(DisjointSet* set) {
    vector<int> values;
    Node* current = set->head;

    while (current != nullptr) {
        values.push_back(current->value);
        current = current->next;
    }

    for (size_t i = 0; i < values.size(); ++i) {
        cout << values[i];
        if (i < values.size() - 1) {
            cout << "<-";
        }
    }
    cout << endl;
}

//record the time
void recordTime(int n, ofstream& csv_file) {
    vector<DisjointSet*> sets;

    //start time
    auto start = high_resolution_clock::now();

    //create n sets
    for (int i = 0; i < n; i++) {
        sets.push_back(makeSet(i));
    }
    
    //union all sets with the first set
    for (int i = 1; i < n; i++) {
        Union(sets[0], sets[i]);
    }

    auto end = high_resolution_clock::now();
    duration<double, micro> elapsed = end - start;

    csv_file << n << "," << elapsed.count() << "\n";
}

int main() {
    //create sets
    vector<DisjointSet*> sets;
    for (int i = 1; i <= 6; ++i) {
        sets.push_back(makeSet(i));
    } 

    cout << "Union of 1 and 2: " << endl;
    Union(sets[0], sets[1]);  //union of {1} and {2}
    printSet(sets[0]);

    cout << "Union of 3 and 4: " << endl;
    Union(sets[2], sets[3]);  //union of {3} and {4}
    printSet(sets[2]);

    cout << "Union of 1 and 3: " << endl;
    Union(sets[0], sets[2]);  //union of {1, 2} and {3, 4}
    printSet(sets[0]);

    cout << "Union of 4 and 5: " << endl;
    Union(sets[4], sets[5]);  //union of {5} and {6}
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
