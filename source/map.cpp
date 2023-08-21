#include "../include/list.h"
#include <cstdlib> // 為 rand() 和 srand()
#include <ctime>   // 為 time()
#include <iostream>
#include <string>

using namespace std;

int main() {
    srand(time(nullptr)); // 初始化隨機種子

    HashMap map(30);

    cout << "<< Testing Hash map >>" << endl;
    for (int i = 0; i < 5; i++) {
        string key = "key_" + to_string(rand() % 10);
        int value = rand() % 100;
        if (map.insert(key, value)) {
            cout << "Insert "
                 << "(" << key << ", " << value << ")" << endl;
        }
    }

    int value;
    for (int i = 0; i < 10; i++) {
        string key = "key_" + to_string(i);
        if (map.lookup(key, value)) {
            cout << "Value for key '" << key << "' in map: " << value << endl;
        }
    }

    for (int i = 0; i < 5; i++) {
        string key = "key_" + to_string(rand() % 10);
        if (map.remove(key)) {
            cout << "Remove " << key << endl;
        }
    }

    map.showMap();
    // 清空 HashMap
    map.clear();

    return 0;
}