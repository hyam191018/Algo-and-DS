#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
using namespace std;

enum Color { RED, BLACK };
enum ChildType { LEFT_CHILD, RIGHT_CHILD, NO_PARENT };

class RBTreeNode {
  private:
    int num;
    RBTreeNode *parent, *left, *right;
    Color color; // true for red, false for black

  public:
    RBTreeNode(int num, RBTreeNode* parent, RBTreeNode* left, RBTreeNode* right, Color color)
        : num(num), parent(parent), left(left), right(right), color(color) {}
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

class RedBlackTree {
  private:
    RBTreeNode* NIL;
    RBTreeNode* root;
    void printTree(RBTreeNode* node, string prefix, bool isLeft,
                   bool isNum /* ture for number, false for color*/);
    void inorderTraversal(RBTreeNode* node);
    ChildType getChildType(RBTreeNode* node);  // 返回該node是其parent的Left還是Right child
    RBTreeNode* findMin(RBTreeNode* node);     // 返回 最小子節點
    RBTreeNode* findUncle(RBTreeNode* node);   // 返回 uncle節點
    RBTreeNode* findBrother(RBTreeNode* node); // 返回 sibling節點
    void insertFix(RBTreeNode* node);          // 重新調整平衡(node為新增節點)
    void removeFix(RBTreeNode* node);          // 重新調整平衡(node為替補節點)
    RBTreeNode* rightRotation(RBTreeNode* node);
    RBTreeNode* leftRotation(RBTreeNode* node);
    RBTreeNode* search(RBTreeNode* node, int num); // 返回目標節點位置，或是nullptr
    void insert(RBTreeNode* node, RBTreeNode* parent, int num); // root可能會改變，要從NIL重新抓
    void remove(RBTreeNode* node, RBTreeNode* parent, int num); // root可能會改變，要從NIL重新抓

