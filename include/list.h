#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
using namespace std;

struct ListNode {
    int num;
    ListNode* next;
    ListNode* prev;
};

ListNode* create_node(int num) {
    ListNode* n = new ListNode;
    n->num = num;
    n->next = n->prev = NULL;
}

class LinkedListBase {
  protected:
    ListNode* head;
    int size;

  public:
    LinkedListBase() : head(nullptr), size(0) {} // 使用nullptr取代NULL
    int length() const { return size; }
    bool isEmpty() const { return size == 0; }
    void printAll() const {
        ListNode* tmp = head;
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
    void insert(ListNode* n) {
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
    ListNode* tail;

  public:
    DoublyLinkedList() : tail(nullptr) {}
    void insert(ListNode* n) {
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
        ListNode* tmp = tail;
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
    void push(ListNode* n) {
        if (size == 0) {
            head = n;
            size = 1;
            return;
        }
        n->next = head;
        head = n;
        size++;
    }
    ListNode* pop() {
        if (size == 0) {
            return nullptr;
        }
        ListNode* n = head;
        head = n->next;
        size--;
        return n;
    }
};

class Queue : public DoublyLinkedList {
  public:
    void push(ListNode* n) {
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
    ListNode* pop() {
        if (size == 0) {
            return nullptr;
        }
        ListNode* n = tail;
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

int hash_function(string key, int mod) {
    int hash = 0;
    for (char c : key) {
        hash += static_cast<int>(c);
    }
    return hash % mod;
}

class HashNode {
  public:
    string key;
    int value;
    bool used;
    HashNode(void) : key(""), value(0), used(false) {}
    bool isUsed(void) { return used; }
};

class HashMap : public HashNode {
  private:
    HashNode* array;
    int array_len;

  public:
    HashMap(void) {
        array = new HashNode[10];
        array_len = 10;
    }
    HashMap(int len) {
        array = new HashNode[len];
        array_len = len;
    }
    ~HashMap(void) { delete[] array; }
    void showMap(void) {
        for (int i = 0; i < array_len; i++) {
            if (!array[i].isUsed())
                continue;
            cout << "key: " << array[i].key << ", value: " << array[i].value << endl;
        }
    }
    bool insert(string key, int value) {
        int h = hash_function(key, array_len);
        for (int i = 0; i < array_len; i++) {
            int point = (h + i) % array_len;

            if (array[point].isUsed()) {
                if (!array[point].key.compare(key)) { // update
                    array[point].value = value;
                    return true;
                } else { // collision
                    continue;
                }
            } else { // insert
                array[point].key = key;
                array[point].value = value;
                array[point].used = true;
                return true;
            }
        }
        return false;
    }
    bool lookup(string key, int& value) {
        int h = hash_function(key, array_len);
        for (int i = 0; i < array_len; i++) {
            int point = (h + i) % array_len;

            if (array[point].isUsed()) {
                if (!array[point].key.compare(key)) { // find
                    value = array[point].value;
                    return true;
                } else { // collision
                    continue;
                }
            } else {
                break;
            }
        }
        return false;
    }
    bool remove(string key) {
        int h = hash_function(key, array_len);
        for (int i = 0; i < array_len; i++) {
            int point = (h + i) % array_len;

            if (array[point].isUsed()) {
                if (!array[point].key.compare(key)) { // find and then remove
                    array[point].key = "";
                    array[point].value = 0;
                    array[point].used = false;
                    return true;
                } else { // collision
                    continue;
                }
            } else {
                break;
            }
        }
        return false;
    }
    void clear(void) {
        for (int i = 0; i < array_len; i++) {
            array[i].key = "";
            array[i].value = 0;
            array[i].used = false;
        }
    }
};

#endif