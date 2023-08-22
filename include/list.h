#ifndef LIST_H
#define LIST_H

#include <iostream>
using namespace std;

class ListNode {
  public:
    int num;
    ListNode* next;
    ListNode* prev;
    ListNode(int num) : num(num), next(nullptr), prev(nullptr) {}
};

class LinkedListBase {
  protected:
    ListNode* head;
    int size;
    void swapValue(ListNode* a, ListNode* b) {
        int tmp = a->num;
        a->num = b->num;
        b->num = tmp;
    }
    ListNode* findMin(ListNode* start) {
        ListNode* min = start;
        ListNode* tmp = start->next;
        while (tmp) {
            if (tmp->num < min->num) {
                min = tmp;
            }
            tmp = tmp->next;
        }
        return min;
    }

  public:
    LinkedListBase(void) : head(nullptr), size(0) {} // �ϥ�nullptr���NNULL
    int length(void) const { return size; }
    bool isEmpty(void) const { return size == 0; }
    void printAll(void) const {
        ListNode* tmp = head;
        cout << "List all: ";
        while (tmp) {
            cout << tmp->num << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }
    void sort(void) { // selection sort
        ListNode* tar = head;
        while (tar) {
            swapValue(tar, findMin(tar));
            tar = tar->next;
        }
    }
};

/**
 * �إ� Singly linked list�A�i�ϥΥH�U function (�������i����)
 * - �� ---------------
 * @fn length - �^�Ǫ���
 * @fn isEmpty - �P�_�O�_����
 * @fn printAll - �C�X�Ҧ�����
 * @fn sort - �N��list�i���ܱƧ�
 * - �s�W ---------------
 * @fn search
 * - @param n �d�䪺�Ʀr
 * - @return true �p�G�Ʀr�s�b
 * - @return false �p�G�Ʀr���s�b
 * @fn insert
 * - @param n �s�W�Ʀr
 * @fn remove
 * - @param n ���R�����Ʀr
 * - @return true �p�G���\�R��
 * - @return false �p�G�Ʀr���s�b
 */
class SinglyLinkedList : public LinkedListBase {
  public:
    bool search(int n) {
        if (size == 0) {
            return false;
        }
        ListNode* tmp = head;
        while (tmp) {
            if (tmp->num == n) {
                return true;
            }
            tmp = tmp->next;
        }
        return false;
    }
    void insert(int n) {
        if (search(n)) {
            return;
        }
        ListNode* node = new ListNode(n);
        if (size == 0) {
            head = node;
            size = 1;
            return;
        }
        node->next = head;
        head = node;
        size++;
    }
    bool remove(int n) {
        if (size == 0) {
            return false;
        }
        ListNode* prev = nullptr;
        ListNode* tmp = head;
        while (tmp) {
            if (tmp->num == n) {
                break;
            }
            prev = tmp;
            tmp = tmp->next;
        }
        if (tmp) {
            if (prev) {
                prev->next = tmp->next;
            } else {
                head = tmp->next;
            }
            delete tmp;
            size--;
            return true;
        }
        return false;
    }
};

/**
 * �إ� Doubly linked list�A�i�ϥΥH�U function (�������i����)
 * - �� ---------------
 * @fn length - �^�Ǫ���
 * @fn isEmpty - �P�_�O�_����
 * @fn printAll - �C�X�Ҧ�����
 * @fn sort - �N��list�i���ܱƧ�
 * @fn search - �d�䦨���O�_�s�b
 * - �мg ---------------
 * @fn insert
 * - @param n �s�W�Ʀr
 * @fn remove
 * - @param n ���R�����Ʀr
 * - @return true �p�G���\�R��
 * - @return false �p�G�Ʀr���s�b
 * @fn printAllInv �ϦV�L�X�Ҧ�����
 */
class DoublyLinkedList : public SinglyLinkedList {
  protected:
    ListNode* tail;

  public:
    DoublyLinkedList() : tail(nullptr) {}
    void insert(int n) {
        if (search(n)) { // ����
            return;
        }
        ListNode* node = new ListNode(n);
        if (size == 0) {
            head = tail = node;
            size = 1;
            return;
        }
        node->next = head;
        head->prev = node;
        head = node;
        size++;
    }
    bool remove(int n) {
        if (size == 0) {
            return false;
        }
        ListNode* prev = nullptr;
        ListNode* tmp = head;
        while (tmp) {
            if (tmp->num == n) {
                break;
            }
            prev = tmp;
            tmp = tmp->next;
        }
        if (tmp) {
            if (prev) {
                prev->next = tmp->next;
                if (tmp->next) {
                    (tmp->next)->prev = prev;
                }
            } else {
                head = tmp->next;
                head->prev = nullptr;
            }
            delete tmp;
            size--;
            return true;
        }
        return false;
    }
    void printAllInv(void) {
        ListNode* tmp = tail;
        cout << "List all invert: ";
        while (tmp) {
            cout << tmp->num << " ";
            tmp = tmp->prev;
        }
        cout << endl;
    }
};

/**
 * �H Singly linked list ��{ stack  (FILO) �ϥ�push���ܡA�����i����
 * - �s�W ---------------
 * @fn push - �N�Ʀr�걵��list�e��
 * - @param n �ؼмƦr
 * @fn pop - �qlist�e�ݲ��X�Ʀr
 * - @return Node�A�ݭn�������
 */
class Stack : public SinglyLinkedList {
  public:
    void push(int n) {
        ListNode* node = new ListNode(n);
        if (size == 0) {
            head = node;
            size = 1;
            return;
        }
        node->next = head;
        head = node;
        size++;
    }
    ListNode* pop(void) {
        if (size == 0) {
            return nullptr;
        }
        ListNode* n = head;
        head = n->next;
        size--;
        return n;
    }
};

/**
 * �H Doubly linked list ��{ queue  (FIFO) �ϥ�push���ܡA�����i����
 * - �s�W ---------------
 * @fn push - �N�Ʀr�걵��list�e��
 * - @param n �ؼмƦr
 * @fn pop - �qlist���ݲ��X�Ʀr
 * - @return Node�A�ݭn�������
 */
class Queue : public DoublyLinkedList {
  public:
    void push(int n) {
        ListNode* node = new ListNode(n);
        if (size == 0) {
            head = tail = node;
            size = 1;
            return;
        }
        head->prev = node;
        node->next = head;
        head = node;
        size++;
    }
    ListNode* pop(void) {
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

#endif