#include "../include/sort.h"
#include "../include/timer.h"

int main(void) {
    Array array(10, -20, 20);

    cout << "<< Functional Testing >>" << endl << endl;

    cout << "# Testing bubble sort" << endl;
    cout << "Before sort: ";
    array.show_array();
    array.bubble_sort();
    cout << "After sort:  ";
    array.show_result();
    cout << endl;

    cout << "# Testing insertion sort" << endl;
    cout << "Before sort: ";
    array.show_array();
    array.insertion_sort();
    cout << "After sort:  ";
    array.show_result();
    cout << endl;

    cout << "# Testing counting sort" << endl;
    cout << "Before sort: ";
    array.show_array();
    array.counting_sort();
    cout << "After sort:  ";
    array.show_result();
    cout << endl;

    cout << "# Testing merge sort" << endl;
    cout << "Before sort: ";
    array.show_array();
    array.merge_sort();
    cout << "After sort:  ";
    array.show_result();
    cout << endl;

    cout << "# Testing selection sort" << endl;
    cout << "Before sort: ";
    array.show_array();
    array.selection_sort();
    cout << "After sort:  ";
    array.show_result();
    cout << endl;

    cout << "# Testing quick sort" << endl;
    cout << "Before sort: ";
    array.show_array();
    array.quick_sort();
    cout << "After sort:  ";
    array.show_result();
    cout << endl;

    cout << "<< Stress Testing >>" << endl << endl;
    Array array2(10000, -10000, 10000);

    cout << "# Testing bubble sort" << endl;
    auto time = timer_start();
    array2.bubble_sort();
    timer_end(time);
    cout << endl;

    cout << "# Testing insertion sort" << endl;
    time = timer_start();
    array2.insertion_sort();
    timer_end(time);
    cout << endl;

    cout << "# Testing counting sort" << endl;
    time = timer_start();
    array2.counting_sort();
    timer_end(time);
    cout << endl;

    cout << "# Testing merge sort" << endl;
    time = timer_start();
    array2.merge_sort();
    timer_end(time);
    cout << endl;

    cout << "# Testing selection sort" << endl;
    time = timer_start();
    array2.selection_sort();
    timer_end(time);
    cout << endl;

    cout << "# Testing quick sort" << endl;
    time = timer_start();
    array2.quick_sort();
    timer_end(time);
    cout << endl;
}