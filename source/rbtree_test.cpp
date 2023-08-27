#include "../include/list.h"
#include "../include/rbtree.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    srand(time(nullptr));

    RedBlackTree rbt;
    SinglyLinkedList list;
    const int numOperations = 100; // Number of operations (insert, search, remove)

    // Insertion phase
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations; // Generate a random number
        rbt.insert(num);
        list.insert(num);
    }
    // Remove phase
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations; // Generate a random number
        rbt.remove(num);
        list.remove(num);
    }
    cout << " -------------------------- RBT -------------------------- " << endl;
    rbt.printTree();
    cout << " ------------------------- COLOR ------------------------- " << endl;
    rbt.printColor();
    cout << " --------------------------------------------------------- " << endl;
    cout << "RBT  all: ";
    rbt.inorderTraversal();
    cout << endl;
    list.sort();
    list.printAll();

    return 0;
}