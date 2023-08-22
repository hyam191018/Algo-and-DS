#ifndef TREE_T
#define TREE_T

#include <iostream>
using namespace std;

/**
 * 定義一個BST的node
 * @param num 儲存的數(key)
 * @param height 該節點在整個樹中的高度
 * @param left left node
 * @param right right node
 * @fn updateHeight - 重新計算此node的高度
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
 * 定義一個Binear tree的基本功能
 * @param root 整棵樹的根結點
 * @fn printTree - 輸出整棵樹的結構
 * @fn inorderTraversal- 從小到大印出樹的node value
 * @fn inorderTraversalInv- 從大到小印出樹的node value
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

        printTree(node->right, prefix + (isLeft ? "│   " : "    "), false);

        cout << prefix;
        cout << (isLeft ? "└── " : "┌── ");
        cout << node->num << endl;

        printTree(node->left, prefix + (isLeft ? "    " : "│   "), true);
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
 * 定義一個BST的基本功能
 * @fn insert - 插入一個數到BST
 * @fn search - 在BST找尋一個數
 * @fn remove - 從BST移除一個數
 */
class BinarySearchTree : public TreeBase {
  protected:
    TreeNode* insert(TreeNode* node, int num) {
        TreeNode* new_node;
        if (!node) { // 建立新的node
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
        if (!node) { // 不存在
            return nullptr;
        } else if (num == node->num) { // 刪除
            TreeNode* new_node = nullptr;
            if (node->right) { // 取代
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
 * AVL樹是BST的進階版，在每一次的insert與remove都會自動調整樹的平衡，雖然降低了一些insert與remove的效能
 * 但是能有效提升search的速度
 * @fn insert - 插入一個數到AVLTree(相比BST多了修改樹高跟重新平衡)
 * @fn search - 在AVLTree找尋一個數
 * @fn remove - 從AVTTree移除一個數(相比BST多了修改樹高跟重新平衡)
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
        if (bf > 1) { // 左子樹過重
            if (balance_factor(node->left) >= 1) {
                // LL type
                return right_rotation(node);
            } else {
                // LR type
                node->left = left_rotation(node->left);
                return right_rotation(node);
            }
        } else if (bf < -1) { // 右子樹過重
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