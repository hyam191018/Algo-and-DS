#include "../include/sort.h"
#include "../include/timer.h"

void sorting_test(void) {
    Item item(10, -200, 200);

    auto timer = timer_start();

    timer = timer_start();
    cout << "Before bubble sort:   ";
    item.show_array();
    item.bubble_sort();
    cout << "After bubble sort:    ";
    item.show_result();
    timer_end(timer);

    timer = timer_start();
    cout << "Before insertion sor: ";
    item.show_array();
    item.insertion_sort();
    cout << "After insertion sort: ";
    item.show_result();
    timer_end(timer);

    timer = timer_start();
    cout << "Before counting sort: ";
    item.show_array();
    item.counting_sort();
    cout << "After counting sort:  ";
    item.show_result();
    timer_end(timer);

    timer = timer_start();
    cout << "Before merge sort:    ";
    item.show_array();
    item.merge_sort();
    cout << "After merge sort:     ";
    item.show_result();
    timer_end(timer);

    timer = timer_start();
    cout << "Before selection sort:";
    item.show_array();
    item.selection_sort();
    cout << "After selection sort: ";
    item.show_result();
    timer_end(timer);

    timer = timer_start();
    cout << "Before quick sort:    ";
    item.show_array();
    item.quick_sort();
    cout << "After quick sort:     ";
    item.show_result();
    timer_end(timer);
}

int main(void) { sorting_test(); }