#include "../include/list.h"
#include <cstdlib> // �� rand() �M srand()
#include <ctime>   // �� time()
#include <iostream>
#include <string>

using namespace std;

int main() {
    srand(time(nullptr)); // ��l���H���ؤl

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
    // �M�� HashMap
    map.clear();

    return 0;
}