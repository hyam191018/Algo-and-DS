#ifndef SORT_H
#define SORT_H

#include <cstring>
#include <ctime>
#include <iostream>
using namespace std;

class Sorting {
  private:
    // 將一個array分成左右兩個array
    static void merge_sort_divide(int* array, int* result, int len) {
        if (len <= 1) {
            return;
        }
        int mid = len / 2;
        merge_sort_divide(array, result, mid);
        merge_sort_divide(array + mid, result + mid, len - mid);
        merge_sort_conquer(array, result, 0, mid, len);
    }
    // 左右兩個array都已排序好，合併到result，再複製回array
    static void merge_sort_conquer(int* array, int* result, int left, int right, int len) {
        int left_len = right;
        int left_index = 0;
        int right_len = len - left_len;
        int right_index = 0;
        for (int i = 0; i < len; i++) {
            if (left_index == left_len) {
                memcpy(&result[i], &array[right + right_index],
                       (right_len - right_index) * sizeof(int));
                break;
            } else if (right_index == right_len) {
                memcpy(&result[i], &array[left_index], (left_len - left_index) * sizeof(int));
                break;
            } else if (array[left_index] <= array[right + right_index]) {
                result[i] = array[left_index];
                left_index++;
            } else {
                result[i] = array[right + right_index];
                right_index++;
            }
        }
        memcpy(array, result, len * sizeof(int));
    }
    static void _quick_sort(int* array, int len) {
        if (len < 2) {
            return;
        }
        int pivot = len / 2;
        // 先將pivot移動到最後一位
        swap(array[pivot], array[len - 1]);

        // 左邊的數字都要比array[len-1]小
        // 右邊的數字都要比array[len-1]大
        int store = 0;
        for (int i = 0; i < len - 1; i++) {
            if (array[i] < array[len - 1]) {
                swap(array[i], array[store]);
                store++;
            }
        }
        // 最後跟store交換回正確的位置
        swap(array[store], array[len - 1]);

        // 左右繼續遞迴
        _quick_sort(array, store);
        _quick_sort(array + store + 1, len - store - 1);
    }

  public:
    static void bubble_sort(int* array, int* result, int len) {
        memcpy(result, array, len * sizeof(int));
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                if (result[i] < result[j]) {
                    swap(result[i], result[j]);
                }
            }
        }
    }
    static void insertion_sort(int* array, int* result, int len) {
        memcpy(result, array, len * sizeof(int));
        for (int i = 1; i < len; i++) {
            // 從右向左掃秒
            for (int j = i; j > 0; j--) {
                if (result[j] > result[j - 1]) {
                    break;
                }
                swap(result[j], result[j - 1]);
            }
        }
    }
    static void counting_sort(int* array, int* result, int len, int min, int max) {
        int range = max - min + 1;
        int* counter = new int[range];
        fill(counter, counter + range, 0);
        // O(n)
        for (int i = 0; i < len; i++) {
            counter[array[i] - min]++;
        }
        // O(k) : max-min+1
        int loc = 0;
        for (int i = 0; i < range; i++) {
            if (!counter[i]) {
                continue;
            }
            fill(result + loc, result + loc + counter[i], i + min);
            loc += counter[i];
        }
        delete[] counter;
    }
    static void merge_sort(int* array, int* result, int len) {
        // backup
        int* tmp = new int[len];
        memcpy(tmp, array, len * sizeof(int));
        // Top-down
        int mid = len / 2;
        // left array 0~mid
        merge_sort_divide(array, result, mid);
        // right array mid+1~len
        merge_sort_divide(array + mid, result + mid, len - mid);
        // merge
        merge_sort_conquer(array, result, 0, mid, len);
        // return
        memcpy(array, tmp, len * sizeof(int));
        delete[] tmp;
    }
    static void selection_sort(int* array, int* result, int len) {
        memcpy(result, array, len * sizeof(int));
        for (int i = 0; i < len; i++) {
            int min = i;
            for (int j = i + 1; j < len; j++) {
                if (result[j] < result[min]) {
                    min = j;
                }
            }
            swap(result[i], result[min]);
        }
    }
    static void quick_sort(int* array, int* result, int len) {
        memcpy(result, array, len * sizeof(int));
        _quick_sort(result, len);
    }
};

class Item {
  private:
    int* array;
    int* result;
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
        result = new int[len];
        assign();
    }
    Item(int len) : len(len), min(0), max(100) {
        srand(time(NULL));
        array = new int[len];
        result = new int[len];
        assign();
    }
    Item(int len, int min, int max) : len(len), min(min), max(max) {
        srand(time(NULL));
        if (this->min > this->max) {
            cout << "Error: minimum is bigger than maximum. (so I swapped them)" << endl;
            swap(this->min, this->max);
        }
        array = new int[len];
        result = new int[len];
        assign();
    }
    ~Item(void) {
        delete[] array;
        delete[] result;
    }
    void show_array(void) {
        for (int i = 0; i < len; i++) {
            cout << array[i] << " ";
        }
        cout << endl;
    }
    void show_result(void) {
        for (int i = 0; i < len; i++) {
            cout << result[i] << " ";
        }
        cout << endl;
    }
    void bubble_sort(void) { Sorting::bubble_sort(array, result, len); }
    void insertion_sort(void) { Sorting::insertion_sort(array, result, len); }
    void counting_sort(void) { Sorting::counting_sort(array, result, len, min, max); }
    void merge_sort(void) { Sorting::merge_sort(array, result, len); }
    void selection_sort(void) { Sorting::selection_sort(array, result, len); }
    void quick_sort(void) { Sorting::quick_sort(array, result, len); }
};

#endif