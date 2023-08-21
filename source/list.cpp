#include "../include/list.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main(void) {

    srand(time(nullptr));

    SinglyLinkedList Slist;
    DoublyLinkedList Dlist;
    const int round = 10;
    cout << "<< Testing Singly and Doubly linked list >>" << endl << endl;

    cout << "# Inserting" << endl;
    for (int i = 0; i < round; i++) {
        int num = rand() % round;
        Slist.insert(num);
        Dlist.insert(num);
    }

    Slist.printAll();
    Dlist.printAll();
    cout << endl;

    cout << "# Searching " << endl;
    cout << "No find ";
    for (int i = 0; i < round; i++) {
        if (!Slist.search(i) && !Dlist.search(i)) {
            cout << i << " ";
        }
    }
    cout << endl << endl;

    cout << "# Removing " << endl;
    cout << "Remove ";
    for (int i = 0; i < round; i++) {
        int num = rand() % round;
        if (Slist.remove(num) && Dlist.remove(num)) {
            cout << num << " ";
        }
    }
    cout << endl << endl;

    Slist.printAll();
    Dlist.printAll();
    cout << endl;

    /*----------------------------stack and queue --------------------------*/

    Stack stack;
    Queue queue;
    cout << "<< Testing Stack and queue >>" << endl << endl;

    cout << "# Pushing" << endl;
    for (int i = 0; i < round; i++) {
        int num = rand() % round;
        stack.push(num);
        queue.push(num);
    }

    stack.printAll();
    queue.printAll();
    cout << endl;

    cout << "# Poping " << endl;
    for (int i = 0; i < round / 2; i++) {
        stack.pop();
        queue.pop();
    }

    stack.printAll();
    queue.printAll();
    cout << endl;
}