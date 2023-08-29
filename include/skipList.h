#ifndef SKIPLIST_H
#define SKIPLIST_H

#include "time.h"
#include <cstring>
#include <iostream>
using namespace std;

#define MAX_LEVEL 6

class SkipListNode {
  public:
    int level;
    int value;
    SkipListNode** forward;
    SkipListNode(int level, int value) : level(level), value(value) {
        forward = new SkipListNode*[level + 1];
        for (int i = 0; i <= level; i++) {
            forward[i] = nullptr;
        }
    };
};

class SkipList {
  private:
    /**
     *     level 3-S ---> nullptr
     *     level 2-S ---> nullptr
     *     level 1-S ---> nullptr
     *     level 0-S ---> nullptr
     */

    SkipListNode* sentinel; // �C��LEVEL�����|���V�P�@��sentinel
    int randomLevel(void) {
        int res = 0;
        while (rand() % 2 && res < MAX_LEVEL) {
            res++;
        }
        return res;
    }

  public:
    SkipList(void) {
        srand(time(nullptr));
        sentinel = new SkipListNode(MAX_LEVEL, INT32_MIN);
    }
    void show(void);
    SkipListNode* search(int num);
    void insert(int num);
    void remove(int num);
};
void SkipList::show(void) {
    for (int i = MAX_LEVEL; i >= 0; i--) {
        SkipListNode* tmp = sentinel;
        cout << "Level " << i << " - ";
        while (tmp) {
            if (tmp->value != INT32_MIN) {
                cout << tmp->value << " ";
            }
            tmp = tmp->forward[i];
        }
        cout << endl;
    }
}
SkipListNode* SkipList::search(int num) {
    SkipListNode* tmp = sentinel;
    int current_level = MAX_LEVEL;
    while (current_level != -1) { // ���e
        if (num == tmp->value) {
            // cout << "Find " << num << " at level " << current_level << endl;
            return tmp;
        } else if (num > tmp->value) {
            // �M�w���e�٬O�V�U
            if (tmp->forward[current_level] && num >= tmp->forward[current_level]->value) {
                tmp = tmp->forward[current_level];
            } else {
                current_level--;
            }
        }
    }
    return nullptr;
}
void SkipList::insert(int num) {
    SkipListNode* tmp = sentinel;
    SkipListNode* prev[MAX_LEVEL + 1];
    for (int i = MAX_LEVEL; i >= 0; i--) {
        prev[i] = sentinel;
    }
    for (int i = MAX_LEVEL; i >= 0; i--) {   // �q�̤W�hLEVEL�}�l�j�M
        while (tmp && (num >= tmp->value)) { // ���e
            prev[i] = tmp;
            tmp = tmp->forward[i];
        }
        tmp = prev[i];
        if (num == tmp->value) { // ����
            return;
        }
    }
    // ���J��prev����
    /**
     *     level 3-S ---> X -------------------------------> nullptr
     *     level 2-S ---> X ---> Y ---> Z----> new_node ---> nullptr
     *     level 1-S ---> X ---> Y ----------> new_node ---> nullptr
     *     level 0-S ---> X ---> Y ---> Z ---> new_node ---> nullptr
     */

    int new_level = randomLevel();
    SkipListNode* new_node = new SkipListNode(new_level, num);
    for (int i = new_level; i >= 0; i--) {
        new_node->forward[i] = prev[i]->forward[i];
        prev[i]->forward[i] = new_node;
    }
}
void SkipList::remove(int num) {
    SkipListNode* tmp = sentinel;
    SkipListNode* prev[MAX_LEVEL + 1];
    for (int i = MAX_LEVEL; i >= 0; i--) {
        prev[i] = sentinel;
    }
    for (int i = MAX_LEVEL; i >= 0; i--) {  // �q�̤W�hLEVEL�}�l�j�M
        while (tmp && (num > tmp->value)) { // ���e
            prev[i] = tmp;
            tmp = tmp->forward[i];
        }
        tmp = prev[i];
    }
    if (!prev[0]->forward[0] || prev[0]->forward[0]->value != num) { // �ˬd�O�_�s�b
        return;
    }

    for (int i = MAX_LEVEL; i >= 0; i--) { // �s�b: �R��prev�ҫ��V���`�I
        prev[i]->forward[i] = prev[i]->forward[i] ? prev[i]->forward[i]->forward[i] : nullptr;
    }
}
#endif