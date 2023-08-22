#include "../include/array.h"
#include "../include/timer.h"

int main(void) {
    Array array(10, -20, 20);

    cout << "<< Functional Testing >>" << endl << endl;

    cout << "# Testing bubble sort" << endl;
    cout << "Before sort: ";
    array.showArray();
    array.bubbleSort();
    cout << "After sort:  ";
    array.showResult();
    cout << endl;

    cout << "# Testing insertion sort" << endl;
    cout << "Before sort: ";
    array.showArray();
    array.insertionSort();
    cout << "After sort:  ";
    array.showResult();
    cout << endl;

    cout << "# Testing counting sort" << endl;
    cout << "Before sort: ";
    array.showArray();
    array.countingSort();
    cout << "After sort:  ";
    array.showResult();
    cout << endl;

    cout << "# Testing merge sort" << endl;
    cout << "Before sort: ";
    array.showArray();
    array.mergeSort();
    cout << "After sort:  ";
    array.showResult();
    cout << endl;

    cout << "# Testing selection sort" << endl;
    cout << "Before sort: ";
    array.showArray();
    array.selectionSort();
    cout << "After sort:  ";
    array.showResult();
    cout << endl;

    cout << "# Testing quick sort" << endl;
    cout << "Before sort: ";
    array.showArray();
    array.quickSort();
    cout << "After sort:  ";
    array.showResult();
    cout << endl;

    cout << "<< Stress Testing >>" << endl << endl;
    Array array2(10000, -10000, 10000);

    cout << "# Testing bubble sort" << endl;
    auto time = timerStart();
    array2.bubbleSort();
    timerEnd(time);
    cout << endl;

    cout << "# Testing insertion sort" << endl;
    time = timerStart();
    array2.insertionSort();
    timerEnd(time);
    cout << endl;

    cout << "# Testing counting sort" << endl;
    time = timerStart();
    array2.countingSort();
    timerEnd(time);
    cout << endl;

    cout << "# Testing merge sort" << endl;
    time = timerStart();
    array2.mergeSort();
    timerEnd(time);
    cout << endl;

    cout << "# Testing selection sort" << endl;
    time = timerStart();
    array2.selectionSort();
    timerEnd(time);
    cout << endl;

    cout << "# Testing quick sort" << endl;
    time = timerStart();
    array2.quickSort();
    timerEnd(time);
    cout << endl;
}