#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
using namespace std;

enum Color { RED, BLACK };

#ifndef CHILD_TYPE
#define CHILD_TYPE
enum ChildType { LEFT_CHILD, RIGHT_CHILD, NO_PARENT };
#endif

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
    ChildType getChildType(RBTreeNode* node);  // ��^��node�O��parent��Left�٬ORight child
    RBTreeNode* findMin(RBTreeNode* node);     // ��^ �̤p�l�`�I
    RBTreeNode* findUncle(RBTreeNode* node);   // ��^ uncle�`�I
    RBTreeNode* findBrother(RBTreeNode* node); // ��^ sibling�`�I
    void insertFix(RBTreeNode* node);          // ���s�վ㥭��(node���s�W�`�I)
    void removeFix(RBTreeNode* node);          // ���s�վ㥭��(node�����ɸ`�I)
    RBTreeNode* rightRotation(RBTreeNode* node);
    RBTreeNode* leftRotation(RBTreeNode* node);
    RBTreeNode* search(RBTreeNode* node, int num); // ��^�ؼи`�I��m�A�άOnullptr
    void insert(RBTreeNode* node, RBTreeNode* parent, int num); // root�i��|���ܡA�n�qNIL���s��
    void remove(RBTreeNode* node, RBTreeNode* parent, int num); // root�i��|���ܡA�n�qNIL���s��

  public:
    RedBlackTree(void) {
        NIL = new RBTreeNode(0, nullptr, nullptr, nullptr, BLACK); // NIL��Left node����root
        root = NIL;
    }
    ~RedBlackTree(void) { // TODO:���ӭn�R���Ҧ���node
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
        cout << (isLeft ? "�|�w�w " : "�z�w�w ");
        cout << "NIL" << endl;
        return;
    }
    printTree(node->getRight(), prefix + (isLeft ? "�x   " : "    "), false, isNum);
    cout << prefix;
    cout << (isLeft ? "�|�w�w " : "�z�w�w ");
    cout << (isNum ? to_string(node->getNum()) : (node->getColor() == RED ? "R" : "B")) << endl;
    printTree(node->getLeft(), prefix + (isLeft ? "    " : "�x   "), true, isNum);
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
    } else if (node->getParent() == NIL) { // �w�qroot�û��ONIL�����l
        return LEFT_CHILD;
    }
    RBTreeNode* parent = node->getParent();
    if (node->getNum() >= parent->getNum()) { // �M����N�`�I��num�Ȯɷ|�ۦP�A���@�w�Oright child
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
    // ��Xparent�OgrandParent��left child�٬Oright child
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
    // ��Xnode�Oparent��left child�٬Oright child
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
    RBTreeNode* new_node = node->getLeft(); // ��M�s���`�I �ì��s�`�I�إ����Y
    // ���Nparent
    new_node->setParent(parent);
    if (type == LEFT_CHILD) {
        parent->setLeft(new_node);
    } else if (type == RIGHT_CHILD) {
        parent->setRight(new_node);
    }
    // �s�`�I���k�l�ܦ��¸`�I�����l
    new_node->getRight()->setParent(node);
    node->setLeft(new_node->getRight());
    // �¸`�I�ܦ��s�`�I���k�l
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
    RBTreeNode* new_node = node->getRight(); // ��M�s���`�I �ì��s�`�I�إ����Y
    // ���Nparent
    new_node->setParent(parent);
    if (type == LEFT_CHILD) {
        parent->setLeft(new_node);
    } else if (type == RIGHT_CHILD) {
        parent->setRight(new_node);
    }
    // �s�`�I�����l�ܦ��¸`�I���k�l
    new_node->getLeft()->setParent(node);
    node->setRight(new_node->getLeft());
    // �¸`�I�ܦ��s�`�I�����l
    new_node->setLeft(node);
    node->setParent(new_node);
    if (node == root) {
        root = new_node;
    }
    return new_node;
}

/**
 * ����1 ���i�H�s�����
 * ����2 �Yblack node��leaf�g�L���¦�node�ƶq�ۦP
 * ����3 root���O�¦�
 * ����4 �Ҧ�leaf(NIL)���O�¦�
 */
