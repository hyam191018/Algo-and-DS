#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
using namespace std;

struct Node {
    int num;
    Node* next;
    Node* prev;
};

Node* create_node(int num) {
    Node* n = new Node;
    n->num = num;
    n->next = n->prev = NULL;
}

class LinkedListBase {
  protected:
    Node* head;
    int size;

  public:
    LinkedListBase() : head(nullptr), size(0) {}
    int length() const { return size; }
    bool isEmpty() const { return size == 0; }
    void printAll() const {
        Node* tmp = head;
        cout << "List all: ";
        while (tmp) {
            cout << tmp->num << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }
};

class SinglyLinkedList : public LinkedListBase {
  public:
    void insert(Node* n) {
        if (size == 0) {
            head = n;
            size = 1;
            return;
        }
        n->next = head;
        head = n;
        size++;
    }
};

class DoublyLinkedList : public LinkedListBase {
  protected:
    Node* tail;

  public:
    DoublyLinkedList() : tail(nullptr) {}
    void insert(Node* n) {
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
    void printAllInv() const {
        Node* tmp = tail;
        cout << "List all invert: ";
        while (tmp) {
            cout << tmp->num << " ";
            tmp = tmp->prev;
        }
        cout << endl;
    }
};

class Stack : public SinglyLinkedList {
  public:
    void push(Node* n) {
        if (size == 0) {
            head = n;
            size = 1;
            return;
        }
        n->next = head;
        head = n;
        size++;
    }
    Node* pop() {
        if (size == 0) {
            return nullptr;
        }
        Node* n = head;
        head = n->next;
        size--;
        return n;
    }
};

class Queue : public DoublyLinkedList {
  public:
    void push(Node* n) {
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
    Node* pop() {
        if (size == 0) {
            return nullptr;
        }
        Node* n = tail;
        tail = n->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        size--;
        return n;
    }
};

#endif