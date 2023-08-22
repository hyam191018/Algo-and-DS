#ifndef HASH_H
#define HASH_H

#include <iostream>
using namespace std;

int hashFunction(string key, int mod) {
    int hash = 0;
    for (char c : key) {
        hash += static_cast<int>(c);
    }
    return hash % mod;
}

class HashNode {
  public:
    string key;
    int value;
    bool used;
    HashNode(void) : key(""), value(0), used(false) {}
    bool isUsed(void) { return used; }
};

/**
 * 建立一個基本的key value structure
 * @param - 陣列的長度，即最多可存放幾個元素
 * @fn search
 * - @param key 欲查詢的key
 * - @param value 查找到的value
 * - @return true 成功查找到
 * - @return false 不存在
 * @fn insert
 * - @param key 新增的key
 * - @param value 新增的key
 * - @return true 成功插入
 * - @return false 重複，或是array已滿
 * @fn remove
 * - @param key - 欲刪除的key
 * - @return true 成功刪除
 * - @return false 不存在
 * @fn clear - 清除所有key value
 * @fn showMap - 列出已儲存的key value
 */
class HashMap {
  private:
    HashNode* array;
    int array_len;

  public:
    HashMap(void) {
        array = new HashNode[10];
        array_len = 10;
    }
    HashMap(int len) {
        array = new HashNode[len];
        array_len = len;
    }
    ~HashMap(void) { delete[] array; }
    void showMap(void) {
        for (int i = 0; i < array_len; i++) {
            if (!array[i].isUsed())
                continue;
            cout << "key: " << array[i].key << ", value: " << array[i].value << endl;
        }
    }
    bool insert(string key, int value) {
        int h = hashFunction(key, array_len);
        for (int i = 0; i < array_len; i++) {
            int point = (h + i) % array_len;

            if (array[point].isUsed()) {
                if (!array[point].key.compare(key)) { // update
                    array[point].value = value;
                    return true;
                } else { // collision
                    continue;
                }
            } else { // insert
                array[point].key = key;
                array[point].value = value;
                array[point].used = true;
                return true;
            }
        }
        return false;
    }
    bool search(string key, int& value) {
        int h = hashFunction(key, array_len);
        for (int i = 0; i < array_len; i++) {
            int point = (h + i) % array_len;

            if (array[point].isUsed()) {
                if (!array[point].key.compare(key)) { // find
                    value = array[point].value;
                    return true;
                } else { // collision
                    continue;
                }
            } else {
                break;
            }
        }
        return false;
    }
    bool remove(string key) {
        int h = hashFunction(key, array_len);
        for (int i = 0; i < array_len; i++) {
            int point = (h + i) % array_len;

            if (array[point].isUsed()) {
                if (!array[point].key.compare(key)) { // find and then remove
                    array[point].key = "";
                    array[point].value = 0;
                    array[point].used = false;
                    return true;
                } else { // collision
                    continue;
                }
            } else {
                break;
            }
        }
        return false;
    }
    void clear(void) {
        for (int i = 0; i < array_len; i++) {
            array[i].key = "";
            array[i].value = 0;
            array[i].used = false;
        }
    }
};

#endif
