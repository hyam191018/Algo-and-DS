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
 * �w�q�@��Red black tree
 * @param root ��ʾ𪺮ڵ��I
 * @param node_number ��ʾ𪺸`�I��
 * @fn printTree �L�X�C�Ӹ`�I�x�s���Ʀr
 * @fn printColor �L�X�C�Ӹ`�I���C��(red or black)�A�Ω�����
 * @fn inorderTraversal ���Ӥ��ǿ�X�`�I�A�ѩ�left < parent <
 * right�A�G��n�O�Ѥp��j�ƦC
 * @fn search �d�ߤ@�ӼƦr�O�_�s�b
 * - @return true �s�b
 * - @return false ���s�b
 * @fn insert ���J�@�ӼƦr��RB tree
 * @fn remove �N�@�ӼƦr�`�I����
 */
class RedBlackTree {
  private:
    RBTreeNode* root;
    RBTreeNode* NIL;
    int node_number;
    void printTree(RBTreeNode* node, string prefix, bool isLeft,
                   bool isNum /* ture for number, false for color*/);
    void inorderTraversal(RBTreeNode* node);
    RBTreeNode* findMin(RBTreeNode* node);   // ��^�̤p�l�`�I
    bool isLeftChild(RBTreeNode* node);      // true�A�p�G��node�O��parent��left node
    RBTreeNode* findUncle(RBTreeNode* node); // ��^���`�I
    void insertFix(RBTreeNode* node);        // ���s�վ㥭��
    void removeFix(RBTreeNode* node);        // ���s�վ㥭��
    RBTreeNode* rightRotation(RBTreeNode* node);
    RBTreeNode* leftRotation(RBTreeNode* node);
    RBTreeNode* search(RBTreeNode* node, int num); // ��^�ؼи`�I��m�A�άOnullptr
    void insert(RBTreeNode* node, RBTreeNode* parent, int num); // root�i��|���ܡA�n�qNIL���s��
    void remove(RBTreeNode* node, RBTreeNode* parent, int num); // root�i��|���ܡA�n�qNIL���s��

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
    printTree(node->getRight(), prefix + (isLeft ? "�x   " : "    "), false, isNum);
    cout << prefix;
    cout << (isLeft ? "�|�w�w " : "�z�w�w ");
    cout << (isNum ? to_string(node->getNum()) : (node->getColor() == RED ? "R" : "B")) << endl;
    printTree(node->getLeft(), prefix + (isLeft ? "    " : "�x   "), true, isNum);
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
    } else if (node->getParent() == NIL) { // �]���w�qroot�û��ONIL�����l
        return true;
    }
    RBTreeNode* parent = node->getParent();
    if (node->getNum() >= parent->getNum()) { // node�O�k�l(�洫���ɭԥi��|�ۦP)
        return false;
    }
    return true;
}
inline RBTreeNode* RedBlackTree::findUncle(RBTreeNode* node) {
    if (!node || node->getParent() == NIL || (node->getParent())->getParent() == NIL) {
        return nullptr;
    }
    // ��X���ˬO���������l�٬O�k�l
    RBTreeNode* parent = node->getParent();
    RBTreeNode* grandParent = parent->getParent();
    return isLeftChild(parent) ? grandParent->getRight() : grandParent->getLeft();
}
RBTreeNode* RedBlackTree::rightRotation(RBTreeNode* node) {
    // �����Dparent�H��node�Oparent�����l�٬O�k�l
    RBTreeNode* parent = node->getParent();
    bool isLeft = isLeftChild(node);
    RBTreeNode* new_node = node->getLeft(); // ��M�s���`�I
    new_node->setParent(parent);            // �إ߷s�`�I�����Y
    isLeft ? parent->setLeft(new_node) : parent->setRight(new_node);
    if (new_node->getRight()) {
        (new_node->getRight())->setParent(node); // �s�`�I���k�l�ܦ��¸`�I�����l
    }
    node->setLeft(new_node->getRight());
    new_node->setRight(node); // �¸`�I�ܦ��s�`�I���k�l
    node->setParent(new_node);
    return new_node;
}
RBTreeNode* RedBlackTree::leftRotation(RBTreeNode* node) {
    // �����Dparent�H��node�Oparent�����l�٬O�k�l
    RBTreeNode* parent = node->getParent();
    bool isLeft = isLeftChild(node);
    RBTreeNode* new_node = node->getRight(); // ��M�s���`�I
    new_node->setParent(parent);             // �إ߷s�`�I�����Y
    isLeft ? parent->setLeft(new_node) : parent->setRight(new_node);
    if (new_node->getLeft()) {
        (new_node->getLeft())->setParent(node); // �s�`�I�����l�ܦ��¸`�I���k�l
    }
    node->setRight(new_node->getLeft());
    new_node->setLeft(node); // �¸`�I�ܦ��s�`�I�����l
    node->setParent(new_node);
    return new_node;
}
/**
 * ����1 ���i�H�s�����
 * ����2 �Ynode��leaf�g�L���¦�node�ƶq�ۦP
 * ����3 �ڸ`�I���O�¦�
 * ����4 �Ҧ�leaf���O�¦�
 */
