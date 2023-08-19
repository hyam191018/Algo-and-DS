#ifndef ALGO_H
#define ALGO_H

#include <cstring>
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
        delete tmp;
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
    static void quick_sort(int* array, int* result, int len) {}
    static void heap_sort(int* array, int* result, int len) {}
};

#endif