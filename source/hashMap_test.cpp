#include "../include/hashMap.h"
#include <ctime> // for time
#include <iostream>
using namespace std;

int main() {
    srand(time(nullptr));

    HashMap map(30);
    const int round = 10;
    cout << "<< Testing Hash map >>" << endl << endl;

    cout << endl << "# Inserting" << endl;
    for (int i = 0; i < round; i++) {
        string key = "key_" + to_string(rand() % round);
        int value = rand() % 100;
        if (map.insert(key, value)) {
            cout << "Insert "
                 << "(" << key << ", " << value << ")" << endl;
        }
    }

    cout << endl << "# Searching" << endl;
    int value;
    for (int i = 0; i < round; i++) {
        string key = "key_" + to_string(i);
        if (map.search(key, value)) {
            cout << "Value for key '" << key << "' in map: " << value << endl;
        }
    }

    cout << endl << "# Removing" << endl;
    for (int i = 0; i < round / 2; i++) {
        string key = "key_" + to_string(rand() % round);
        if (map.remove(key)) {
            cout << "Remove " << key << endl;
        }
    }

    cout << endl << "# Show mapping" << endl;
    map.showMap();
    // ²MªÅ HashMap
    map.clear();
    map.showMap();

    return 0;
}