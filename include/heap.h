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
 * 基於array的 Max Heap實現，Max Heap能在保持array的特性時，額外提升insert(O(n) to
 * O(logn))與findMax(O(n) to O(1))的速度
 * @param size 支援陣列的長度
 * @param min  隨機數的最小值
 * @param max  隨機數的最大值
 * @fn insert 插入一個數字到 Max heap
 * - @return true 如果成功插入
 * - @return false 如果插入失敗
 * @fn findMax 找出Max heap中最大的數值
 * - @return NOT_FOUND 如果heap為空
 * @fn remove 將heap中的root(最大值)移除，並重新調整
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
        // 新增node後，將該node調整到正確的位置
        int node_index = heapSize;
        while (true) {
            if (node_index == 0) { // 爬到root了
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
        // 跟末端節點交換
        heapSize--;
        swap(array->origin[0], array->origin[heapSize]);
        // 將新的root調整到適當的位置
        int node_index = 0;
        while (true) {
            int left_child = leftChildIndex(node_index);
            int right_child = rightChildIndex(node_index);
            if (left_child != NOT_FOUND) {
                if (right_child != NOT_FOUND) {
                    // 挑選要跟right還是left比較
                    if (array->origin[left_child] > array->origin[right_child]) {
                        goto cmpLeft;
                    } else {
                        goto cmpRight;
                    }
                } else {
                    // 沒有right，只能跟left比較
                cmpLeft:
                    if (array->origin[node_index] < array->origin[left_child]) {
                        swap(array->origin[node_index], array->origin[left_child]);
                        node_index = left_child;
                    } else {
                        // 已經最佳了
                        break;
                    }
                }
            } else {
                if (right_child != NOT_FOUND) {
                // 沒有left，只能跟right比較
                cmpRight:
                    if (array->origin[node_index] < array->origin[right_child]) {
                        swap(array->origin[node_index], array->origin[right_child]);
                        node_index = right_child;
                    } else {
                        // 已經最佳了
                        break;
                    }
                } else {
                    // 沒有child node了
                    break;
                }
            }
        }
    }
};

/**
 * 基於array的 Min Heap實現，功能與Max heap類似，不過root總是儲存最小值
 * @param size 支援陣列的長度
 * @param min  隨機數的最小值
 * @param max  隨機數的最大值
 * @fn insert 插入一個數字到 Min heap
 * - @return true 如果成功插入
 * - @return false 如果插入失敗
 * @fn findMin 找出Min heap中最小的數值
 * - @return NOT_FOUND 如果heap為空
 * @fn remove 將heap中的root(最小值)移除，並重新調整
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
        // 新增node後，將該node調整到正確的位置
        int node_index = heapSize;
        while (true) {
            if (node_index == 0) { // 爬到root了
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
        // 跟末端節點交換
        heapSize--;
        swap(array->origin[0], array->origin[heapSize]);
        // 將新的root調整到適當的位置
        int node_index = 0;
        while (true) {
            int left_child = leftChildIndex(node_index);
            int right_child = rightChildIndex(node_index);
            if (left_child != NOT_FOUND) {
                if (right_child != NOT_FOUND) {
                    // 挑選要跟right還是left比較
                    if (array->origin[left_child] < array->origin[right_child]) {
                        goto cmpLeft;
                    } else {
                        goto cmpRight;
                    }
                } else {
                    // 沒有right，只能跟left比較
                cmpLeft:
                    if (array->origin[node_index] > array->origin[left_child]) {
                        swap(array->origin[node_index], array->origin[left_child]);
                        node_index = left_child;
                    } else {
                        // 已經最佳了
                        break;
                    }
                }
            } else {
                if (right_child != NOT_FOUND) {
                // 沒有left，只能跟right比較
                cmpRight:
                    if (array->origin[node_index] > array->origin[right_child]) {
                        swap(array->origin[node_index], array->origin[right_child]);
                        node_index = right_child;
                    } else {
                        // 已經最佳了
                        break;
                    }
                } else {
                    // 沒有child node了
                    break;
                }
            }
        }
    }
};
#endif
