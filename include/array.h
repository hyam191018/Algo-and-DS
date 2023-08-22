#ifndef ARRAY_H
#define ARRAY_H

#include "time.h"   // for time
#include <iostream> // for swap
using namespace std;

/**
 * �إ� Array�A�i�ϥΥH�Ufunction
 * @param �}�C���סB(�̤p�ȡB�̤j��)
 * @fn showArray - �C�X����ͦ����}�C(origin)
 * @fn showResult - �C�X�ק�᪺�}�C(result)
 */
class Array {
  private:
    void assign(void) {
        for (int i = 0; i < len; i++) {
            origin[i] = result[i] = rand() % (max - min + 1) + min;
        }
    }

  public:
    int* origin;
    int* result;
    unsigned len;
    int min;
    int max;
    Array(void) : len(10), min(-10), max(10) {
        srand(time(NULL));
        origin = new int[len];
        result = new int[len];
        assign();
    }
    Array(int len) : len(len), min(0), max(100) {
        srand(time(NULL));
        origin = new int[len];
        result = new int[len];
        assign();
    }
    Array(int len, int min, int max) : len(len), min(min), max(max) {
        srand(time(NULL));
        if (this->min > this->max) {
            cout << "Error: minimum is bigger than maximum. (so I swapped them)" << endl;
            swap(this->min, this->max);
        }
        origin = new int[len];
        result = new int[len];
        assign();
    }
    ~Array(void) {
        delete[] origin;
        delete[] result;
    }
    void showArray(void) {
        for (int i = 0; i < len; i++) {
            cout << origin[i] << " ";
        }
        cout << endl;
    }
    void showResult(void) {
        for (int i = 0; i < len; i++) {
            cout << result[i] << " ";
        }
        cout << endl;
    }
};

#endif