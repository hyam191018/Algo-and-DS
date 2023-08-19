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

    Stack stack;
    n = stack.create_node(5);
    stack.push(n);
    n = stack.create_node(6);
    stack.push(n);
    n = stack.create_node(2);
    stack.push(n);
    n = stack.create_node(4);
    stack.push(n);
    n = stack.create_node(3);
    stack.push(n);
    stack.printAll();
    stack.pop();
    stack.pop();
    stack.printAll();
    n = stack.create_node(7);
    stack.push(n);
    n = stack.create_node(7);
    stack.push(n);
    stack.printAll();
    cout << "Stack size is " << stack.length() << endl;

    Queue queue;
    n = queue.create_node(5);
    queue.push(n);
    n = queue.create_node(6);
    queue.push(n);
    n = queue.create_node(2);
    queue.push(n);
    n = queue.create_node(4);
    queue.push(n);
    n = queue.create_node(3);
    queue.push(n);
    queue.printAll();
    queue.pop();
    queue.pop();
    queue.printAll();
    n = queue.create_node(7);
    queue.push(n);
    n = queue.create_node(7);
    queue.push(n);
    queue.printAll();
    cout << "Queue size is " << queue.length() << endl;
}