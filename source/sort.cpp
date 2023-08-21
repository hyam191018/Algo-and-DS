#include "../include/sort.h"
#include "../include/timer.h"

int main(void) {
    Item item(10, -20, 20);

    cout << "<< 正向測試 >>" << endl << endl;

    cout << "# Testing bubble sort" << endl;
    cout << "Before sort: ";
    item.show_array();
    item.bubble_sort();
    cout << "After sort:  ";
    item.show_result();
    cout << endl;

    cout << "# Testing insertion sort" << endl;
    cout << "Before sort: ";
    item.show_array();
    item.insertion_sort();
    cout << "After sort:  ";
    item.show_result();
    cout << endl;

    cout << "# Testing counting sort" << endl;
    cout << "Before sort: ";
    item.show_array();
    item.counting_sort();
    cout << "After sort:  ";
    item.show_result();
    cout << endl;

    cout << "# Testing merge sort" << endl;
    cout << "Before sort: ";
    item.show_array();
    item.merge_sort();
    cout << "After sort:  ";
    item.show_result();
    cout << endl;

    cout << "# Testing selection sort" << endl;
    cout << "Before sort: ";
    item.show_array();
    item.selection_sort();
    cout << "After sort:  ";
    item.show_result();
    cout << endl;

    cout << "# Testing quick sort" << endl;
    cout << "Before sort: ";
    item.show_array();
    item.quick_sort();
    cout << "After sort:  ";
    item.show_result();
    cout << endl;

    cout << "<< 時間測試 >>" << endl << endl;
    Item item2(10000, -10000, 10000);

    cout << "# Testing bubble sort" << endl;
    auto time = timer_start();
    item2.bubble_sort();
    timer_end(time);
    cout << endl;

    cout << "# Testing insertion sort" << endl;
    time = timer_start();
    item2.insertion_sort();
    timer_end(time);
    cout << endl;

    cout << "# Testing counting sort" << endl;
    time = timer_start();
    item2.counting_sort();
    timer_end(time);
    cout << endl;

    cout << "# Testing merge sort" << endl;
    time = timer_start();
    item2.merge_sort();
    timer_end(time);
    cout << endl;

    cout << "# Testing selection sort" << endl;
    time = timer_start();
    item2.selection_sort();
    timer_end(time);
    cout << endl;

    cout << "# Testing quick sort" << endl;
    time = timer_start();
    item2.quick_sort();
    timer_end(time);
    cout << endl;
}