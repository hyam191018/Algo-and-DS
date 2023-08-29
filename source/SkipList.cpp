
#include "../include/skipList.h"
#include "../include/list.h"

int main() {
    SkipList skiplist;
    SinglyLinkedList list;
    const int operationTime = 100;

    cout << "# Inserting" << endl;
    for (int i = 0; i < operationTime; i++) {
        int num = rand() % operationTime;
        skiplist.insert(num);
        list.insert(num);
    }

    cout << "# Searching" << endl;
    for (int i = 0; i < operationTime / 2; i++) {
        int num = rand() % operationTime;
        if (bool(skiplist.search(num)) != list.search(num)) {
            cout << "Searching fail" << endl;
        }
    }

    cout << "# Removing" << endl;
    for (int i = 0; i < operationTime / 2; i++) {
        int num = rand() % operationTime;
        skiplist.remove(num);
        list.remove(num);
    }

    skiplist.show();
    cout << "----------------- cmp with linked list -------------- " << endl;
    list.sort();
    list.printAll();
}