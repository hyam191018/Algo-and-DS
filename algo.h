#ifndef ALGO_H
#define ALGO_H

#include <iostream>
using namespace std;

#define SWAP(x, y)                                                                                 \
    do {                                                                                           \
        x ^= y;                                                                                    \
        y ^= x;                                                                                    \
        x ^= y;                                                                                    \
    } while (0);

class Sorting {
  public:
    static void bubble_sort(int* array, int len) {
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                if (array[i] < array[j]) {
                    SWAP(array[i], array[j]);
                }
            }
        }
    }
    static void insertion_sort(int* array, int len) {
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                if (array[i] < array[j]) {
                    SWAP(array[i], array[j]);
                }
            }
        }
    }
    static void quick_sort(int* array, int len) {
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                if (array[i] < array[j]) {
                    SWAP(array[i], array[j]);
                }
            }
        }
    }
    static void counting_sort(int* array, int len) {
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                if (array[i] < array[j]) {
                    SWAP(array[i], array[j]);
                }
            }
        }
    }
};

#endif