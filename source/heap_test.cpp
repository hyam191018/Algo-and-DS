
#include "../include/heap.h"

#include <iostream>
using namespace std;

int main() {
    srand(time(nullptr));

    cout << "<< Testing Max heap >>" << endl << endl;
    MaxHeap maxheap(10);
    const int round = 30;

    cout << "# Inserting" << endl;
    for (int i = 0; i < round; i++) {
        int num = rand() % round;
        maxheap.insert(num);
    }

    maxheap.showHeap();
    cout << endl;

    cout << "# Removing" << endl;
    for (int i = 0; i < 10; i++) {
        if (maxheap.findMax() != NOT_FOUND) {
            cout << "Remove " << maxheap.findMax() << endl;
            maxheap.remove();
        }
    }

    cout << endl;
    cout << "<< Testing Min heap >>" << endl << endl;
    MinHeap minheap(10);

    cout << "# Inserting" << endl;
    for (int i = 0; i < round; i++) {
        int num = rand() % round;
        minheap.insert(num);
    }

    minheap.showHeap();
    cout << endl;

    cout << "# Removing" << endl;
    for (int i = 0; i < 10; i++) {
        if (minheap.findMin() != NOT_FOUND) {
            cout << "Remove " << minheap.findMin() << endl;
            minheap.remove();
        }
    }
}