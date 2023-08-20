#include "../include/tree.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    srand(time(nullptr));

    BinarySearchTree bst;
    const int numOperations = 100; // Number of operations (insert, search, remove)

    // Insertion phase
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % 100; // Generate a random number
        bst.insert(num);
    }

    // Search phase
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % 100; // Generate a random number
        bool found = bst.search(num);
    }

    // Removal phase
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % 100; // Generate a random number
        bst.remove(num);
    }

    bst.printTree();

    return 0;
}