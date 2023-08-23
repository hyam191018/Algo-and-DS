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
    RBTreeNode(int num) : num(num), parent(nullptr), left(nullptr), right(nullptr), color(true) {}
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
class RBTree {
  private:
    RBTreeNode* root;
    int node_number;
    void printTree(RBTreeNode* node, string prefix = "", bool isLeft = true,
                   bool isNum = true /* ture for number, false for color*/);
    void inorderTraversal(RBTreeNode* node);
    RBTreeNode* search(RBTreeNode* node, int num); // 返回目標節點位置，或是nullptrt
    RBTreeNode* insert(RBTreeNode* node, int num); // 返回新的subtree root
    RBTreeNode* remove(RBTreeNode* node, int num); // 返回新的subtree root

  public:
    RBTree(void) : root(nullptr), node_number(0) {}
    void printTree(void) { printTree(root, "", true, true); }
    void printColor(void) { printTree(root, "", true, false); }
    void inorderTraversal(void) { inorderTraversal(root); }
    bool search(int num) { return search(root, num); }
    void insert(int num) { root = insert(root, num); }
    void remove(int num) { root = remove(root, num); }
};

void RBTree::printTree(RBTreeNode* node, string prefix = "", bool isLeft = true, bool isNum) {
    if (!node) {
        return;
    }
    printTree(node->getRight(), prefix + (isLeft ? "│   " : "    "), false, isNum);
    cout << prefix;
    cout << (isLeft ? "└── " : "┌── ");
    cout << node->getNum() << endl;
    printTree(node->getLeft(), prefix + (isLeft ? "    " : "│   "), true, isNum);
}
void RBTree::inorderTraversal(RBTreeNode* node) {
    if (!node)
        return;
    inorderTraversal(node->getLeft());
    cout << node->getNum() << " ";
    inorderTraversal(node->getRight());
}

RBTreeNode* RBTree::search(RBTreeNode* node, int num) { return nullptr; }
RBTreeNode* RBTree::insert(RBTreeNode* node, int num) { return nullptr; }
RBTreeNode* RBTree::remove(RBTreeNode* node, int num) { return nullptr; }

#endif