ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "TreeNode.h"
#include <vector>

using namespace std;

class BinarySearchTree {
private:
    TreeNode* root;
    TreeNode* insert(TreeNode* node, int value);
    void findBranches(TreeNode* node, vector<int>& branches);

public:
    BinarySearchTree();
    void insert(int value);
    vector<int> findBranches();
};

#endif // BINARYSEARCHTREE_H
