#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <iostream>
using namespace std;

#ifndef CHILD_TYPE
#define CHILD_TYPE
enum ChildType { LEFT_CHILD, RIGHT_CHILD, NO_PARENT };
#endif

class SplayTreeNode {
  private:
    int num;
    SplayTreeNode *parent, *left, *right;

  public:
    SplayTreeNode(int num, SplayTreeNode* parent, SplayTreeNode* left, SplayTreeNode* right)
        : num(num), parent(parent), left(left), right(right) {}
    // Getter
    int getNum(void) { return this->num; }
    SplayTreeNode* getParent(void) { return this->parent; }
    SplayTreeNode* getLeft(void) { return this->left; }
    SplayTreeNode* getRight(void) { return this->right; }
    // Setter
    void setNum(int num) { this->num = num; }
    void setParent(SplayTreeNode* node) { this->parent = node; }
    void setLeft(SplayTreeNode* node) { this->left = node; }
    void setRight(SplayTreeNode* node) { this->right = node; }
};

class SplayTree {
  private:
    SplayTreeNode* root;
    void printTree(SplayTreeNode* node, string prefix, bool isLeft);
    void inorderTraversal(SplayTreeNode* node);
    ChildType getChildType(SplayTreeNode* node); // 返回該node是其parent的Left還是Right child
    SplayTreeNode* findMin(SplayTreeNode* node); // 返回 最小子節點
    SplayTreeNode* rightRotation(SplayTreeNode* node);
    SplayTreeNode* leftRotation(SplayTreeNode* node);
    SplayTreeNode* moveToRoot(SplayTreeNode* node);      // 返回新的root
    SplayTreeNode* search(SplayTreeNode* node, int num); // 返回目標node
    void insert(SplayTreeNode* node, SplayTreeNode* parent, int num);
    void remove(SplayTreeNode* node, int num);

  public:
    SplayTree(void) { root = nullptr; }
    ~SplayTree(void) { delete root; }
    void printTree(void) { printTree(root, "", true); }
    void inorderTraversal(void) { inorderTraversal(root); }
    bool search(int num) { return search(root, num); }
    void insert(int num) { insert(root, nullptr, num); }
    void remove(int num) { remove(root, num); }
};

void SplayTree::printTree(SplayTreeNode* node, string prefix = "", bool isLeft = true) {
    if (!node) {
        return;
    }
    printTree(node->getRight(), prefix + (isLeft ? "│   " : "    "), false);
    cout << prefix;
    cout << (isLeft ? "└── " : "┌── ");
    cout << node->getNum() << endl;
    printTree(node->getLeft(), prefix + (isLeft ? "    " : "│   "), true);
}

void SplayTree::inorderTraversal(SplayTreeNode* node) {
    if (!node) {
        return;
    }
    inorderTraversal(node->getLeft());
    cout << node->getNum() << " ";
    inorderTraversal(node->getRight());
}

inline SplayTreeNode* SplayTree::findMin(SplayTreeNode* node) {
    return node->getLeft() == nullptr ? node : findMin(node->getLeft());
}

inline ChildType SplayTree::getChildType(SplayTreeNode* node) {
    if (!node || node == root) {
        return NO_PARENT;
    }
    SplayTreeNode* parent = node->getParent();
    if (!parent) {
        return NO_PARENT;
    } else if (node->getNum() >= parent->getNum()) {
        return RIGHT_CHILD;
    } else if (node->getNum() < parent->getNum()) {
        return LEFT_CHILD;
    }
}

