// /**
//  * Definition for a binary tree node.
//  * struct TreeNode {
//  *     int val;
//  *     struct TreeNode *left;
//  *     struct TreeNode *right;
//  * };
//  */

// int answer;

// int height(struct TreeNode* node) {
//     // code here
//     if (node == NULL) return 0;
    
//     int lh = height(node->left);
//     int rh = height(node->right);
//     int maxHeight = (lh > rh)? lh : rh;
//     return 1 + maxHeight;
// }

// void diameter(struct TreeNode *root){
//     if (root == NULL) return;
//     int lh = height(root->left);
//     int rh = height(root->right);
//     int dia = lh + rh;
//     answer = (answer < dia)? dia : answer;
//     diameter(root->left);
//     diameter(root->right);
// }

// int diameterOfBinaryTree(struct TreeNode* root) {
//     answer = 0;
//     diameter(root);
//     return answer;
// }

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int answer;

// Optimized to calculate height AND update diameter at the same time
int height(struct TreeNode* node) {
    if (node == NULL) return 0;
    
    int lh = height(node->left);
    int rh = height(node->right);
    
    // The diameter passing through this current node
    int current_diameter = lh + rh;
    
    // Update the global maximum diameter if the current one is larger
    if (current_diameter > answer) {
        answer = current_diameter;
    }
    
    // Return the height of the current node
    return 1 + (lh > rh ? lh : rh);
}

int diameterOfBinaryTree(struct TreeNode* root) {
    answer = 0; // Reset for multiple test cases
    height(root); 
    return answer;
}