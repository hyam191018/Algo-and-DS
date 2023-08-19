#include "../include/linked_list.h"

int main(void) {
    SinglyLinkedList Slist;
    node* n;
    n = list.create_node(5);
    list.insert(n);
    n = list.create_node(6);
    list.insert(n);
    n = list.create_node(2);
    list.insert(n);
    n = list.create_node(4);
    list.insert(n);
    n = list.create_node(3);
    list.insert(n);

    list.printAll();
    cout << "List size is " << list.length() << endl;
}