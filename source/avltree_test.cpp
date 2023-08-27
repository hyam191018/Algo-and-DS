#include "../include/list.h"
#include "../include/tree.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    srand(time(nullptr));

    AVLTree avl;
    SinglyLinkedList list;
    const int numOperations = 1000; // Number of operations (insert, search, remove)

    // Insertion phase
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations; // Generate a random number
        avl.insert(num);
        list.insert(num);
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
    cout << "AVL  all: ";
    avl.inorderTraversal();
    cout << endl;
    list.sort();
    list.printAll();

    return 0;
}