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
 * �إߤ@�Ӱ򥻪�key value structure
 * @param - �}�C�����סA�Y�̦h�i�s��X�Ӥ���
 * @fn search
 * - @param key ���d�ߪ�key
 * - @param value �d��쪺value
 * - @return true ���\�d���
 * - @return false ���s�b
 * @fn insert
 * - @param key �s�W��key
 * - @param value �s�W��key
 * - @return true ���\���J
 * - @return false ���ơA�άOarray�w��
 * @fn remove
 * - @param key - ���R����key
 * - @return true ���\�R��
 * - @return false ���s�b
 * @fn clear - �M���Ҧ�key value
 * @fn showMap - �C�X�w�x�s��key value
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
