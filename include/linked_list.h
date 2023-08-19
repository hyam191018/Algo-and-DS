#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
using namespace std;

struct node {
    int num;
    struct node* next;
};

class SinglyLinkedList {
  private:
    node* head;
    node* tail;
    int size;

  public:
    SinglyLinkedList(void) : head(NULL), tail(NULL), size(0){};
    int length(void) { return size; }
    node* create_node(int num) {
        node* n = new node;
        n->num = num;
        n->next = NULL;
        return n;
    }
    bool isEmpty(void) {
        if (size == 0) {
            return true;
        }
        return false;
    }
    void insert(node* n) {
        if (size == 0) {
            head = tail = n;
            size = 1;
            return;
        }
        n->next = head;
        head = n;
        size++;
    }
    void printAll(void) {
        node* tmp = head;
        cout << "List all: ";
        while (tmp) {
            cout << tmp->num << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }
};

#endif
