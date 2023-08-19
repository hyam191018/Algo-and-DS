#include "../include/linked_list.h"

int main(void) {
    SinglyLinkedList Slist;
    node* n;
    n = Slist.create_node(5);
    Slist.insert(n);
    n = Slist.create_node(6);
    Slist.insert(n);
    n = Slist.create_node(2);
    Slist.insert(n);
    n = Slist.create_node(4);
    Slist.insert(n);
    n = Slist.create_node(3);
    Slist.insert(n);
    Slist.printAll();
    cout << "List size is " << Slist.length() << endl;

    DoublyLinkedList Dlist;
    n = Dlist.create_node(5);
    Dlist.insert(n);
    n = Dlist.create_node(6);
    Dlist.insert(n);
    n = Dlist.create_node(2);
    Dlist.insert(n);
    n = Dlist.create_node(4);
    Dlist.insert(n);
    n = Dlist.create_node(3);
    Dlist.insert(n);
    Dlist.printAll();
    Dlist.printAll_inv();
    cout << "List size is " << Dlist.length() << endl;
}