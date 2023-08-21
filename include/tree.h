#ifndef TREE_T
#define TREE_T

#include <iostream>
using namespace std;

class TreeNode {
  public:
    int num;
    int height; // for self-balance tree
    TreeNode* left;
    TreeNode* right;
    TreeNode(void) : num(0), height(-1), left(nullptr), right(nullptr) {}
    TreeNode(int num) : num(num), height(-1), left(nullptr), right(nullptr) {}
    int get_height(void) { return height; } // for self-balance tree
    void set_height(int h) { height = h; }  // for self-balance tree
    void update_height(TreeNode* node) {    // for self-balance tree
        if (!node) {
            return;
        }
        if (!node->left && !node->right) {
            node->set_height(0);
            return;
        }

        update_height(node->left);
        update_height(node->right);
        int right_h = -1, left_h = -1;
        if (node->left) {
            left_h = (node->left)->get_height();
        }
        if (node->right) {
            right_h = (node->right)->get_height();
        }
        node->set_height(1 + (left_h > right_h ? left_h : right_h));
    }
    void update_height(void) { update_height(this); } // for self-balance tree
};

class TreeBase {
  protected:
    TreeNode* root;
    int node_num;

  public:
    TreeBase(void) : root(nullptr), node_num(0) {}
    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
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
    void inorder_traversal(TreeNode* node) {
        if (!node)
            return;
        inorder_traversal(node->left);
        cout << node->num << " ";
        inorder_traversal(node->right);
    }
    void inorder_traversal(void) {
        inorder_traversal(root);
        cout << endl;
    }
    int size(void) { return node_num; }
};

class BinarySearchTree : public TreeBase {
  public:
    TreeNode* insert(TreeNode* node, int num) {
        TreeNode* new_node;
        if (!node) { // 建立新的node
            new_node = new TreeNode(num);
            return new_node;
        } else if (num == node->num) { // 重複
            return node;
        }

        if (num > node->num) {
            new_node = insert(node->right, num);
            if (!node->right) {
                node->right = new_node;
            }
        } else {
            new_node = insert(node->left, num);
            if (!node->left) {
                node->left = new_node;
            }
        }
        return new_node;
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
    TreeNode* remove(TreeNode* node, int num, bool free = true) {
        if (!node) { // 不存在
            return nullptr;
        } else if (num == node->num) { // 刪除
            TreeNode* new_node = nullptr;
            if (node->right) { // 取代
                if (node->left) {
                    new_node = findMin(node->right);
                    new_node->right = remove(node->right, new_node->num, false);
                    new_node->left = node->left;
                } else {
                    new_node = node->right;
                }
            } else if (node->left) {
                new_node = node->left;
            }

            if (free) {
                delete node;
            }
            return new_node;
        }

        if (num > node->num) {
            node->right = remove(node->right, num, free);
        } else {
            node->left = remove(node->left, num, free);
        }

        return node;
    }
    TreeNode* insert(int num) {
        if (!root) {
            return root = insert(root, num);
        } else {
            return insert(root, num);
        }
    }
    bool search(int num) { return search(root, num); }
    void remove(int num) { root = remove(root, num); }
};

/** -----------------------------------------------------------------*/

class AVLTree : public BinarySearchTree {
  private:
    int balance_factor(TreeNode* node) {
        if (!node) {
            return 0;
        }

        int left_height = (node->left ? (node->left)->get_height() : -1);
        int right_height = (node->right ? (node->right)->get_height() : -1);

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
    void update_treeHeight(TreeNode* node) { node->update_height(); }
    TreeNode* update_treeBalance(TreeNode* node) {}

  public:
    void insert(int num) { TreeNode* n = BinarySearchTree::insert(num); }
    bool search(int num) { return BinarySearchTree::search(num); }
    void remove(int num) { root = BinarySearchTree::remove(root, num); }
};

#endif