SplayTreeNode* SplayTree::rightRotation(SplayTreeNode* node) {
    SplayTreeNode* parent = node->getParent();
    ChildType type = getChildType(node);
    SplayTreeNode* new_node = node->getLeft(); // 找尋新的節點 並為新節點建立關係
    if (new_node) {
        new_node->setParent(parent);
    }
    if (parent) {
        if (type == LEFT_CHILD) {
            parent->setLeft(new_node);
        } else if (type == RIGHT_CHILD) {
            parent->setRight(new_node);
        }
    } else {
        root = new_node;
    }
    // 新節點的右子變成舊節點的左子
    if (new_node && new_node->getRight()) {
        new_node->getRight()->setParent(node);
    }
    if (new_node) {
        node->setLeft(new_node->getRight());
    }
    // 舊節點變成新節點的左子
    node->setParent(new_node);
    new_node->setRight(node);
    return new_node;
}
SplayTreeNode* SplayTree::leftRotation(SplayTreeNode* node) {
    SplayTreeNode* parent = node->getParent();
    ChildType type = getChildType(node);
    SplayTreeNode* new_node = node->getRight(); // 找尋新的節點 並為新節點建立關係
    if (new_node) {
        new_node->setParent(parent);
    }
    if (parent) {
        if (type == LEFT_CHILD) {
            parent->setLeft(new_node);
        } else if (type == RIGHT_CHILD) {
            parent->setRight(new_node);
        }
    } else {
        root = new_node;
    }
    // 新節點的左子變成舊節點的右子
    if (new_node && new_node->getLeft()) {
        new_node->getLeft()->setParent(node);
    }
    if (new_node) {
        node->setRight(new_node->getLeft());
    }
    // 舊節點變成新節點的左子
    node->setParent(new_node);
    new_node->setLeft(node);
    return new_node;
}

SplayTreeNode* SplayTree::moveToRoot(SplayTreeNode* node) {
    if (!node || node == root) {
        return node;
    }
    if (getChildType(node) == LEFT_CHILD) { // node為left child
        if (node->getParent() == root) {    // Zig
            rightRotation(node->getParent());
            return node;
        }
        if (getChildType(node->getParent()) == LEFT_CHILD) { // Zig-zig
            rightRotation(node->getParent()->getParent());
            rightRotation(node->getParent());
            moveToRoot(node);
        } else if (getChildType(node->getParent()) == RIGHT_CHILD) { // Zig-zag
            rightRotation(node->getParent());
            leftRotation(node->getParent());
            moveToRoot(node);
        }
    } else if (getChildType(node) == RIGHT_CHILD) { // node為right child
        if (node->getParent() == root) {
            leftRotation(node->getParent());
            return node;
        }
        if (getChildType(node->getParent()) == RIGHT_CHILD) { // Zig-zig
            leftRotation(node->getParent()->getParent());
            leftRotation(node->getParent());
            moveToRoot(node);
        } else if (getChildType(node->getParent()) == LEFT_CHILD) { // Zig-zag
            leftRotation(node->getParent());
            rightRotation(node->getParent());
            moveToRoot(node);
        }
    }
    return node;
}

SplayTreeNode* SplayTree::search(SplayTreeNode* node, int num) {
    if (!node) {
        return nullptr;
    }
    if (num > node->getNum()) {
        return search(node->getRight(), num);
    } else if (num < node->getNum()) {
        return search(node->getLeft(), num);
    }
    root = moveToRoot(node);
    return node;
}

void SplayTree::insert(SplayTreeNode* node, SplayTreeNode* parent, int num) {
    if (!node) {
        // 建立一個new_node
        SplayTreeNode* new_node = new SplayTreeNode(num, parent, nullptr, nullptr);
        // 建立新關係
        if (getChildType(new_node) == LEFT_CHILD) {
            parent->setLeft(new_node);
        } else if (getChildType(new_node) == RIGHT_CHILD) {
            parent->setRight(new_node);
        }
        root = moveToRoot(new_node);
        return;
    }
    if (num > node->getNum()) {
        insert(node->getRight(), node, num); // 往右子樹丟
    } else if (num < node->getNum()) {
        insert(node->getLeft(), node, num); // 往左子樹丟
    } else {
        root = moveToRoot(node);
    }
}
void SplayTree::remove(SplayTreeNode* node, int num) {
    if (!search(node, num)) {
        return;
    }
    SplayTreeNode* tmp_node = root;
    if (root->getRight()) {                   // 有右子的話
        tmp_node = findMin(root->getRight()); // 替換節點
        root->setNum(tmp_node->getNum());
        if (getChildType(tmp_node) == LEFT_CHILD) { // 刪除tmp_node前，將其關係清洗
            tmp_node->getParent()->setLeft(tmp_node->getRight());
        } else if (getChildType(tmp_node) == RIGHT_CHILD) {
            tmp_node->getParent()->setRight(tmp_node->getRight());
        }
        if (tmp_node->getRight()) {
            tmp_node->getRight()->setParent(tmp_node->getParent());
        }
    } else { // 只有左子或沒有的話
        root = tmp_node->getLeft();
        root->setParent(nullptr);
    }
    delete tmp_node;
}

#endif