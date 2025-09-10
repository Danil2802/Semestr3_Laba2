#ifndef TREENODE_H
#define TREENODE_H

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

#endif // TREENODE_H