void RedBlackTree::insertFix(RBTreeNode* node) {
    if (!node) {
        return;
    } else if (node->getParent() == NIL) { // ����3
        node->setColor(BLACK);
        return;
    } else if ((node->getParent())->getColor() == BLACK) { // �����Ҧ�����A���ΰ���
        return;
    }
    // �H�ϱ���1
    RBTreeNode* parent = node->getParent();
    RBTreeNode* grandParent = parent->getParent();
    RBTreeNode* uncle = findUncle(node);
    if (!uncle || uncle->getColor() == BLACK) {
        // node�۹��grandParent�OLL�BLR�BRL�BRR?
        if (isLeftChild(parent)) {
            if (isLeftChild(node)) { // LL
                // parent�PgrandParent���ܦ�
                parent->setColor(parent->getColor() == RED ? BLACK : RED);
                grandParent->setColor(grandParent->getColor() == RED ? BLACK : RED);
                rightRotation(grandParent);
            } else { // LR
                // node�PgrandParent���ܦ�
                node->setColor(node->getColor() == RED ? BLACK : RED);
                grandParent->setColor(grandParent->getColor() == RED ? BLACK : RED);
                leftRotation(parent);
                rightRotation(grandParent);
            }
        } else {
            if (isLeftChild(node)) { // RL
                // node�PgrandParent���ܦ�
                node->setColor(node->getColor() == RED ? BLACK : RED);
                grandParent->setColor(grandParent->getColor() == RED ? BLACK : RED);
                rightRotation(parent);
                leftRotation(grandParent);
            } else { // RR
                // parent�PgrandParent���ܦ�
                parent->setColor(parent->getColor() == RED ? BLACK : RED);
                grandParent->setColor(grandParent->getColor() == RED ? BLACK : RED);
                leftRotation(grandParent);
            }
        }
    } else {
        // parent�Buncle�BgrandParent�ܦ�
        parent->setColor(parent->getColor() == RED ? BLACK : RED);
        grandParent->setColor(grandParent->getColor() == RED ? BLACK : RED);
        uncle->setColor(uncle->getColor() == RED ? BLACK : RED);
        // grandParent���s�ˬd
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
        // �إߤ@�ӷs���`�I
        node_number++;
        RBTreeNode* new_node = new RBTreeNode(num, parent, parent == NIL ? BLACK : RED);
        // parent�{child
        isLeftChild(new_node) ? parent->setLeft(new_node) : parent->setRight(new_node);
        insertFix(new_node); // �ˬd�O�_�ݭn����
        return;
    }
    if (num > node->getNum()) {
        insert(node->getRight(), node, num); // ���k�l���
    } else if (num < node->getNum()) {
        insert(node->getLeft(), node, num); // �����l���
    }
}
void RedBlackTree::remove(RBTreeNode* node, RBTreeNode* parent, int num) {
    if (!node) {
        return;
    }
    if (num > node->getNum()) {
        remove(node->getRight(), node, num); // ���k�l���
        return;
    } else if (num < node->getNum()) {
        remove(node->getLeft(), node, num); // �����l���
        return;
    }
    // �R��node�A�B�M��s��node����
    RBTreeNode* new_node = nullptr;
    if (node->getRight()) {
        if (node->getLeft()) {                    // ����Ӥl�`�I
            new_node = findMin(node->getRight()); // ����N�`�I(�k�l��̤p�άO���l��̤j)
            node->setColor(new_node->getColor()); // �����s�`�I����T(���洫)
            node->setNum(new_node->getNum());
            remove(node->getRight(), node, new_node->getNum()); // �����s�`�I
            return;
        } else { // �u���k�`�I�A�����ɤW
            new_node = node->getRight();
            new_node->setParent(parent); // �إ߷s�`�I���Y
            isLeftChild(node) ? parent->setLeft(new_node) : parent->setRight(new_node);
        }
    } else if (node->getLeft()) { // �u�����`�I�A�����ɤW
        new_node = node->getLeft();
        new_node->setParent(parent); // �إ߷s�`�I���Y
        isLeftChild(node) ? parent->setLeft(new_node) : parent->setRight(new_node);
    } else { // �S���l�`�I�A����parent�n���node���
        isLeftChild(node) ? parent->setLeft(new_node) : parent->setRight(new_node);
    }
    node_number--;
    delete node;
}

#endif