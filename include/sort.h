#ifndef SORT_H
#define SORT_H

#include <cstring>  // for memcpy
#include <iostream> // for swap
using namespace std;

/**
 * �򥻪��ƧǤ�k
 * @fn bubbleSort - O(n^2)
 * @fn insertionSort - O(n^2)
 * @fn countingSort - O(n+k) k ��max-min+1
 * @fn mergeSort - O(nlogn)
 * @fn selectionSort - O(n^2)
 * @fn quickSort - O(nlogn)
 */
class Sorting {
  private:
    // �N�@��array�������k���array
    static void mergeSort_divide(int* array, int* result, int len) {
        if (len <= 1) {
            return;
        }
        int mid = len / 2;
        mergeSort_divide(array, result, mid);
        mergeSort_divide(array + mid, result + mid, len - mid);
        mergeSort_conquer(array, result, 0, mid, len);
    }
    // ���k���array���w�ƧǦn�A�X�֨�result�A�A�ƻs�^array
    static void mergeSort_conquer(int* array, int* result, int left, int right, int len) {
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
    static void _quickSort(int* array, int len) {
        if (len < 2) {
            return;
        }
        int pivot = len / 2;
        // ���Npivot���ʨ�̫�@��
        swap(array[pivot], array[len - 1]);

        // ���䪺�Ʀr���n��array[len-1]�p
        // �k�䪺�Ʀr���n��array[len-1]�j
        int store = 0;
        for (int i = 0; i < len - 1; i++) {
            if (array[i] < array[len - 1]) {
                swap(array[i], array[store]);
                store++;
            }
        }
        // �̫��store�洫�^���T����m
        swap(array[store], array[len - 1]);
        // ���k�~�򻼰j
        _quickSort(array, store);
        _quickSort(array + store + 1, len - store - 1);
    }

  public:
    static void bubbleSort(int* array, int* result, int len) {
        memcpy(result, array, len * sizeof(int));
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                if (result[i] < result[j]) {
                    swap(result[i], result[j]);
                }
            }
        }
    }
    static void insertionSort(int* array, int* result, int len) {
        memcpy(result, array, len * sizeof(int));
        for (int i = 1; i < len; i++) {
            // �q�k�V������
            for (int j = i; j > 0; j--) {
                if (result[j] > result[j - 1]) {
                    break;
                }
                swap(result[j], result[j - 1]);
            }
        }
    }
    static void countingSort(int* array, int* result, int len, int min, int max) {
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
    static void mergeSort(int* array, int* result, int len) {
        // backup
        int* tmp = new int[len];
        memcpy(tmp, array, len * sizeof(int));
        // Top-down
        int mid = len / 2;
        // left array 0~mid
        mergeSort_divide(array, result, mid);
        // right array mid+1~len
        mergeSort_divide(array + mid, result + mid, len - mid);
        // merge
        mergeSort_conquer(array, result, 0, mid, len);
        // return
        memcpy(array, tmp, len * sizeof(int));
        delete[] tmp;
    }
    static void selectionSort(int* array, int* result, int len) {
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
    static void quickSort(int* array, int* result, int len) {
        memcpy(result, array, len * sizeof(int));
        _quickSort(result, len);
    }
};

#endif