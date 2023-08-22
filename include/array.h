#ifndef ARRAY_H
#define ARRAY_H

#include "sort.h"
#include "time.h" // for time

/**
 * 建立 Array，可使用以下function
 * @param 陣列長度、(最小值、最大值)
 * @fn showArray - 列出原先生成的陣列
 * @fn showResult - 列出排序後的陣列
 * @fn bubbleSort - O(n^2)
 * @fn insertionSort - O(n^2)
 * @fn countingSort - O(n+k) k 為max-min+1
 * @fn mergeSort - O(nlogn)
 * @fn selectionSort - O(n^2)
 * @fn quickSort - O(nlogn)
 */
class Array {
  private:
    int* array;
    int* result;
    unsigned len;
    int min;
    int max;
    void assign(void) {
        for (int i = 0; i < len; i++) {
            array[i] = result[i] = rand() % (max - min + 1) + min;
        }
    }

  public:
    Array(void) : len(10), min(-10), max(10) {
        srand(time(NULL));
        array = new int[len];
        result = new int[len];
        assign();
    }
    Array(int len) : len(len), min(0), max(100) {
        srand(time(NULL));
        array = new int[len];
        result = new int[len];
        assign();
    }
    Array(int len, int min, int max) : len(len), min(min), max(max) {
        srand(time(NULL));
        if (this->min > this->max) {
            cout << "Error: minimum is bigger than maximum. (so I swapped them)" << endl;
            swap(this->min, this->max);
        }
        array = new int[len];
        result = new int[len];
        assign();
    }
    ~Array(void) {
        delete[] array;
        delete[] result;
    }
    void showArray(void) {
        for (int i = 0; i < len; i++) {
            cout << array[i] << " ";
        }
        cout << endl;
    }
    void showResult(void) {
        for (int i = 0; i < len; i++) {
            cout << result[i] << " ";
        }
        cout << endl;
    }
    void bubbleSort(void) { Sorting::bubbleSort(array, result, len); }
    void insertionSort(void) { Sorting::insertionSort(array, result, len); }
    void countingSort(void) { Sorting::countingSort(array, result, len, min, max); }
    void mergeSort(void) { Sorting::mergeSort(array, result, len); }
    void selectionSort(void) { Sorting::selectionSort(array, result, len); }
    void quickSort(void) { Sorting::quickSort(array, result, len); }
};

#endif