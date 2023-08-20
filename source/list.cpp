#include "../include/list.h"

int main(void) {
    SinglyLinkedList Slist;
    cout << "<< Testing Singly Linked list >>" << endl;
    ListNode* n;
    n = create_node(5);
    Slist.insert(n);
    n = create_node(6);
    Slist.insert(n);
    n = create_node(2);
    Slist.insert(n);
    n = create_node(4);
    Slist.insert(n);
    n = create_node(3);
    Slist.insert(n);
    Slist.printAll();
    cout << "Singly List size is " << Slist.length() << endl;

    DoublyLinkedList Dlist;
    cout << "<< Testing Doubly Linked list >>" << endl;
    n = create_node(5);
    Dlist.insert(n);
    n = create_node(6);
    Dlist.insert(n);
    n = create_node(2);
    Dlist.insert(n);
    n = create_node(4);
    Dlist.insert(n);
    n = create_node(3);
    Dlist.insert(n);
    Dlist.printAll();
    Dlist.printAllInv();
    cout << "Doubly List size is " << Dlist.length() << endl;

    Stack stack;
    cout << "<< Testing Stack >>" << endl;
    n = create_node(5);
    stack.push(n);
    n = create_node(6);
    stack.push(n);
    n = create_node(2);
    stack.push(n);
    n = create_node(4);
    stack.push(n);
    n = create_node(3);
    stack.push(n);
    stack.printAll();
    stack.pop();
    stack.pop();
    stack.printAll();
    n = create_node(7);
    stack.push(n);
    n = create_node(7);
    stack.push(n);
    stack.printAll();
    cout << "Stack size is " << stack.length() << endl;

    Queue queue;
    cout << "<< Testing Queue >>" << endl;
    n = create_node(5);
    queue.push(n);
    n = create_node(6);
    queue.push(n);
    n = create_node(2);
    queue.push(n);
    n = create_node(4);
    queue.push(n);
    n = create_node(3);
    queue.push(n);
    queue.printAll();
    queue.pop();
    queue.pop();
    queue.printAll();
    n = create_node(7);
    queue.push(n);
    n = create_node(7);
    queue.push(n);
    queue.printAll();
    cout << "Queue size is " << queue.length() << endl;
}