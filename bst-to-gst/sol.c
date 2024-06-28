#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

int tree_sum = 0;

void traverse(struct TreeNode* root)
{
  if (!root)
    return;
  traverse(root->right);
  tree_sum += root->val;
  root->val = tree_sum;
  traverse(root->left);
}

struct TreeNode* bstToGst(struct TreeNode* root) {
  traverse(root);
  return root;
}