void RedBlackTree::insertFix(RBTreeNode* node) {
    if (!node || node == NIL) {
        return;
    } else if (node->getParent() == NIL) { // ����3: root�����O�¦�
        node->setColor(BLACK);
        return;
    } else if (node->getParent()->getColor() == BLACK) { // �����Ҧ�����A���ΰ���
        return;
    }
    // �H�ϱ���1
    RBTreeNode* parent = node->getParent();
    RBTreeNode* grandParent = parent->getParent();
    RBTreeNode* uncle = findUncle(node);
    if (uncle->getColor() == BLACK) {
        // node�۹��grandParent�OLL�BLR�BRL�BRR?
        if (getChildType(parent) == LEFT_CHILD) {
            if (getChildType(node) == LEFT_CHILD) { // LL
                // parent�PgrandParent���ܦ�
                parent->setColor(parent->getColor() == RED ? BLACK : RED);
                grandParent->setColor(grandParent->getColor() == RED ? BLACK : RED);
                rightRotation(grandParent);
            } else if (getChildType(node) == RIGHT_CHILD) { // LR
                // node�PgrandParent���ܦ�
                node->setColor(node->getColor() == RED ? BLACK : RED);
                grandParent->setColor(grandParent->getColor() == RED ? BLACK : RED);
                leftRotation(parent);
                rightRotation(grandParent);
            } else {
                cout << "Error: insertFix" << endl;
            }
        } else if (getChildType(parent) == RIGHT_CHILD) {
            if (getChildType(node) == LEFT_CHILD) { // RL
                // node�PgrandParent���ܦ�
                node->setColor(node->getColor() == RED ? BLACK : RED);
                grandParent->setColor(grandParent->getColor() == RED ? BLACK : RED);
                rightRotation(parent);
                leftRotation(grandParent);
            } else if (getChildType(node) == RIGHT_CHILD) { // RR
                // parent�PgrandParent���ܦ�
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
        // parent�Buncle�BgrandParent�ܦ�
        parent->setColor(parent->getColor() == RED ? BLACK : RED);
        grandParent->setColor(grandParent->getColor() == RED ? BLACK : RED);
        uncle->setColor(uncle->getColor() == RED ? BLACK : RED);
        // grandParent���s�ˬd
        insertFix(grandParent);
    }
}
void RedBlackTree::removeFix(RBTreeNode* node) {
    // ����node�u�|���@��child
    if (!node) {
        return;
    }
    if (node == root || node->getColor() == RED) { // �Y���ɸ`�I�O����A������¦�Y�i
        node->setColor(BLACK);
        return;
    }
    RBTreeNode* brother = findBrother(node); // remove�n��brother���C��
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
    if (!node || node == NIL) {
        return nullptr;
    }
    if (num > node->getNum()) {
        return search(node->getRight(), num);
    } else if (num < node->getNum()) {
        return search(node->getLeft(), num);
    }
    return node;
}

void RedBlackTree::insert(RBTreeNode* node, RBTreeNode* parent, int num) {
    if (!node || node == NIL) {
        // �إߤ@�ӷs���`�I
        RBTreeNode* new_node = new RBTreeNode(num, parent, NIL, NIL, parent == NIL ? BLACK : RED);
        // �إ߷s���Y
        if (getChildType(new_node) == LEFT_CHILD) {
            parent->setLeft(new_node);
        } else if (getChildType(new_node) == RIGHT_CHILD) {
            parent->setRight(new_node);
        } else {
        }
        insertFix(new_node); // �ˬd�O�_�ݭn����
        root = NIL->getLeft();
        return;
    }
    if (num > node->getNum()) {
        insert(node->getRight(), node, num); // ���k�l���
    } else if (num < node->getNum()) {
        insert(node->getLeft(), node, num); // �����l���
    }
}

void RedBlackTree::remove(RBTreeNode* node, RBTreeNode* parent, int num) {
    if (!node || node == NIL) {
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
    RBTreeNode* del_node = node;
    RBTreeNode* tmp_node;
    if (del_node->getLeft() != NIL && del_node->getRight() != NIL) { // �����child node
        tmp_node = findMin(del_node->getRight());                    // ��M���N�`�I
        del_node->setNum(tmp_node->getNum()); // ����N�`�I����Ʒm�L��
        del_node = tmp_node;                  // ��R���N�`�I
    }
    if (del_node->getLeft() == NIL) {
        tmp_node = del_node->getRight(); // ���N�R�����`�I
    } else if (del_node->getRight() == NIL) {
        tmp_node = del_node->getLeft();
    }
    // ��del_node����Ƶ�tmp_node
    tmp_node->setParent(del_node->getParent());
    if (getChildType(del_node) == LEFT_CHILD) {
        del_node->getParent()->setLeft(tmp_node);
    } else if (getChildType(del_node) == RIGHT_CHILD) {
        del_node->getParent()->setRight(tmp_node);
    }
    // root�i��|�ܧ�
    if (root == del_node) {
        root = tmp_node;
    }
    // �Rred node�S���Y
    if (del_node->getColor() == BLACK) {
        removeFix(del_node); // ���ӭn�OremoveFix(tmp_node)�~��r?!
    }
    delete del_node;
}

#endif