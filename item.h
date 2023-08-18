#ifndef ITEM_H
#define ITEM_H

#include "algo.h"
#include <ctime>
#include <iostream>

class Item {
  private:
    int* array;
    unsigned len;
    int min;
    int max;
    void assign(void) {
        for (int i = 0; i < len; i++) {
            array[i] = rand() % (max - min + 1) + min;
        }
    }

  public:
    Item(void) : len(10), min(-10), max(10) {
        srand(time(NULL));
        array = new int[len];
        assign();
    }
    Item(int len) : len(len), min(0), max(100) {
        srand(time(NULL));
        array = new int[len];
        assign();
    }
    Item(int len, int min, int max) : len(len), min(min), max(max) {
        srand(time(NULL));
        if (this->min > this->max) {
            cout << "Error: minimum is bigger than maximum. (so I swapped them)" << endl;
            SWAP(this->min, this->max);
        }
        array = new int[len];
        assign();
    }
    ~Item(void) { delete array; }
    void show(void) {
        for (int i = 0; i < len; i++) {
            cout << array[i] << " ";
        }
        cout << endl;
    }
    void bubble_sort(void) { Sorting::bubble_sort(array, len); }
    void insertion_sort(void) { Sorting::insertion_sort(array, len); }
    void quick_sort(void) { Sorting::quick_sort(array, len); }
    void counting_sort(void) { Sorting::counting_sort(array, len); }
};

#endif