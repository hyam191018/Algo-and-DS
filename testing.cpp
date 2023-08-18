#include "item.h"

int main(void) {
    Item item3(5, -1, -10);
    item3.show();
    item3.bubble_sort();
    item3.counting_sort();
    item3.insertion_sort();
    item3.quick_sort();
    item3.show();
}