#ifndef TREE_T
#define TREE_T

#include <iostream>
using namespace std;

/**
 * �w�q�@��BST��node
 * @param num �x�s����(key)
 * @param height �Ӹ`�I�b��Ӿ𤤪�����
 * @param left left node
 * @param right right node
 * @fn updateHeight - ���s�p�⦹node������
 */
class TreeNode {
  public:
    int num;
    int height; // for self-balance tree
    TreeNode* left;
    TreeNode* right;
    TreeNode(void) : num(0), height(-1), left(nullptr), right(nullptr) {}
    TreeNode(int num) : num(num), height(-1), left(nullptr), right(nullptr) {}
    void updateHeight(TreeNode* node) { // for self-balance tree
        if (!node) {
            return;
        }
        if (!node->left && !node->right) {
            node->height = 0;
            return;
        }

        updateHeight(node->left);
        updateHeight(node->right);
        int right_h = -1, left_h = -1;
        if (node->left) {
            left_h = (node->left)->height;
        }
        if (node->right) {
            right_h = (node->right)->height;
        }
        node->height = 1 + (left_h > right_h ? left_h : right_h);
    }
    void updateHeight(void) { updateHeight(this); } // for self-balance tree
};

/**
 * �w�q�@��Binear tree���򥻥\��
 * @param root ��ʾ𪺮ڵ��I
 * @fn printTree - ��X��ʾ𪺵��c
 * @fn inorderTraversal- �q�p��j�L�X��node value
 * @fn inorderTraversalInv- �q�j��p�L�X��node value
 */
class TreeBase {
  protected:
    TreeNode* root;
    int node_num;
    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

  public:
    TreeBase(void) : root(nullptr), node_num(0) {}
    void printTree(TreeNode* node, string prefix = "", bool isLeft = true) {
        if (node == nullptr) {
            return;
        }

        printTree(node->right, prefix + (isLeft ? "�x   " : "    "), false);

        cout << prefix;
        cout << (isLeft ? "�|�w�w " : "�z�w�w ");
        cout << node->num << endl;

        printTree(node->left, prefix + (isLeft ? "    " : "�x   "), true);
    }
    void printTree(void) { printTree(root); }
    void inorderTraversal(TreeNode* node) {
        if (!node)
            return;
        inorderTraversal(node->left);
        cout << node->num << " ";
        inorderTraversal(node->right);
    }
    void inorderTraversalInv(TreeNode* node) {
        if (!node)
            return;
        inorderTraversalInv(node->right);
        cout << node->num << " ";
        inorderTraversalInv(node->left);
    }
    void inorderTraversal(void) {
        inorderTraversal(root);
        cout << endl;
    }
    void inorderTraversalInv(void) {
        inorderTraversalInv(root);
        cout << endl;
    }
};

/**
 * �w�q�@��BST���򥻥\��
 * @fn insert - ���J�@�Ӽƨ�BST
 * @fn search - �bBST��M�@�Ӽ�
 * @fn remove - �qBST�����@�Ӽ�
 */
class BinarySearchTree : public TreeBase {
  protected:
    TreeNode* insert(TreeNode* node, int num) {
        TreeNode* new_node;
        if (!node) { // �إ߷s��node
            new_node = new TreeNode(num);
            return new_node;
        }

        if (num > node->num) {
            node->right = insert(node->right, num);
        } else if (num < node->num) {
            node->left = insert(node->left, num);
        }
        return node;
    }
    bool search(TreeNode* node, int num) {
        if (!node) {
            return false;
        } else if (num == node->num) {
            return true;
        }

        if (num > node->num) {
            return search(node->right, num);
        } else {
            return search(node->left, num);
        }
    }
    TreeNode* remove(TreeNode* node, int num) {
        if (!node) { // ���s�b
            return nullptr;
        } else if (num == node->num) { // �R��
            TreeNode* new_node = nullptr;
            if (node->right) { // ���N
                if (node->left) {
                    new_node = findMin(node->right);
                    node->num = new_node->num;
                    node->right = remove(node->right, new_node->num);
                    return node;
                } else {
                    new_node = node->right;
                }
            } else if (node->left) {
                new_node = node->left;
            }
            delete node;
            return new_node;
        }

        if (num > node->num) {
            node->right = remove(node->right, num);
        } else {
            node->left = remove(node->left, num);
        }
        return node;
    }

  public:
    void insert(int num) { root = insert(root, num); }
    bool search(int num) { return search(root, num); }
    void remove(int num) { root = remove(root, num); }
};

/** -----------------------------------------------------------------*/

/**
 * AVL��OBST���i�����A�b�C�@����insert�Premove���|�۰ʽվ�𪺥��šA���M���C�F�@��insert�Premove���į�
 * ���O�঳�Ĵ���search���t��
 * @fn insert - ���J�@�Ӽƨ�AVLTree(�ۤ�BST�h�F�ק�𰪸򭫷s����)
 * @fn search - �bAVLTree��M�@�Ӽ�
 * @fn remove - �qAVTTree�����@�Ӽ�(�ۤ�BST�h�F�ק�𰪸򭫷s����)
 */
class AVLTree : public BinarySearchTree {
  protected:
    int balance_factor(TreeNode* node) {
        if (!node) {
            return 0;
        }

        int left_height = (node->left ? (node->left)->height : -1);
        int right_height = (node->right ? (node->right)->height : -1);

        return left_height - right_height;
    }
    TreeNode* right_rotation(TreeNode* node) {
        TreeNode* new_node = node->left;
        node->left = new_node->right;
        new_node->right = node;
        return new_node;
    }
    TreeNode* left_rotation(TreeNode* node) {
        TreeNode* new_node = node->right;
        node->right = new_node->left;
        new_node->left = node;
        return new_node;
    }
    void update_treeHeight(TreeNode* node) { node->updateHeight(); }
    TreeNode* update_treeBalance(TreeNode* node) {
        if (!node) {
            return nullptr;
        }
        int bf = balance_factor(node);
        if (bf > 1) { // ���l��L��
            if (balance_factor(node->left) >= 1) {
                // LL type
                return right_rotation(node);
            } else {
                // LR type
                node->left = left_rotation(node->left);
                return right_rotation(node);
            }
        } else if (bf < -1) { // �k�l��L��
            if (balance_factor(node->right) <= -1) {
                // RR type
                return left_rotation(node);
            } else {
                // RL type
                node->right = right_rotation(node->right);
                return left_rotation(node);
            }
        }
        return node;
    }
    TreeNode* insert(TreeNode* node, int num) {
        node = BinarySearchTree::insert(node, num);
        update_treeHeight(node);
        return update_treeBalance(node);
    }
    TreeNode* remove(TreeNode* node, int num) {
        node = BinarySearchTree::remove(node, num);
        update_treeHeight(node);
        return update_treeBalance(node);
    }

  public:
    void insert(int num) { root = insert(root, num); }
    bool search(int num) { return BinarySearchTree::search(root, num); }
    void remove(int num) { root = remove(root, num); }
};

#endif