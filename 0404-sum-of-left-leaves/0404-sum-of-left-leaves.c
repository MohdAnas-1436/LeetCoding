/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int sumOfLeftLeaves(struct TreeNode* root) {
    // Base case: If the tree is empty, there are no leaves
    if (root == NULL) {
        return 0;
    }
    
    int sum = 0;
    
    // Check if the left child exists
    if (root->left != NULL) {
        // Is the left child a leaf?
        if (root->left->left == NULL && root->left->right == NULL) {
            sum += root->left->val; // Add the left leaf's value
        } else {
            // Otherwise, recursively search the left subtree
            sum += sumOfLeftLeaves(root->left);
        }
    }
    
    // Recursively search the right subtree for any left leaves deeper down
    if (root->right != NULL) {
        sum += sumOfLeftLeaves(root->right);
    }
    
    return sum;
}