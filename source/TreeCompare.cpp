#include "../include/list.h"
#include "../include/rbtree.h"
#include "../include/splayTree.h"
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
    SplayTree st;
    SinglyLinkedList list;
    const int numOperations = 10000;

    cout << endl << "# Testing insert" << endl;
    auto time = timerStart();
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations;
        list.insert(num);
    }
    cout << "Linked list ";
    timerEnd(time);

    time = timerStart();
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations;
        bst.insert(num);
    }
    cout << "BST ";
    timerEnd(time);

    time = timerStart();
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations;
        avl.insert(num);
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

    time = timerStart();
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations;
        st.insert(num);
    }
    cout << "Splay Tree ";
    timerEnd(time);

    cout << endl << "# Testing search" << endl;
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

    time = timerStart();
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations;
        st.search(num);
    }
    cout << "Splay Tree ";
    timerEnd(time);

    cout << endl << "# Testing remove" << endl;
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

    time = timerStart();
    for (int i = 0; i < numOperations; ++i) {
        int num = rand() % numOperations;
        st.remove(num);
    }
    cout << "Splay Tree ";
    timerEnd(time);

    return 0;
}