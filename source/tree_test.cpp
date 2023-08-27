#include "../include/list.h"
#include "../include/rbtree.h"
#include "../include/timer.h"
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
    const int numOperations = 10000;

    cout << "# Testing insert" << endl;
    auto time = timerStart();
    for (int i = 0; i < numOperations; ++i) {
        list.insert(i);
    }
    cout << "Linked list ";
    timerEnd(time);

    time = timerStart();
    for (int i = 0; i < numOperations; ++i) {
        bst.insert(i);
    }
    cout << "BST ";
    timerEnd(time);

    time = timerStart();
    for (int i = 0; i < numOperations; ++i) {
        avl.insert(i);
    }
    cout << "AVL Tree ";
    timerEnd(time);

    time = timerStart();
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations;
        rbt.insert(num);
    }
    cout << "RB Tree ";
    timerEnd(time);

    cout << "# Testing search" << endl;
    time = timerStart();
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations;
        list.search(num);
    }
    cout << "Linked list ";
    timerEnd(time);

    time = timerStart();
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations;
        bst.search(num);
    }
    cout << "BST ";
    timerEnd(time);

    time = timerStart();
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations;
        avl.search(num);
    }
    cout << "AVL Tree ";
    timerEnd(time);

    time = timerStart();
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations;
        rbt.search(num);
    }
    cout << "RB Tree ";
    timerEnd(time);

    cout << "# Testing remove" << endl;
    time = timerStart();
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations;
        list.remove(num);
    }
    cout << "Linked list ";
    timerEnd(time);

    time = timerStart();
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations;
        bst.remove(num);
    }
    cout << "BST ";
    timerEnd(time);

    time = timerStart();
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations;
        avl.remove(num);
    }
    cout << "AVL Tree ";
    timerEnd(time);

    time = timerStart();
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations;
        rbt.remove(num);
    }
    cout << "RB Tree ";
    timerEnd(time);

    return 0;
}