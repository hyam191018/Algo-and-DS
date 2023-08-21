#include "../include/tree.h"
#include "../include/list.h"
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
    // Removal phase
    for (int i = 0; i < numOperations / 2; ++i) {
        int num = rand() % numOperations; // Generate a random number
        cout << "!Remove " << num << endl;
        avl.remove(num);
        list.remove(num);
    }
    avl.printTree();
    cout << " --- compare with linked list --- " << endl;
    cout << "Tree all: ";
    avl.inorder_traversal();
    list.sort();
    list.printAll();

    return 0;
}