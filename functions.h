#include <ctime>
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
};

class Item {
  private:
    int* array;
    unsigned len;
    int min;
    int max;
    void assign_random(void) {
        for (int i = 0; i < len; i++) {
            array[i] = rand() % (max - min + 1) + min;
        }
    }

  public:
    Item(void) : len(10), min(-10), max(10) {
        srand(time(NULL));
        array = new int[len];
        assign_random();
    }
    Item(int len) : len(len), min(0), max(100) {
        srand(time(NULL));
        array = new int[len];
        assign_random();
    }
    Item(int len, int min, int max) : len(len), min(min), max(max) {
        srand(time(NULL));
        if (this->min > this->max) {
            cout << "Error: minimum is bigger than maximum. (so I swapped them)" << endl;
            SWAP(this->min, this->max);
        }
        array = new int[len];
        assign_random();
    }
    ~Item(void) { delete array; }
    void show(void) {
        for (int i = 0; i < len; i++) {
            cout << array[i] << " ";
        }
        cout << endl;
    }
    void bubble_sort(void) { Sorting::bubble_sort(array, len); }
};