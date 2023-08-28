#include "../include/list.h"
#include "../include/splayTree.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    srand(time(nullptr));
    SplayTree st;
    SinglyLinkedList list;
    const int numOperations = 100; // Number of operations (insert, search, remove)
    // Insertion phase
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations; // Generate a random number
        st.insert(num);
        list.insert(num);
    }
    // Search phase
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations; // Generate a random number
        cout << "Search " << num << endl;
        st.search(num);
        st.printTree();
    }
    // Remove phase
    /*for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations; // Generate a random number
        st.remove(num);
        list.remove(num);
    }*/
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