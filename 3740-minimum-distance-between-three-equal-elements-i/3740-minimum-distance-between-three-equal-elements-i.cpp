#pragma GCC optimize("O3", "unroll-loops")
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        // Based on constraints (1 <= nums[i] <= n <= 100)
        // Fixed-size arrays are significantly faster than dynamic vectors
        int pos1[105], pos2[105], pos3[105];
        
        // Initialize history arrays to -1
        for (int i = 0; i <= 100; ++i) {
            pos1[i] = pos2[i] = pos3[i] = -1;
        }
        
        int min_dist = 1e9; // Represents infinity
        
        for (int i = 0; i < nums.size(); ++i) {
            int val = nums[i];
            
            // Shift the historical positions backwards
            pos3[val] = pos2[val];
            pos2[val] = pos1[val];
            pos1[val] = i; // Current is now the most recent
            
            // If we have seen this number at least 3 times
            if (pos3[val] != -1) {
                // Distance formula simplified: 2 * (max_index - min_index)
                // Using bitwise shift << 1 for micro-optimization of * 2
                int dist = (i - pos3[val]) << 1; 
                if (dist < min_dist) {
                    min_dist = dist;
                }
            }
        }
        
        // If min_dist wasn't updated, no valid tuple was found
        return min_dist == 1e9 ? -1 : min_dist;
    }
};