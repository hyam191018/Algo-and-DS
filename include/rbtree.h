#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
using namespace std;

/**
 * 之前寫了BST與AVL tree，但總感覺沒有寫得很好，故在此重新為RB tree寫一個新的類別
 */
class RBTreeNode {
  private:
    int num;
    RBTreeNode *parent, *left, *right;
    bool color; // true for red, false for black

  public:
    RBTreeNode(void) : num(0), parent(nullptr), left(nullptr), right(nullptr), color(true) {}
    // for root
    RBTreeNode(int num) : num(num), parent(nullptr), left(nullptr), right(nullptr), color(false) {}
    // for the other
    RBTreeNode(int num, RBTreeNode* parent)
        : num(num), parent(parent), left(nullptr), right(nullptr), color(true) {}
    // Getter
    int getNum(void) { return num; }
    bool isRed(void) { return this->color; }
    RBTreeNode* getParent(void) { return parent; }
    RBTreeNode* getLeft(void) { return left; }
    RBTreeNode* getRight(void) { return right; }
    // Setter
    void setNum(int num) { this->num = num; }
    void setRed(bool isRed) { this->color = isRed; }
    void setParent(RBTreeNode* node) { parent = node; }
    void setLeft(RBTreeNode* node) { left = node; }
    void setRight(RBTreeNode* node) { right = node; }
};

/**
 * 定義一個Red black tree
 * @param root 整棵樹的根結點
 * @param node_number 整棵樹的節點數
 * @fn printTree 印出每個節點儲存的數字
 * @fn printColor 印出每個節點的顏色(red or black)，用於檢驗
 * @fn inorderTraversal 按照中序輸出節點，由於left < parent < right，故剛好是由小到大排列
 * @fn search 查詢一個數字是否存在
 * - @return true 存在
 * - @return false 不存在
 * @fn insert 插入一個數字到RB tree
 * @fn remove 將一個數字節點移除
 */
class RedBlackTree {
  private:
    RBTreeNode* root;
    int node_number;
    void printTree(RBTreeNode* node, string prefix, bool isLeft,
                   bool isNum /* ture for number, false for color*/);
    void inorderTraversal(RBTreeNode* node);
    RBTreeNode* search(RBTreeNode* node, int num); // 返回目標節點位置，或是nullptrt
    RBTreeNode* insert(RBTreeNode* node, RBTreeNode* parent, int num); // 返回新的subtree root
    RBTreeNode* remove(RBTreeNode* node, int num);                     // 返回新的subtree root

  public:
    RedBlackTree(void) : root(nullptr), node_number(0) {}
    void printTree(void) { printTree(root, "", true, true); }
    void printColor(void) { printTree(root, "", true, false); }
    void inorderTraversal(void) { inorderTraversal(root); }
    bool search(int num) { return search(root, num); }
    void insert(int num) { root = insert(root, nullptr, num); }
    void remove(int num) { root = remove(root, num); }
};

void RedBlackTree::printTree(RBTreeNode* node, string prefix = "", bool isLeft = true,
                             bool isNum = true) {
    if (!node) {
        return;
    }
    printTree(node->getRight(), prefix + (isLeft ? "│   " : "    "), false, isNum);
    cout << prefix;
    cout << (isLeft ? "└── " : "┌── ");
    cout << (isNum ? to_string(node->getNum()) : (node->isRed() ? "R" : "B")) << endl;
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
RBTreeNode* RedBlackTree::insert(RBTreeNode* node, RBTreeNode* parent, int num) {
    if (!node) {
        // 沒有節點就建立一個新的節點，若沒有parent代表該新節點為root
        return parent ? new RBTreeNode(num, parent) : new RBTreeNode(num);
    }
    if (num > node->getNum()) {
        // 往右子樹丟
        node->setRight(insert(node->getRight(), node, num));
    } else if (num < node->getNum()) {
        // 往左子樹丟
        node->setLeft(insert(node->getLeft(), node, num));
    }
    // 相等代表重複
    return node;
}
RBTreeNode* RedBlackTree::remove(RBTreeNode* node, int num) { return nullptr; }

#endif