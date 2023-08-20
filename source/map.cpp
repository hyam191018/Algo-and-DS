#include "../include/list.h"
#include <cstdlib> // 為 rand() 和 srand()
#include <ctime>   // 為 time()
#include <iostream>
#include <string>

using namespace std;

int main() {
    srand(time(NULL)); // 初始化隨機種子

    // 創建 HashMap 實例
    HashMap hashMap1(10);
    HashMap hashMap2(20);

    // 插入鍵值對
    for (int i = 0; i < 10000; i++) {
        string key = "key_" + to_string(i);
        int value = rand() % 100;
        hashMap1.insert(key, value);
        hashMap2.insert(key, value);
    }

    // 查找鍵對應的值
    int value;
    for (int i = 0; i < 5000; i++) {
        string key = "key_" + to_string(rand() % 10000);
        if (hashMap1.lookup(key, value)) {
            cout << "Value for key '" << key << "' in hashMap1: " << value << endl;
        }
        if (hashMap2.lookup(key, value)) {
            cout << "Value for key '" << key << "' in hashMap2: " << value << endl;
        }
    }

    // 刪除鍵值對
    for (int i = 0; i < 2000; i++) {
        string key = "key_" + to_string(rand() % 10000);
        hashMap1.remove(key);
        hashMap2.remove(key);
    }

    // 清空 HashMap
    hashMap1.clear();
    hashMap2.clear();

    return 0;
}