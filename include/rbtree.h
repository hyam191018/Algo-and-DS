#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
using namespace std;

/**
 * ���e�g�FBST�PAVL tree�A���`�Pı�S���g�o�ܦn�A�G�b�����s��RB tree�g�@�ӷs�����O
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
 * �w�q�@��Red black tree
 * @param root ��ʾ𪺮ڵ��I
 * @param node_number ��ʾ𪺸`�I��
 * @fn printTree �L�X�C�Ӹ`�I�x�s���Ʀr
 * @fn printColor �L�X�C�Ӹ`�I���C��(red or black)�A�Ω�����
 * @fn inorderTraversal ���Ӥ��ǿ�X�`�I�A�ѩ�left < parent < right�A�G��n�O�Ѥp��j�ƦC
 * @fn search �d�ߤ@�ӼƦr�O�_�s�b
 * - @return true �s�b
 * - @return false ���s�b
 * @fn insert ���J�@�ӼƦr��RB tree
 * @fn remove �N�@�ӼƦr�`�I����
 */
class RBTree {
  private:
    RBTreeNode* root;
    int node_number;
    void printTree(RBTreeNode* node, string prefix = "", bool isLeft = true,
                   bool isNum = true /* ture for number, false for color*/);
    void inorderTraversal(RBTreeNode* node);
    RBTreeNode* search(RBTreeNode* node, int num); // ��^�ؼи`�I��m�A�άOnullptrt
    RBTreeNode* insert(RBTreeNode* node, int num); // ��^�s��subtree root
    RBTreeNode* remove(RBTreeNode* node, int num); // ��^�s��subtree root

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
    printTree(node->getRight(), prefix + (isLeft ? "�x   " : "    "), false, isNum);
    cout << prefix;
    cout << (isLeft ? "�|�w�w " : "�z�w�w ");
    cout << node->getNum() << endl;
    printTree(node->getLeft(), prefix + (isLeft ? "    " : "�x   "), true, isNum);
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