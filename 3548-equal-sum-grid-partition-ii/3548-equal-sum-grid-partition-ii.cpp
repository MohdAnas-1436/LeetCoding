class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        // 1. Check for valid Horizontal Cuts
        if (checkHorizontal(grid)) return true;
        
        // 2. Check for valid Vertical Cuts (By transposing the grid)
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> transposedGrid(n, vector<int>(m));
        
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                transposedGrid[c][r] = grid[r][c];
            }
        }
        
        return checkHorizontal(transposedGrid);
    }

private:
    bool checkHorizontal(const vector<vector<int>>& g) {
        int m = g.size();
        int n = g[0].size();
        
        // A horizontal cut isn't possible if there is only 1 row
        if (m == 1) return false;
        
        vector<long long> rowSums(m, 0);
        long long totalSum = 0;
        
        for (int r = 0; r < m; ++r) {
            for (int val : g[r]) {
                rowSums[r] += val;
            }
            totalSum += rowSums[r];
        }
        
        // Arrays to track the presence of elements in O(1) time. 
        // Size is 100005 to cover the constraint 1 <= grid[i][j] <= 10^5
        vector<bool> topSet(100005, false);
        vector<int> bottomFreq(100005, 0);
        
        // Initially, all elements belong to the bottom section
        for (int r = 0; r < m; ++r) {
            for (int val : g[r]) {
                bottomFreq[val]++;
            }
        }
        
        long long s1 = 0;
        for (int i = 0; i < m - 1; ++i) {
            // Shift the current row from the bottom section to the top section
            for (int val : g[i]) {
                topSet[val] = true;
                bottomFreq[val]--;
            }
            
            s1 += rowSums[i];
            long long s2 = totalSum - s1;
            
            if (s1 == s2) return true;
            
            // If top section is larger, we must remove 'diff' from the top
            if (s1 > s2) {
                long long diff = s1 - s2;
                if (diff <= 100000) {
                    if (n == 1) {
                        // 1D column: Can only remove the top or bottom ends
                        if (g[0][0] == diff || g[i][0] == diff) return true;
                    } else if (i == 0) {
                        // 1D row: Can only remove the left or right ends
                        if (g[0][0] == diff || g[0][n - 1] == diff) return true;
                    } else {
                        // 2D Grid: Any cell in the top section can be removed
                        if (topSet[diff]) return true;
                    }
                }
            } 
            // If bottom section is larger, we must remove 'diff' from the bottom
            else {
                long long diff = s2 - s1;
                if (diff <= 100000) {
                    if (n == 1) {
                        // 1D column: Can only remove the top or bottom ends
                        if (g[i + 1][0] == diff || g[m - 1][0] == diff) return true;
                    } else if (i == m - 2) {
                        // 1D row: Can only remove the left or right ends
                        if (g[m - 1][0] == diff || g[m - 1][n - 1] == diff) return true;
                    } else {
                        // 2D Grid: Any cell in the bottom section can be removed
                        if (bottomFreq[diff] > 0) return true;
                    }
                }
            }
        }
        return false;
    }
    
};