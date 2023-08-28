#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <iostream>
using namespace std;

enum ChildType { LEFT_CHILD, RIGHT_CHILD, NO_PARENT };

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
    ChildType getChildType(SplayTreeNode* node); // ��^��node�O��parent��Left�٬ORight child
    SplayTreeNode* findMin(SplayTreeNode* node); // ��^ �̤p�l�`�I
    SplayTreeNode* rightRotation(SplayTreeNode* node);
    SplayTreeNode* leftRotation(SplayTreeNode* node);
    SplayTreeNode* moveToRoot(SplayTreeNode* node);      // ��^�s��root
    SplayTreeNode* search(SplayTreeNode* node, int num); // ��^�ؼ�node
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
    printTree(node->getRight(), prefix + (isLeft ? "�x   " : "    "), false);
    cout << prefix;
    cout << (isLeft ? "�|�w�w " : "�z�w�w ");
    cout << node->getNum() << endl;
    printTree(node->getLeft(), prefix + (isLeft ? "    " : "�x   "), true);
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
    SplayTreeNode* new_node = node->getLeft(); // ��M�s���`�I �ì��s�`�I�إ����Y
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
    // �s�`�I���k�l�ܦ��¸`�I�����l
    if (new_node && new_node->getRight()) {
        new_node->getRight()->setParent(node);
    }
    if (new_node) {
        node->setLeft(new_node->getRight());
    }
    // �¸`�I�ܦ��s�`�I�����l
    node->setParent(new_node);
    new_node->setRight(node);
    return new_node;
}
SplayTreeNode* SplayTree::leftRotation(SplayTreeNode* node) {
    SplayTreeNode* parent = node->getParent();
    ChildType type = getChildType(node);
    SplayTreeNode* new_node = node->getRight(); // ��M�s���`�I �ì��s�`�I�إ����Y
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
    // �s�`�I�����l�ܦ��¸`�I���k�l
    if (new_node && new_node->getLeft()) {
        new_node->getLeft()->setParent(node);
    }
    if (new_node) {
        node->setRight(new_node->getLeft());
    }
    // �¸`�I�ܦ��s�`�I�����l
    node->setParent(new_node);
    new_node->setLeft(node);
    return new_node;
}

SplayTreeNode* SplayTree::moveToRoot(SplayTreeNode* node) {
    if (!node || node == root) {
        return node;
    }
    if (getChildType(node) == LEFT_CHILD) { // node��left child
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
    } else if (getChildType(node) == RIGHT_CHILD) { // node��right child
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
        // �إߤ@��new_node
        SplayTreeNode* new_node = new SplayTreeNode(num, parent, nullptr, nullptr);
        // �إ߷s���Y
        if (getChildType(new_node) == LEFT_CHILD) {
            parent->setLeft(new_node);
        } else if (getChildType(new_node) == RIGHT_CHILD) {
            parent->setRight(new_node);
        }
        root = moveToRoot(new_node);
        return;
    }
    if (num > node->getNum()) {
        insert(node->getRight(), node, num); // ���k�l���
    } else if (num < node->getNum()) {
        insert(node->getLeft(), node, num); // �����l���
    } else {
        root = moveToRoot(node);
    }
}
void SplayTree::remove(SplayTreeNode* node, int num) {
    if (!search(node, num)) {
        return;
    }
    SplayTreeNode* tmp_node = root;
    if (root->getRight()) {                   // ���k�l����
        tmp_node = findMin(root->getRight()); // �����`�I
        root->setNum(tmp_node->getNum());
        if (getChildType(tmp_node) == LEFT_CHILD) { // �R��tmp_node�e�A�N�����Y�M�~
            tmp_node->getParent()->setLeft(tmp_node->getRight());
        } else if (getChildType(tmp_node) == RIGHT_CHILD) {
            tmp_node->getParent()->setRight(tmp_node->getRight());
        }
        if (tmp_node->getRight()) {
            tmp_node->getRight()->setParent(tmp_node->getParent());
        }
    } else { // �u�����l�ΨS������
        root = tmp_node->getLeft();
    }
    delete tmp_node;
}

#endif