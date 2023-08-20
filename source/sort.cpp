#include "../include/sort.h"
#include "../include/timer.h"

int main(void) {
    Item item(10, -200, 200);

    auto timer = timer_start();

    cout << "<< Testing bubble sort >>" << endl;
    timer = timer_start();
    cout << "Before sort: ";
    item.show_array();
    item.bubble_sort();
    cout << "After sort:  ";
    item.show_result();
    timer_end(timer);

    cout << "<< Testing insertion sort >>" << endl;
    timer = timer_start();
    cout << "Before sort: ";
    item.show_array();
    item.insertion_sort();
    cout << "After sort:  ";
    item.show_result();
    timer_end(timer);

    cout << "<< Testing counting sort >>" << endl;
    timer = timer_start();
    cout << "Before sort: ";
    item.show_array();
    item.counting_sort();
    cout << "After sort:  ";
    item.show_result();
    timer_end(timer);

    cout << "<< Testing merge sort >>" << endl;
    timer = timer_start();
    cout << "Before sort: ";
    item.show_array();
    item.merge_sort();
    cout << "After sort:  ";
    item.show_result();
    timer_end(timer);

    cout << "<< Testing selection sort >>" << endl;
    timer = timer_start();
    cout << "Before sort: ";
    item.show_array();
    item.selection_sort();
    cout << "After sort:  ";
    item.show_result();
    timer_end(timer);

    cout << "<< Testing quick sort >>" << endl;
    timer = timer_start();
    cout << "Before sort: ";
    item.show_array();
    item.quick_sort();
    cout << "After sort:  ";
    item.show_result();
    timer_end(timer);
}