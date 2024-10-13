// #include <iostream>
// #include <chrono>
// #include <vector>
// #include <fstream>  // For file handling

// using namespace std;

// class Node {
// public:
//     int value;
//     Node* next;
//     class DisjointSet* set_ptr;  // Pointer to the set that contains this node

//     Node(int v) : value(v), next(nullptr), set_ptr(nullptr) {}
// };

// class DisjointSet {
// public:
//     Node* head;
//     Node* tail;
//     int size;

//     DisjointSet(Node* n) : head(n), tail(n), size(1) {
//         n->set_ptr = this;  // Each node knows which set it belongs to
//     }
// };

// // Make-Set operation: creates a new set with a single element
// DisjointSet* MakeSet(int x) {
//     Node* newNode = new Node(x);
//     DisjointSet* newSet = new DisjointSet(newNode);
//     return newSet;
// }

// // Find-Set operation: returns the representative of the set containing x
// Node* FindSet(Node* x) {
//     return x->set_ptr->head;
// }

// // Union operation with weighted-union heuristic
// void Union(DisjointSet* set1, DisjointSet* set2) {
//     if (set1->size >= set2->size) {
//         set1->tail->next = set2->head;  // Append set2's list to set1's list
//         set1->tail = set2->tail;  // Update the tail of set1
//         set1->size += set2->size;  // Update the size of set1

//         // Update the set_ptr for all nodes in set2
//         Node* temp = set2->head;
//         while (temp != nullptr) {
//             temp->set_ptr = set1;
//             temp = temp->next;
//         }
//     } else {
//         Union(set2, set1);  // Always append the smaller list to the larger one
//     }
// }

// // Function to run the experiment and record the time
// void RunExperiment_LinkedList(int n, std::ofstream& csv_file) {
//     vector<DisjointSet*> sets;

//     // Step 1: Create n sets
//     for (int i = 0; i < n; i++) {
//         sets.push_back(MakeSet(i));
//     }

//     // Step 2: Perform n-1 Union operations
//     auto start = chrono::high_resolution_clock::now();
    
//     for (int i = 1; i < n; i++) {
//         Union(sets[0], sets[i]);  // Union all sets with the first set
//     }

//     auto end = chrono::high_resolution_clock::now();
//     chrono::duration<double> elapsed = end - start;

//     // Save results to CSV
//     csv_file << n << "," << elapsed.count() << "\n";

//     cout << "Time taken for " << n << " Make-Set and " << (n - 1) 
//         << " Union operations (Linked List, Weighted Union): " 
//         << elapsed.count() << " seconds.\n";
// }

// // int main() {
// //     int sizes[] = {1000, 2500, 5000, 7500, 10000, 12500, 15000, 17500, 20000};
    
// //     // Open CSV file for writing
// //     ofstream csv_file("linked_list_experiment.csv");
// //     csv_file << "Number of Sets,Time (seconds)\n";

// //     for (int size : sizes) {
// //         RunExperiment_LinkedList(size, csv_file);
// //     }

// //     csv_file.close();  // Close the file after writing
// //     return 0;
// // }

// // Function to print all values in a specific disjoint set in the format "1<-2<-3<-4"
// void PrintSet(DisjointSet* set) {
//     vector<int> values; // To hold values for printing
//     Node* current = set->head;

//     // Traverse through the linked list and collect values
//     while (current != nullptr) {
//         values.push_back(current->value);
//         current = current->next;
//     }

//     // Print values in the specified format
//     for (size_t i = 0; i < values.size(); ++i) {
//         cout << values[i];
//         if (i < values.size() - 1) {
//             cout << "<-"; // Add arrow between values
//         }
//     }
//     cout << endl; // New line after printing
// }

// int main() {
//     // Create disjoint sets for values 1 to 6
//     vector<DisjointSet*> sets;
//     for (int i = 1; i <= 6; ++i) {
//         sets.push_back(MakeSet(i));
//         PrintSet(sets[i]);
//     } 

//     // Perform some unions
//     cout<< "Union of 1 and 2: ";
//     Union(sets[0], sets[1]);  // Union of {1} and {2}
//     PrintSet(sets[0]);
//     cout<<endl;

//     Union(sets[2], sets[3]);  // Union of {3} and {4}
//     PrintSet(sets[2]);  
//     cout << endl;

//     Union(sets[0], sets[2]);  // Union of {1, 2} and {3, 4}
//     PrintSet(sets[0]); 
//     cout << endl;

//     Union(sets[4], sets[5]);  // Union of {5} and {6}
//     PrintSet(sets[4]);   


//     return 0;
// }

#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>  // For file handling

using namespace std;

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
DisjointSet* MakeSet(int x) {
    Node* newNode = new Node(x);
    DisjointSet* newSet = new DisjointSet(newNode);
    return newSet;
}

//finds set containing x
Node* FindSet(Node* x) {
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
void PrintSet(DisjointSet* set) {
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

int main() {
    //create sets
    vector<DisjointSet*> sets;
    for (int i = 1; i <= 6; ++i) {
        sets.push_back(MakeSet(i));
    } 

    cout << "Union of 1 and 2: " << endl;
    Union(sets[0], sets[1]);  //union of {1} and {2}
    PrintSet(sets[0]);

    cout << "Union of 3 and 4: " << endl;
    Union(sets[2], sets[3]);  //union of {3} and {4}
    PrintSet(sets[2]);

    cout << "Union of 1 and 3: " << endl;
    Union(sets[0], sets[2]);  //union of {1, 2} and {3, 4}
    PrintSet(sets[0]);

    cout << "Union of 4 and 5: " << endl;
    Union(sets[4], sets[5]);  //union of {5} and {6}
    PrintSet(sets[4]);   

    return 0;
}
