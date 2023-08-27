#include "../include/list.h"
#include "../include/rbtree.h"
#include "../include/tree.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    srand(time(nullptr));

    AVLTree avl;
    BinarySearchTree bst;
    RedBlackTree rbt;
    SinglyLinkedList list;
    const int numOperations = 10000; // Number of operations (insert, search, remove)

    // Insertion phase
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations; // Generate a random number
        avl.insert(num);
        bst.insert(num);
        rbt.insert(num);
        list.insert(num);
    }
    // Removal phase
    for (int i = 0; i < numOperations / 2; ++i) {
        int num = rand() % numOperations; // Generate a random number
        avl.remove(num);
        bst.remove(num);
        rbt.remove(num);
        list.remove(num);
    }
    return 0;
}