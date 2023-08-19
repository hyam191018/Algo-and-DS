#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
using namespace std;

struct node {
    int num;
    struct node* next;
    struct node* prev;
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

class DoublyLinkedList {
  private:
    node* head;
    node* tail;
    int size;

  public:
    DoublyLinkedList(void) : head(NULL), tail(NULL), size(0){};
    int length(void) { return size; }
    node* create_node(int num) {
        node* n = new node;
        n->num = num;
        n->next = NULL;
        n->prev = NULL;
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
        head->prev = n;
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
    void printAll_inv(void) {
        node* tmp = tail;
        cout << "List all invert: ";
        while (tmp) {
            cout << tmp->num << " ";
            tmp = tmp->prev;
        }
        cout << endl;
    }
};

// use Singly linked list
class Stack {
  private:
    node* head;
    int size;

  public:
    Stack(void) : head(NULL), size(0){};
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
    void push(node* n) {
        if (size == 0) {
            head = n;
            size = 1;
            return;
        }
        n->next = head;
        head = n;
        size++;
    }
    node* pop(void) {
        if (size == 0) {
            return NULL;
        }
        node* n = head;
        head = n->next;
        size--;
        return n;
    }
    void printAll(void) {
        node* tmp = head;
        cout << "Top to down: ";
        while (tmp) {
            cout << tmp->num << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }
};

// use Doubly linked list
class Queue {
  private:
    node* head;
    node* tail;
    int size;

  public:
    Queue(void) : head(NULL), tail(NULL), size(0){};
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
    void push(node* n) {
        if (size == 0) {
            head = tail = n;
            size = 1;
            return;
        }
        head->prev = n;
        n->next = head;
        head = n;
        size++;
    }
    node* pop(void) {
        if (size == 0) {
            return NULL;
        }
        node* n = tail;
        tail = n->prev;
        tail->next = NULL;
        size--;
        return n;
    }
    void printAll(void) {
        node* tmp = head;
        cout << "Top to down: ";
        while (tmp) {
            cout << tmp->num << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }
    void printAll_inv(void) {
        node* tmp = tail;
        cout << "List all invert: ";
        while (tmp) {
            cout << tmp->num << " ";
            tmp = tmp->prev;
        }
        cout << endl;
    }
};

#endif
