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
    LinkedListBase(void) : head(nullptr), size(0) {} // 使用nullptr取代NULL
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
 * 建立 Singly linked list，可使用以下 function (成員不可重複)
 * - 基本 ---------------
 * @fn length - 回傳長度
 * @fn isEmpty - 判斷是否為空
 * @fn printAll - 列出所有元素
 * @fn sort - 將此list進行選擇排序
 * - 新增 ---------------
 * @fn search
 * - @param 查找的數字
 * - @return true 如果數字存在
 * - @return false 如果數字不存在
 * @fn insert
 * - @param 新增數字
 * @fn remove
 * - @param 欲刪除的數字
 * - @return true 如果成功刪除
 * - @return false 如果數字不存在
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
 * 建立 Doubly linked list，可使用以下 function (成員不可重複)
 * - 基本 ---------------
 * @fn length - 回傳長度
 * @fn isEmpty - 判斷是否為空
 * @fn printAll - 列出所有元素
 * @fn sort - 將此list進行選擇排序
 * @fn search - 查找成員是否存在
 * - 覆寫 ---------------
 * @fn insert
 * - @param 新增數字
 * @fn remove
 * - @param 欲刪除的數字
 * - @return true 如果成功刪除
 * - @return false 如果數字不存在
 * @fn printAllInv 反向印出所有元素
 */
class DoublyLinkedList : public SinglyLinkedList {
  protected:
    ListNode* tail;

  public:
    DoublyLinkedList() : tail(nullptr) {}
    void insert(int n) {
        if (search(n)) { // 重複
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
 * 以 Singly linked list 實現 stack  (FILO) 使用push的話，成員可重複
 * - 新增 ---------------
 * @fn push - 將數字串接到list前端
 * @fn pop - 從list前端移出數字
 * - @return Node，需要手動釋放
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

/**
 * 以 Doubly linked list 實現 queue  (FIFO) 使用push的話，成員可重複
 * - 新增 ---------------
 * @fn push - 將數字串接到list前端
 * @fn pop - 從list末端移出數字
 * - @return Node，需要手動釋放
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

#endif