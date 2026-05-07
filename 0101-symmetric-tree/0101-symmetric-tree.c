/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

// The helper function to compare two nodes
bool isMirror(struct TreeNode* p1, struct TreeNode* p2) {
    // If both nodes are NULL, they are symmetric
    if (p1 == NULL && p2 == NULL) {
        return true;
    }
    
    // If only one is NULL, or if their values don't match, they are not symmetric
    if (p1 == NULL || p2 == NULL || (*p1).val != (*p2).val) {
        return false;
    }
    
    // Recursively check the outer edges and inner edges
    return isMirror((*p1).left, (*p2).right) && isMirror((*p1).right, (*p2).left);
}

// The main function
bool isSymmetric(struct TreeNode* root) {
    if (root == NULL) {
        return true;
    }
    
    // Call the helper function with the left and right children of the root
    return isMirror((*root).left, (*root).right);
}