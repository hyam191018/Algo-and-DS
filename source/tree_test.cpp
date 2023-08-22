#include "../include/list.h"
#include "../include/tree.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    srand(time(nullptr));

    AVLTree avl;
    BinarySearchTree bst;
    SinglyLinkedList list;
    const int numOperations = 100; // Number of operations (insert, search, remove)

    // Insertion phase
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations; // Generate a random number
        avl.insert(num);
        bst.insert(num);
        list.insert(num);
    }
    // Removal phase
    for (int i = 0; i < numOperations / 2; ++i) {
        int num = rand() % numOperations; // Generate a random number
        avl.remove(num);
        bst.remove(num);
        list.remove(num);
    }
    cout << " -------------------------- BST -------------------------- " << endl;
    bst.printTree();
    cout << " -------------------------- AVL -------------------------- " << endl;
    avl.printTree();
    cout << " ------------------------------------------- " << endl;
    cout << "BST  all: ";
    bst.inorderTraversal();
    cout << "AVL  all: ";
    avl.inorderTraversal();
    list.sort();
    list.printAll();

    return 0;
}