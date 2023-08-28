#include "../include/splayTree.h"
#include "../include/list.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    srand(time(nullptr));
    SplayTree st;
    SinglyLinkedList list;
    const int numOperations = 100; // Number of operations (insert, search, remove)
    // Insertion phase
    cout << "Inserting phase" << endl;
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations; // Generate a random number
        st.insert(num);
        list.insert(num);
    }
    // Search phase
    cout << "Searching phase" << endl;
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations; // Generate a random number
        if (st.search(num) != list.search(num)) {
            cout << "Search fail!" << endl;
        }
    }
    // Remove phase
    cout << "Removing phase" << endl;
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations; // Generate a random number
        st.remove(num);
        list.remove(num);
    }
    cout << " ------------------------- Splay tree ------------------------- " << endl;
    st.printTree();
    cout << " -------------------- cmp with linked list -------------------- " << endl;
    cout << "Tree all: ";
    st.inorderTraversal();
    cout << endl;
    list.sort();
    list.printAll();

    return 0;
}