#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
using namespace std;

enum Color { RED, BLACK };

class RBTreeNode {
  private:
    int num;
    RBTreeNode *parent, *left, *right;
    Color color; // true for red, false for black

  public:
    // for the other
    RBTreeNode(int num, RBTreeNode* parent, Color color)
        : num(num), parent(parent), left(nullptr), right(nullptr), color(color) {}
    // Getter
    int getNum(void) { return this->num; }
    Color getColor(void) { return this->color; }
    RBTreeNode* getParent(void) { return this->parent; }
    RBTreeNode* getLeft(void) { return this->left; }
    RBTreeNode* getRight(void) { return this->right; }
    // Setter
    void setNum(int num) { this->num = num; }
    void setColor(Color color) { this->color = color; }
    void setParent(RBTreeNode* node) { this->parent = node; }
    void setLeft(RBTreeNode* node) { this->left = node; }
    void setRight(RBTreeNode* node) { this->right = node; }
};

/**
 * 定義一個Red black tree
 * @param root 整棵樹的根結點
 * @param node_number 整棵樹的節點數
 * @fn printTree 印出每個節點儲存的數字
 * @fn printColor 印出每個節點的顏色(red or black)，用於檢驗
 * @fn inorderTraversal 按照中序輸出節點，由於left < parent <
 * right，故剛好是由小到大排列
 * @fn search 查詢一個數字是否存在
 * - @return true 存在
 * - @return false 不存在
 * @fn insert 插入一個數字到RB tree
 * @fn remove 將一個數字節點移除
 */
class RedBlackTree {
  private:
    RBTreeNode* root;
    RBTreeNode* NIL;
    int node_number;
    void printTree(RBTreeNode* node, string prefix, bool isLeft,
                   bool isNum /* ture for number, false for color*/);
    void inorderTraversal(RBTreeNode* node);
    RBTreeNode* findMin(RBTreeNode* node);   // 返回最小子節點
    bool isLeftChild(RBTreeNode* node);      // true，如果該node是其parent的left node
    RBTreeNode* findUncle(RBTreeNode* node); // 返回叔節點
    void insertFix(RBTreeNode* node);        // 重新調整平衡
    void removeFix(RBTreeNode* node);        // 重新調整平衡
    RBTreeNode* rightRotation(RBTreeNode* node);
    RBTreeNode* leftRotation(RBTreeNode* node);
    RBTreeNode* search(RBTreeNode* node, int num); // 返回目標節點位置，或是nullptr
    void insert(RBTreeNode* node, RBTreeNode* parent, int num); // root可能會改變，要從NIL重新抓
    void remove(RBTreeNode* node, RBTreeNode* parent, int num); // root可能會改變，要從NIL重新抓

  public:
    RedBlackTree(void) : root(nullptr), NIL(new RBTreeNode(0, nullptr, BLACK)), node_number(0) {}
    ~RedBlackTree(void) { delete NIL; }
    void printTree(void) { printTree(root, "", true, true); }
    void printColor(void) { printTree(root, "", true, false); }
    void inorderTraversal(void) { inorderTraversal(root); }
    bool search(int num) { return search(root, num); }
    void insert(int num) {
        insert(root, NIL, num);
        root = NIL->getLeft();
    }
    void remove(int num) {
        remove(root, NIL, num);
        root = NIL->getLeft();
    }
};

void RedBlackTree::printTree(RBTreeNode* node, string prefix = "", bool isLeft = true,
                             bool isNum = true) {
    if (!node) {
        return;
    }
    printTree(node->getRight(), prefix + (isLeft ? "│   " : "    "), false, isNum);
    cout << prefix;
    cout << (isLeft ? "└── " : "┌── ");
    cout << (isNum ? to_string(node->getNum()) : (node->getColor() == RED ? "R" : "B")) << endl;
    printTree(node->getLeft(), prefix + (isLeft ? "    " : "│   "), true, isNum);
}
void RedBlackTree::inorderTraversal(RBTreeNode* node) {
    if (!node) {
        return;
    }
    inorderTraversal(node->getLeft());
    cout << node->getNum() << " ";
    inorderTraversal(node->getRight());
}
inline RBTreeNode* RedBlackTree::findMin(RBTreeNode* node) {
    return node->getLeft() ? findMin(node->getLeft()) : node;
}
inline bool RedBlackTree::isLeftChild(RBTreeNode* node) {
    if (!node) {
        return false;
    } else if (node->getParent() == NIL) { // 因為定義root永遠是NIL的左子
        return true;
    }
    RBTreeNode* parent = node->getParent();
    if (node->getNum() >= parent->getNum()) { // node是右子(交換的時候可能會相同)
        return false;
    }
    return true;
}
inline RBTreeNode* RedBlackTree::findUncle(RBTreeNode* node) {
    if (!node || node->getParent() == NIL || (node->getParent())->getParent() == NIL) {
        return nullptr;
    }
    // 找出父親是祖父的左子還是右子
    RBTreeNode* parent = node->getParent();
    RBTreeNode* grandParent = parent->getParent();
    return isLeftChild(parent) ? grandParent->getRight() : grandParent->getLeft();
}
RBTreeNode* RedBlackTree::rightRotation(RBTreeNode* node) {
    // 先知道parent以及node是parent的左子還是右子
    RBTreeNode* parent = node->getParent();
    bool isLeft = isLeftChild(node);
    RBTreeNode* new_node = node->getLeft(); // 找尋新的節點
    new_node->setParent(parent);            // 建立新節點的關係
    isLeft ? parent->setLeft(new_node) : parent->setRight(new_node);
    if (new_node->getRight()) {
        (new_node->getRight())->setParent(node); // 新節點的右子變成舊節點的左子
    }
    node->setLeft(new_node->getRight());
    new_node->setRight(node); // 舊節點變成新節點的右子
    node->setParent(new_node);
    return new_node;
}
RBTreeNode* RedBlackTree::leftRotation(RBTreeNode* node) {
    // 先知道parent以及node是parent的左子還是右子
    RBTreeNode* parent = node->getParent();
    bool isLeft = isLeftChild(node);
    RBTreeNode* new_node = node->getRight(); // 找尋新的節點
    new_node->setParent(parent);             // 建立新節點的關係
    isLeft ? parent->setLeft(new_node) : parent->setRight(new_node);
    if (new_node->getLeft()) {
        (new_node->getLeft())->setParent(node); // 新節點的左子變成舊節點的右子
    }
    node->setRight(new_node->getLeft());
    new_node->setLeft(node); // 舊節點變成新節點的左子
    node->setParent(new_node);
    return new_node;
}
/**
 * 條件1 不可以連續紅色
 * 條件2 某node到leaf經過的黑色node數量相同
 * 條件3 根節點必是黑色
 * 條件4 所有leaf都是黑色
 */
