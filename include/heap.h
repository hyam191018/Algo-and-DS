#ifndef HEAP_H
#define HEAP_H

#include "array.h"
#define NOT_FOUND INT32_MIN

class HeapBase {
  protected:
    Array* array;
    int heapSize;
    bool isFull(void) { return heapSize < array->len ? false : true; }
    bool isEmpty(void) { return heapSize == 0; }
    int parentIndex(int index) {
        if (index <= 0) {
            return NOT_FOUND;
        }
        return (index - 1) >> 1; // parent = (child - 1) / 2
    }
    int leftChildIndex(int index) {
        int result = (index << 1) + 1;
        return result > heapSize - 1 ? NOT_FOUND : result;
    }
    int rightChildIndex(int index) {
        int result = (index << 1) + 2;
        return result > heapSize - 1 ? NOT_FOUND : result;
    }
    HeapBase(void) {
        array = new Array;
        heapSize = 0;
    }
    HeapBase(int size) {
        array = new Array(size);
        heapSize = 0;
    }
    HeapBase(int size, int min, int max) {
        array = new Array(size, min, max);
        heapSize = 0;
    }
    ~HeapBase(void) { delete array; }

  public:
    void showHeap(void) {
        for (int i = 0; i < heapSize; i++) {
            cout << array->origin[i] << " ";
        }
        cout << endl;
    }
};

/**
 * ���array�� Max Heap��{�AMax Heap��b�O��array���S�ʮɡA�B�~����insert(O(n) to
 * O(logn))�PfindMax(O(n) to O(1))���t��
 * @param size �䴩�}�C������
 * @param min  �H���ƪ��̤p��
 * @param max  �H���ƪ��̤j��
 * @fn insert ���J�@�ӼƦr�� Max heap
 * - @return true �p�G���\���J
 * - @return false �p�G���J����
 * @fn findMax ��XMax heap���̤j���ƭ�
 * - @return NOT_FOUND �p�Gheap����
 * @fn remove �Nheap����root(�̤j��)�����A�í��s�վ�
 */
class MaxHeap : public HeapBase {
  public:
    MaxHeap(int size) : HeapBase(size) {}
    MaxHeap(int size, int min, int max) : HeapBase(size, min, max) {}
    bool insert(int num) {
        if (isFull()) {
            return false;
        }
        array->origin[heapSize] = num;
        // �s�Wnode��A�N��node�վ�쥿�T����m
        int node_index = heapSize;
        while (true) {
            if (node_index == 0) { // ����root�F
                break;
            }
            int parent = parentIndex(node_index);
            if (array->origin[node_index] > array->origin[parent]) {
                swap(array->origin[node_index], array->origin[parent]);
                node_index = parent;
            } else {
                break;
            }
        }
        heapSize++;
        return true;
    }
    int findMax(void) { return isEmpty() ? NOT_FOUND : array->origin[0]; }
    void remove(void) {
        if (isEmpty()) {
            return;
        }
        // �򥽺ݸ`�I�洫
        heapSize--;
        swap(array->origin[0], array->origin[heapSize]);
        // �N�s��root�վ��A����m
        int node_index = 0;
        while (true) {
            int left_child = leftChildIndex(node_index);
            int right_child = rightChildIndex(node_index);
            if (left_child != NOT_FOUND) {
                if (right_child != NOT_FOUND) {
                    // �D��n��right�٬Oleft���
                    if (array->origin[left_child] > array->origin[right_child]) {
                        goto cmpLeft;
                    } else {
                        goto cmpRight;
                    }
                } else {
                    // �S��right�A�u���left���
                cmpLeft:
                    if (array->origin[node_index] < array->origin[left_child]) {
                        swap(array->origin[node_index], array->origin[left_child]);
                        node_index = left_child;
                    } else {
                        // �w�g�̨ΤF
                        break;
                    }
                }
            } else {
                if (right_child != NOT_FOUND) {
                // �S��left�A�u���right���
                cmpRight:
                    if (array->origin[node_index] < array->origin[right_child]) {
                        swap(array->origin[node_index], array->origin[right_child]);
                        node_index = right_child;
                    } else {
                        // �w�g�̨ΤF
                        break;
                    }
                } else {
                    // �S��child node�F
                    break;
                }
            }
        }
    }
};

/**
 * ���array�� Min Heap��{�A�\��PMax heap�����A���Lroot�`�O�x�s�̤p��
 * @param size �䴩�}�C������
 * @param min  �H���ƪ��̤p��
 * @param max  �H���ƪ��̤j��
 * @fn insert ���J�@�ӼƦr�� Min heap
 * - @return true �p�G���\���J
 * - @return false �p�G���J����
 * @fn findMin ��XMin heap���̤p���ƭ�
 * - @return NOT_FOUND �p�Gheap����
 * @fn remove �Nheap����root(�̤p��)�����A�í��s�վ�
 */
class MinHeap : public HeapBase {
  public:
    MinHeap(int size) : HeapBase(size) {}
    MinHeap(int size, int min, int max) : HeapBase(size, min, max) {}
    bool insert(int num) {
        if (isFull()) {
            return false;
        }
        array->origin[heapSize] = num;
        // �s�Wnode��A�N��node�վ�쥿�T����m
        int node_index = heapSize;
        while (true) {
            if (node_index == 0) { // ����root�F
                break;
            }
            int parent = parentIndex(node_index);
            if (array->origin[node_index] < array->origin[parent]) {
                swap(array->origin[node_index], array->origin[parent]);
                node_index = parent;
            } else {
                break;
            }
        }
        heapSize++;
        return true;
    }
    int findMin(void) { return isEmpty() ? NOT_FOUND : array->origin[0]; }
    void remove(void) {
        if (isEmpty()) {
            return;
        }
        // �򥽺ݸ`�I�洫
        heapSize--;
        swap(array->origin[0], array->origin[heapSize]);
        // �N�s��root�վ��A����m
        int node_index = 0;
        while (true) {
            int left_child = leftChildIndex(node_index);
            int right_child = rightChildIndex(node_index);
            if (left_child != NOT_FOUND) {
                if (right_child != NOT_FOUND) {
                    // �D��n��right�٬Oleft���
                    if (array->origin[left_child] < array->origin[right_child]) {
                        goto cmpLeft;
                    } else {
                        goto cmpRight;
                    }
                } else {
                    // �S��right�A�u���left���
                cmpLeft:
                    if (array->origin[node_index] > array->origin[left_child]) {
                        swap(array->origin[node_index], array->origin[left_child]);
                        node_index = left_child;
                    } else {
                        // �w�g�̨ΤF
                        break;
                    }
                }
            } else {
                if (right_child != NOT_FOUND) {
                // �S��left�A�u���right���
                cmpRight:
                    if (array->origin[node_index] > array->origin[right_child]) {
                        swap(array->origin[node_index], array->origin[right_child]);
                        node_index = right_child;
                    } else {
                        // �w�g�̨ΤF
                        break;
                    }
                } else {
                    // �S��child node�F
                    break;
                }
            }
        }
    }
};
#endif
