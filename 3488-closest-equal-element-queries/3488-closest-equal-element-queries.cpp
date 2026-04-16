#include <vector>
#include <unordered_map>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        int n = nums.size();
        
        // Step 1: Group all indices by their corresponding values in nums
        unordered_map<int, vector<int>> pos;
        for (int i = 0; i < n; ++i) {
            pos[nums[i]].push_back(i);
        }

        // Step 2: Precompute the shortest circular distance for each index
        vector<int> res(n, -1);
        
        for (auto& [val, indices] : pos) {
            int k = indices.size();
            
            // If the value appears more than once, calculate the distances
            if (k > 1) {
                for (int i = 0; i < k; ++i) {
                    // Find the adjacent indices in the grouped list, wrapping around for circularity
                    int prevIdx = indices[(i - 1 + k) % k];
                    int nextIdx = indices[(i + 1) % k];

                    int curr = indices[i];
                    
                    // Calculate circular distances to the left and right identical neighbors
                    int d1 = min(abs(curr - prevIdx), n - abs(curr - prevIdx));
                    int d2 = min(abs(curr - nextIdx), n - abs(curr - nextIdx));

                    // Store the minimum of the two distances
                    res[curr] = min(d1, d2);
                }
            }
        }

        // Step 3: Populate the answers for the exact queries provided
        vector<int> ans;
        ans.reserve(queries.size());
        for (int q : queries) {
            ans.push_back(res[q]);
        }
        
        return ans;
    }
};