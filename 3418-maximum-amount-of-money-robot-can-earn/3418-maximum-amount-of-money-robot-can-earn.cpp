#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximumAmount(vector<vector<int>>& coins) {
        int m = coins.size();
        int n = coins[0].size();
        
        // Use a safe minimum bound to represent impossible states
        const int INF = 1e9;
        
        // dp[i][j][k] stores the max coins at (i, j) having used exactly k neutralizations
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(3, -INF)));
        
        // Base case for the starting cell (0, 0)
        dp[0][0][0] = coins[0][0];
        if (coins[0][0] < 0) {
            // We can neutralize the very first cell if it's a robber
            dp[0][0][1] = 0; 
        }
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // Skip the base case cell since it's already initialized
                if (i == 0 && j == 0) continue; 
                
                for (int k = 0; k < 3; ++k) {
                    int max_prev = -INF;
                    
                    // Option 1: Move from Top or Left without neutralizing the current cell
                    if (i > 0) max_prev = max(max_prev, dp[i-1][j][k]);
                    if (j > 0) max_prev = max(max_prev, dp[i][j-1][k]);
                    
                    if (max_prev != -INF) {
                        dp[i][j][k] = max(dp[i][j][k], max_prev + coins[i][j]);
                    }
                    
                    // Option 2: Move from Top or Left AND neutralize the current cell
                    // This is only valid if it's a robber (coins < 0) and we've used at least 1 ability (k > 0)
                    if (coins[i][j] < 0 && k > 0) {
                        int max_prev_k1 = -INF;
                        if (i > 0) max_prev_k1 = max(max_prev_k1, dp[i-1][j][k-1]);
                        if (j > 0) max_prev_k1 = max(max_prev_k1, dp[i][j-1][k-1]);
                        
                        if (max_prev_k1 != -INF) {
                            dp[i][j][k] = max(dp[i][j][k], max_prev_k1); 
                        }
                    }
                }
            }
        }
        
        // Return the maximum profit at the bottom-right corner across all possible uses of abilities (0, 1, or 2)
        return max({dp[m-1][n-1][0], dp[m-1][n-1][1], dp[m-1][n-1][2]});
    }
};