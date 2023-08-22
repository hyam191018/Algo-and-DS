#include "../include/array.h"
#include "../include/sort.h"
#include "../include/timer.h"

int main(void) {
    Array array(10, -20, 20);

    cout << "<< Functional Testing >>" << endl << endl;

    cout << "# Testing bubble sort" << endl;
    cout << "Before sort: ";
    array.showArray();
    Sorting::bubbleSort(array.origin, array.result, array.len);
    cout << "After sort:  ";
    array.showResult();
    cout << endl;

    cout << "# Testing insertion sort" << endl;
    cout << "Before sort: ";
    array.showArray();
    Sorting::insertionSort(array.origin, array.result, array.len);
    cout << "After sort:  ";
    array.showResult();
    cout << endl;

    cout << "# Testing counting sort" << endl;
    cout << "Before sort: ";
    array.showArray();
    Sorting::countingSort(array.origin, array.result, array.len, array.min, array.max);
    cout << "After sort:  ";
    array.showResult();
    cout << endl;

    cout << "# Testing merge sort" << endl;
    cout << "Before sort: ";
    array.showArray();
    Sorting::mergeSort(array.origin, array.result, array.len);
    cout << "After sort:  ";
    array.showResult();
    cout << endl;

    cout << "# Testing selection sort" << endl;
    cout << "Before sort: ";
    array.showArray();
    Sorting::selectionSort(array.origin, array.result, array.len);
    cout << "After sort:  ";
    array.showResult();
    cout << endl;

    cout << "# Testing quick sort" << endl;
    cout << "Before sort: ";
    array.showArray();
    Sorting::quickSort(array.origin, array.result, array.len);
    cout << "After sort:  ";
    array.showResult();
    cout << endl;

    cout << "<< Stress Testing >>" << endl << endl;
    Array array2(10000, -10000, 10000);

    cout << "# Testing bubble sort" << endl;
    auto time = timerStart();
    Sorting::bubbleSort(array2.origin, array2.result, array2.len);
    timerEnd(time);
    cout << endl;

    cout << "# Testing insertion sort" << endl;
    time = timerStart();
    Sorting::insertionSort(array2.origin, array2.result, array2.len);
    timerEnd(time);
    cout << endl;

    cout << "# Testing counting sort" << endl;
    time = timerStart();
    Sorting::countingSort(array2.origin, array2.result, array2.len, array2.min, array2.max);
    timerEnd(time);
    cout << endl;

    cout << "# Testing merge sort" << endl;
    time = timerStart();
    Sorting::mergeSort(array2.origin, array2.result, array2.len);
    timerEnd(time);
    cout << endl;

    cout << "# Testing selection sort" << endl;
    time = timerStart();
    Sorting::selectionSort(array2.origin, array2.result, array2.len);
    timerEnd(time);
    cout << endl;

    cout << "# Testing quick sort" << endl;
    time = timerStart();
    Sorting::quickSort(array2.origin, array2.result, array2.len);
    timerEnd(time);
    cout << endl;
}