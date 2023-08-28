#include "../include/list.h"
#include "../include/tree.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    srand(time(nullptr));

    BinarySearchTree bst;
    SinglyLinkedList list;
    const int numOperations = 100; // Number of operations (insert, search, remove)

    // Insertion phase
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations; // Generate a random number
        bst.insert(num);
        list.insert(num);
    }
    // Search phase
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations; // Generate a random number
        if (bst.search(num) != list.search(num)) {
            cout << "Search fail!" << endl;
        }
    }
    // Remove phase
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations; // Generate a random number
        bst.remove(num);
        list.remove(num);
    }
    cout << " ------------------------- BST -------------------------- " << endl;
    bst.printTree();
    cout << " -------------------------------------------------------- " << endl;
    cout << "BST  all: ";
    bst.inorderTraversal();
    list.sort();
    list.printAll();

    return 0;
}