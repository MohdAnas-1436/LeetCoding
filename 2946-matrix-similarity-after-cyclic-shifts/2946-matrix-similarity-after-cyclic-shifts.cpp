#include <vector>

class Solution {
public:
    bool areSimilar(std::vector<std::vector<int>>& mat, int k) {
        int m = mat.size();
        int n = mat[0].size();
        
        // Since shifting by 'n' brings the array back to its original state,
        // we only need to shift by k modulo n.
        k = k % n; 
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i % 2 == 0) {
                    // Even rows: Left shift by k
                    // The element currently at j will be compared to the element at (j + k) % n
                    if (mat[i][j] != mat[i][(j + k) % n]) {
                        return false;
                    }
                } else {
                    // Odd rows: Right shift by k
                    // The element currently at j will be compared to the element at (j - k + n) % n
                    if (mat[i][j] != mat[i][(j - k + n) % n]) {
                        return false;
                    }
                }
            }
        }
        
        return true;
    }
};