/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool symmetric(struct TreeNode* p1, struct TreeNode* p2) {
    if (p1 == NULL && p2 == NULL) {
        return true;
    }

    if (p1 == NULL || p2 == NULL || p1->val != p2->val) {
        return false;
    }
    
    return symmetric(p1->left, p2->right) && symmetric(p1->right, p2->left);
}

bool isSymmetric(struct TreeNode* root) {
    if (root == NULL) {
        return true;
    }
    
    // Call the helper function with the left and right children of the root
    return symmetric(root->left, root->right);
}