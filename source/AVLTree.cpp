#include "../include/list.h"
#include "../include/tree.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    srand(time(nullptr));

    AVLTree avl;
    SinglyLinkedList list;
    const int numOperations = 100; // Number of operations (insert, search, remove)

    // Insertion phase
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations; // Generate a random number
        avl.insert(num);
        list.insert(num);
    }
    // Search phase
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations; // Generate a random number
        if (avl.search(num) != list.search(num)) {
            cout << "Search fail!" << endl;
        }
    }
    // Remove phase
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations; // Generate a random number
        avl.remove(num);
        list.remove(num);
    }
    cout << " ------------------------- AVLT -------------------------- " << endl;
    avl.printTree();
    cout << " --------------------------------------------------------- " << endl;
    cout << "AVLT all: ";
    avl.inorderTraversal();
    list.sort();
    list.printAll();

    return 0;
}