#include "BinarySearchTree.h"

using namespace std;

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

TreeNode* BinarySearchTree::insert(TreeNode* node, int value) {
    if (!node) {
        return new TreeNode(value);
    }
    if (value < node->value) {
        node->left = insert(node->left, value);
    } else if (value > node->value) {
        node->right = insert(node->right, value);
    }
    return node;
}

void BinarySearchTree::insert(int value) {
    root = insert(root, value);
}

void BinarySearchTree::findBranches(TreeNode* node, vector<int>& branches) {
    if (!node) return;
    if (node->left && node->right) {
        branches.push_back(node->value);
    }
    findBranches(node->left, branches);
    findBranches(node->right, branches);
}

vector<int> BinarySearchTree::findBranches() {
    vector<int> branches;
    findBranches(root, branches);
    return branches;
}
