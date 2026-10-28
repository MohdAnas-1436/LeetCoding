/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
//         if (n == 0) return {};

//         return buildTrees(1, n);
//     }

// private:
//     vector<TreeNode*> buildTrees(int start, int end){
//         vector<TreeNode*> result;

//         //Base case: agar start bada ho jaye end se matlab no valid range toh null pointer return hoga
//         if (start > end){
//             result.push_back(nullptr);
//             return result;
//         }

//         for (int i = start; i <= end; ++i){
            
//             vector<TreeNode*> leftTrees = buildTrees(start, i - 1);
//             vector<TreeNode*> rightTrees = buildTrees(i + 1, end);

//             for (TreeNode* leftNode : leftTrees) {
//                 for (TreeNode* rightNode : rightTrees) {
//                     TreeNode* root = new TreeNode(i, leftNode, rightNode);
//                     result.push_back(root);
//                 }
//             }
//         }
//         return result;

    if (n == 0) return {};

    vector<vector<vector<TreeNode*>>> memo(n + 1, vector<vector<TreeNode*>>(n+1));
    return buildTrees(1, n, memo);
    }

private:
    vector<TreeNode*> buildTrees(int start, int end, vector<vector<vector<TreeNode*>>>& memo){
        vector<TreeNode*> result;

        if(start > end){
            result.push_back(nullptr);
            return result;
        }


        if (!memo[start][end].empty()) {
        return memo[start][end];
        }
    

    for (int i = start; i <= end; ++i){
        vector<TreeNode*> leftTrees = buildTrees(start, i - 1, memo);
        vector<TreeNode*> rightTrees = buildTrees(i + 1, end, memo);

        for (TreeNode* leftNode : leftTrees){
            for (TreeNode* rightNode : rightTrees) {
                TreeNode* root = new TreeNode(i, leftNode, rightNode);
                result.push_back(root);
            }
        }
    }

    memo[start][end] = result;

    return result;
    }

    
};