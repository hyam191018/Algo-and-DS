#ifndef TREE_T
#define TREE_T

#include <iostream>
using namespace std;

class TreeNode {
  public:
    int num;
    TreeNode* left;
    TreeNode* right;
    int factor;
    TreeNode(void) : num(0), left(nullptr), right(nullptr), factor(0) {}
    TreeNode(int num) : num(num), left(nullptr), right(nullptr), factor(0) {}
};

class TreeBase {
  protected:
    TreeNode* root;
    int node_num;

  public:
    TreeBase(void) : root(nullptr), node_num(0) {}
    void printTree(TreeNode* node, string prefix = "", bool isLeft = true) {
        if (node == nullptr) {
            return;
        }

        printTree(node->right, prefix + (isLeft ? "¢x   " : "    "), false);

        cout << prefix;
        cout << (isLeft ? "¢|¢w¢w " : "¢z¢w¢w ");
        cout << node->num << endl;

        printTree(node->left, prefix + (isLeft ? "    " : "¢x   "), true);
    }
    void printTree(void) { printTree(root); }
};

class BinarySearchTree : public TreeBase {
  private:
    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

  public:
    void insert(int num) {
        TreeNode* node = new TreeNode(num);
        if (node_num == 0) {
            root = node;
            node_num++;
            return;
        }
        TreeNode* tmp = root;
        while (true) {
            if (node->num == tmp->num) { // ­«½Æ
                return;
            } else if (node->num > tmp->num) {
                if (tmp->right) {
                    tmp = tmp->right;
                } else {
                    tmp->right = node;
                    node_num++;
                    return;
                }
            } else {
                if (tmp->left) {
                    tmp = tmp->left;
                } else {
                    tmp->left = node;
                    node_num++;
                    return;
                }
            }
        }
    }
    bool search(int num) {
        TreeNode* tmp = root;
        while (tmp) {
            if (tmp->num == num) {
                return true;
            } else if (num > tmp->num) {
                tmp = tmp->right;
            } else {
                tmp = tmp->left;
            }
        }
        return false;
    }
    void remove(int num) {
        TreeNode* prev = nullptr;
        TreeNode* tmp = root;
        // finding
        while (tmp) {
            if (tmp->num == num) {
                break;
            } else if (num > tmp->num) {
                prev = tmp;
                tmp = tmp->right;
            } else {
                prev = tmp;
                tmp = tmp->left;
            }
        }
        if (!tmp) { // Not exist
            return;
        }
        if (!tmp->left && !tmp->right) { // is Leaf
            if (prev) {
                if (tmp->num > prev->num) {
                    prev->right = nullptr;
                } else {
                    prev->left = nullptr;
                }
            } else {
                root = nullptr;
            }
            node_num--;
            delete tmp;
        } else if (!tmp->left && tmp->right) {
            if (prev) {
                if (tmp->num > prev->num) {
                    prev->right = tmp->right;
                } else {
                    prev->left = tmp->right;
                }
            } else {
                root = tmp->right;
            }
            node_num--;
            delete tmp;
        } else if (tmp->left && !tmp->right) {
            if (prev) {
                if (tmp->num > prev->num) {
                    prev->right = tmp->left;
                } else {
                    prev->left = tmp->left;
                }
            } else {
                root = tmp->left;
            }
        } else {
            TreeNode* node = findMin(tmp->right);
            node->left = tmp->left;
            if (prev) {
                if (tmp->num > prev->num) {
                    prev->right = node;
                } else {
                    prev->left = node;
                }
            } else {
                root = node;
            }
        }
        node_num--;
        delete tmp;
    }
};

#endif