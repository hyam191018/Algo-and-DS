#include "item.h"
#include "timer.h"

int main(void) {
    Item item(100, -100000, 100000);

    auto timer = timer_start();
    item.bubble_sort();
    item.show_result();
    timer_end(timer);

    timer = timer_start();
    item.merge_sort();
    item.show_result();
    timer_end(timer);
}