void RedBlackTree::insertFix(RBTreeNode* node) {
    if (!node) {
        return;
    } else if (node->getParent() == NIL) { // 條件3
        node->setColor(BLACK);
        return;
    } else if ((node->getParent())->getColor() == BLACK) { // 滿足所有條件，不用做事
        return;
    }
    // 違反條件1
    RBTreeNode* parent = node->getParent();
    RBTreeNode* grandParent = parent->getParent();
    RBTreeNode* uncle = findUncle(node);
    if (!uncle || uncle->getColor() == BLACK) {
        // node相對於grandParent是LL、LR、RL、RR?
        if (isLeftChild(parent)) {
            if (isLeftChild(node)) { // LL
                // parent與grandParent先變色
                parent->setColor(parent->getColor() == RED ? BLACK : RED);
                grandParent->setColor(grandParent->getColor() == RED ? BLACK : RED);
                rightRotation(grandParent);
            } else { // LR
                // node與grandParent先變色
                node->setColor(node->getColor() == RED ? BLACK : RED);
                grandParent->setColor(grandParent->getColor() == RED ? BLACK : RED);
                leftRotation(parent);
                rightRotation(grandParent);
            }
        } else {
            if (isLeftChild(node)) { // RL
                // node與grandParent先變色
                node->setColor(node->getColor() == RED ? BLACK : RED);
                grandParent->setColor(grandParent->getColor() == RED ? BLACK : RED);
                rightRotation(parent);
                leftRotation(grandParent);
            } else { // RR
                // parent與grandParent先變色
                parent->setColor(parent->getColor() == RED ? BLACK : RED);
                grandParent->setColor(grandParent->getColor() == RED ? BLACK : RED);
                leftRotation(grandParent);
            }
        }
    } else {
        // parent、uncle、grandParent變色
        parent->setColor(parent->getColor() == RED ? BLACK : RED);
        grandParent->setColor(grandParent->getColor() == RED ? BLACK : RED);
        uncle->setColor(uncle->getColor() == RED ? BLACK : RED);
        // grandParent重新檢查
        insertFix(grandParent);
    }
}
void RedBlackTree::removeFix(RBTreeNode* node) {}
RBTreeNode* RedBlackTree::search(RBTreeNode* node, int num) {
    if (!node) {
        return nullptr;
    }
    if (num > node->getNum()) {
        return search(node->getLeft(), num);
    } else if (num < node->getNum()) {
        return search(node->getRight(), num);
    }
    return node;
}

void RedBlackTree::insert(RBTreeNode* node, RBTreeNode* parent, int num) {
    if (!node) {
        // 建立一個新的節點
        node_number++;
        RBTreeNode* new_node = new RBTreeNode(num, parent, parent == NIL ? BLACK : RED);
        // parent認child
        isLeftChild(new_node) ? parent->setLeft(new_node) : parent->setRight(new_node);
        insertFix(new_node); // 檢查是否需要平衡
        return;
    }
    if (num > node->getNum()) {
        insert(node->getRight(), node, num); // 往右子樹丟
    } else if (num < node->getNum()) {
        insert(node->getLeft(), node, num); // 往左子樹丟
    }
}
void RedBlackTree::remove(RBTreeNode* node, RBTreeNode* parent, int num) {
    if (!node) {
        return;
    }
    if (num > node->getNum()) {
        remove(node->getRight(), node, num); // 往右子樹丟
        return;
    } else if (num < node->getNum()) {
        remove(node->getLeft(), node, num); // 往左子樹丟
        return;
    }
    // 刪除node，且尋找新的node替補
    RBTreeNode* new_node = nullptr;
    if (node->getRight()) {
        if (node->getLeft()) {                    // 有兩個子節點
            new_node = findMin(node->getRight()); // 找替代節點(右子樹最小或是左子樹最大)
            node->setColor(new_node->getColor()); // 偷取新節點的資訊(假交換)
            node->setNum(new_node->getNum());
            remove(node->getRight(), node, new_node->getNum()); // 移除新節點
            return;
        } else { // 只有右節點，直接補上
            new_node = node->getRight();
            new_node->setParent(parent); // 建立新節點關係
            isLeftChild(node) ? parent->setLeft(new_node) : parent->setRight(new_node);
        }
    } else if (node->getLeft()) { // 只有左節點，直接補上
        new_node = node->getLeft();
        new_node->setParent(parent); // 建立新節點關係
        isLeftChild(node) ? parent->setLeft(new_node) : parent->setRight(new_node);
    } else { // 沒有子節點，那其parent要把該node遺棄
        isLeftChild(node) ? parent->setLeft(new_node) : parent->setRight(new_node);
    }
    node_number--;
    delete node;
}

#endif