  public:
    RedBlackTree(void) {
        NIL = new RBTreeNode(0, nullptr, nullptr, nullptr, BLACK); // NIL的Left node必為root
        root = NIL;
    }
    ~RedBlackTree(void) { // TODO:應該要刪除所有的node
        delete NIL;
    }
    void printTree(void) { printTree(root, "", true, true); }
    void printColor(void) { printTree(root, "", true, false); }
    void inorderTraversal(void) { inorderTraversal(root); }
    bool search(int num) { return search(root, num); }
    void insert(int num) { insert(root, NIL, num); }
    void remove(int num) { remove(root, NIL, num); }
};

void RedBlackTree::printTree(RBTreeNode* node, string prefix = "", bool isLeft = true,
                             bool isNum = true) {
    if (!node) {
        return;
    }
    if (node == NIL) {
        cout << prefix;
        cout << (isLeft ? "└── " : "┌── ");
        cout << "NIL" << endl;
        return;
    }
    printTree(node->getRight(), prefix + (isLeft ? "│   " : "    "), false, isNum);
    cout << prefix;
    cout << (isLeft ? "└── " : "┌── ");
    cout << (isNum ? to_string(node->getNum()) : (node->getColor() == RED ? "R" : "B")) << endl;
    printTree(node->getLeft(), prefix + (isLeft ? "    " : "│   "), true, isNum);
}

void RedBlackTree::inorderTraversal(RBTreeNode* node) {
    if (!node || node == NIL) {
        return;
    }
    inorderTraversal(node->getLeft());
    cout << node->getNum() << " ";
    inorderTraversal(node->getRight());
}

inline RBTreeNode* RedBlackTree::findMin(RBTreeNode* node) {
    return node->getLeft() == NIL ? node : findMin(node->getLeft());
}

inline ChildType RedBlackTree::getChildType(RBTreeNode* node) {
    if (!node || node == NIL) {
        return NO_PARENT;
    } else if (node->getParent() == NIL) { // 定義root永遠是NIL的左子
        return LEFT_CHILD;
    }
    RBTreeNode* parent = node->getParent();
    if (node->getNum() >= parent->getNum()) { // 尋找替代節點時num暫時會相同，但一定是right child
        return RIGHT_CHILD;
    } else if (node->getNum() < parent->getNum()) {
        return LEFT_CHILD;
    }
    cout << "Error: I am my parent!" << endl;
    return NO_PARENT;
}

inline RBTreeNode* RedBlackTree::findUncle(RBTreeNode* node) {
    if (!node || node->getParent() == NIL || node->getParent()->getParent() == NIL) {
        return NIL;
    }
    // 找出parent是grandParent的left child還是right child
    RBTreeNode* parent = node->getParent();
    RBTreeNode* grandParent = parent->getParent();
    if (getChildType(parent) == LEFT_CHILD) {
        return grandParent->getRight();
    } else if (getChildType(parent) == RIGHT_CHILD) {
        return grandParent->getLeft();
    }
    return NIL;
}

inline RBTreeNode* RedBlackTree::findBrother(RBTreeNode* node) {
    if (!node || node->getParent() == NIL) {
        return NIL;
    }
    // 找出node是parent的left child還是right child
    RBTreeNode* parent = node->getParent();
    if (getChildType(node) == LEFT_CHILD) {
        return parent->getRight();
    } else if (getChildType(node) == RIGHT_CHILD) {
        return parent->getLeft();
    }
    return NIL;
}
RBTreeNode* RedBlackTree::rightRotation(RBTreeNode* node) {
    RBTreeNode* parent = node->getParent();
    ChildType type = getChildType(node);
    RBTreeNode* new_node = node->getLeft(); // 找尋新的節點 並為新節點建立關係
    // 取代parent
    new_node->setParent(parent);
    if (type == LEFT_CHILD) {
        parent->setLeft(new_node);
    } else if (type == RIGHT_CHILD) {
        parent->setRight(new_node);
    }
    // 新節點的右子變成舊節點的左子
    new_node->getRight()->setParent(node);
    node->setLeft(new_node->getRight());
    // 舊節點變成新節點的右子
    new_node->setRight(node);
    node->setParent(new_node);
    if (node == root) {
        root = new_node;
    }
    return new_node;
}
RBTreeNode* RedBlackTree::leftRotation(RBTreeNode* node) {
    RBTreeNode* parent = node->getParent();
    ChildType type = getChildType(node);
    RBTreeNode* new_node = node->getRight(); // 找尋新的節點 並為新節點建立關係
    // 取代parent
    new_node->setParent(parent);
    if (type == LEFT_CHILD) {
        parent->setLeft(new_node);
    } else if (type == RIGHT_CHILD) {
        parent->setRight(new_node);
    }
    // 新節點的左子變成舊節點的右子
    new_node->getLeft()->setParent(node);
    node->setRight(new_node->getLeft());
    // 舊節點變成新節點的左子
    new_node->setLeft(node);
    node->setParent(new_node);
    if (node == root) {
        root = new_node;
    }
    return new_node;
}

/**
 * 條件1 不可以連續紅色
 * 條件2 某black node到leaf經過的黑色node數量相同
 * 條件3 root必是黑色
 * 條件4 所有leaf(NIL)都是黑色
 */
void RedBlackTree::insertFix(RBTreeNode* node) {
    if (!node || node == NIL) {
        return;
    } else if (node->getParent() == NIL) { // 條件3: root必須是黑色
        node->setColor(BLACK);
        return;
    } else if (node->getParent()->getColor() == BLACK) { // 滿足所有條件，不用做事
        return;
    }
    // 違反條件1
    RBTreeNode* parent = node->getParent();
    RBTreeNode* grandParent = parent->getParent();
    RBTreeNode* uncle = findUncle(node);
    if (uncle->getColor() == BLACK) {
        // node相對於grandParent是LL、LR、RL、RR?
        if (getChildType(parent) == LEFT_CHILD) {
            if (getChildType(node) == LEFT_CHILD) { // LL
                // parent與grandParent先變色
                parent->setColor(parent->getColor() == RED ? BLACK : RED);
                grandParent->setColor(grandParent->getColor() == RED ? BLACK : RED);
                rightRotation(grandParent);
            } else if (getChildType(node) == RIGHT_CHILD) { // LR
                // node與grandParent先變色
                node->setColor(node->getColor() == RED ? BLACK : RED);
                grandParent->setColor(grandParent->getColor() == RED ? BLACK : RED);
                leftRotation(parent);
                rightRotation(grandParent);
            } else {
                cout << "Error: insertFix" << endl;
            }
        } else if (getChildType(parent) == RIGHT_CHILD) {
            if (getChildType(node) == LEFT_CHILD) { // RL
                // node與grandParent先變色
                node->setColor(node->getColor() == RED ? BLACK : RED);
                grandParent->setColor(grandParent->getColor() == RED ? BLACK : RED);
                rightRotation(parent);
                leftRotation(grandParent);
            } else if (getChildType(node) == RIGHT_CHILD) { // RR
                // parent與grandParent先變色
                parent->setColor(parent->getColor() == RED ? BLACK : RED);
                grandParent->setColor(grandParent->getColor() == RED ? BLACK : RED);
                leftRotation(grandParent);
            } else {
                cout << "Error: insertFix" << endl;
            }
        } else {
            cout << "Error: insertFix" << endl;
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
void RedBlackTree::removeFix(RBTreeNode* node) {
    // 此時node只會有一個child
    if (!node) {
        return;
    }
    if (node == root || node->getColor() == RED) { // 若替補節點是紅色，直接塗成黑色即可
        node->setColor(BLACK);
        return;
    }
    RBTreeNode* brother = findBrother(node); // remove要看brother的顏色
    RBTreeNode* parent = node->getParent();
    if (getChildType(node) == LEFT_CHILD) {
        if (brother->getColor() == RED) {
            brother->setColor(BLACK);
            parent->setColor(RED);
            leftRotation(parent);
            brother = findBrother(node);
        }
        if (brother->getRight()->getColor() == BLACK && brother->getLeft()->getColor() == BLACK) {
            brother->setColor(RED);
            removeFix(parent);
        } else {
            if (brother->getRight()->getColor() == BLACK) {
                brother->getLeft()->setColor(BLACK);
                brother->setColor(RED);
                rightRotation(brother);
                brother = findBrother(node);
            }
            brother->setColor(parent->getColor());
            parent->setColor(BLACK);
            brother->getRight()->setColor(BLACK);
            leftRotation(parent);
        }
    } else if (getChildType(node) == RIGHT_CHILD) {
        if (brother->getColor() == RED) {
            brother->setColor(BLACK);
            parent->setColor(RED);
            rightRotation(parent);
            brother = findBrother(node);
        }
        if (brother->getLeft()->getColor() == BLACK && brother->getRight()->getColor() == BLACK) {
            brother->setColor(RED);
            removeFix(parent);
        } else {
            if (brother->getLeft()->getColor() == BLACK) {
                brother->getRight()->setColor(BLACK);
                brother->setColor(RED);
                leftRotation(brother);
                brother = findBrother(node);
            }
            brother->setColor(parent->getColor());
            parent->setColor(BLACK);
            brother->getLeft()->setColor(BLACK);
            rightRotation(parent);
        }
    }
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

void RedBlackTree::insert(RBTreeNode* node, RBTreeNode* parent, int num) {
    if (!node || node == NIL) {
        // 建立一個新的節點
        RBTreeNode* new_node = new RBTreeNode(num, parent, NIL, NIL, parent == NIL ? BLACK : RED);
        // 建立新關係
        if (getChildType(new_node) == LEFT_CHILD) {
            parent->setLeft(new_node);
        } else if (getChildType(new_node) == RIGHT_CHILD) {
            parent->setRight(new_node);
        } else {
        }
        insertFix(new_node); // 檢查是否需要平衡
        root = NIL->getLeft();
        return;
    }
    if (num > node->getNum()) {
        insert(node->getRight(), node, num); // 往右子樹丟
    } else if (num < node->getNum()) {
        insert(node->getLeft(), node, num); // 往左子樹丟
    }
}

void RedBlackTree::remove(RBTreeNode* node, RBTreeNode* parent, int num) {
    if (!node || node == NIL) {
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
    RBTreeNode* del_node = node;
    RBTreeNode* tmp_node;
    if (del_node->getLeft() != NIL && del_node->getRight() != NIL) { // 有兩個child node
        tmp_node = findMin(del_node->getRight());                    // 找尋替代節點
        del_node->setNum(tmp_node->getNum()); // 把替代節點的資料搶過來
        del_node = tmp_node;                  // 改刪替代節點
    }
    if (del_node->getLeft() == NIL) {
        tmp_node = del_node->getRight(); // 取代刪除的節點
    } else if (del_node->getRight() == NIL) {
        tmp_node = del_node->getLeft();
    }
    // 把del_node的資料給tmp_node
    tmp_node->setParent(del_node->getParent());
    if (getChildType(del_node) == LEFT_CHILD) {
        del_node->getParent()->setLeft(tmp_node);
    } else if (getChildType(del_node) == RIGHT_CHILD) {
        del_node->getParent()->setRight(tmp_node);
    }
    // root可能會變更
    if (root == del_node) {
        root = tmp_node;
    }
    // 刪red node沒關係
    if (del_node->getColor() == BLACK) {
        removeFix(tmp_node);
    }
    delete del_node;
}

#endif