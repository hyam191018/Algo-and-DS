#ifndef ALGO_H
#define ALGO_H

#include <cstring>
#include <iostream>
using namespace std;

#define SWAP(x, y)                                                                                 \
    do {                                                                                           \
        x ^= y;                                                                                    \
        y ^= x;                                                                                    \
        x ^= y;                                                                                    \
    } while (0);

class Sorting {
  private:
    // �N�@��array�������k���array
    static void merge_sort_divide(int* array, int* result, int len) {
        if (len <= 1) {
            return;
        }
        int mid = len / 2;
        merge_sort_divide(array, result, mid);
        merge_sort_divide(array + mid, result + mid, len - mid);
        merge_sort_conquer(array, result, 0, mid, len);
    }
    // ���k���array���w�ƧǦn�A�X�֨�result�A�A�ƻs�^array
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
                    SWAP(result[i], result[j]);
                }
            }
        }
    }
    static void insertion_sort(int* array, int* result, int len) {
        memcpy(result, array, len * sizeof(int));
        for (int i = 1; i < len; i++) {
            // �q�k�V������
            for (int j = i; j > 0; j--) {
                if (result[j] > result[j - 1]) {
                    break;
                }
                SWAP(result[j], result[j - 1]);
            }
        }
    }
    static void counting_sort(int* array, int* result, int len, int min, int max) {
        int range = max - min + 1;
        int counter[range];
        fill(counter, counter + range, 0);
        // O(n)
        for (int i = 0; i < len; i++) {
            counter[array[i]]++;
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
    }
    static void merge_sort(int* array, int* result, int len) {
        // Top-down
        int mid = len / 2;
        // left array 0~mid
        merge_sort_divide(array, result, mid);
        // right array mid+1~len
        merge_sort_divide(array + mid, result + mid, len - mid);
        // merge
        merge_sort_conquer(array, result, 0, mid, len);
        memcpy(result, array, len * sizeof(int));
    }
    static void selection_sort(int* array, int* result, int len) {}
    static void quick_sort(int* array, int* result, int len) {}
    static void heap_sort(int* array, int* result, int len) {}
};

#endif