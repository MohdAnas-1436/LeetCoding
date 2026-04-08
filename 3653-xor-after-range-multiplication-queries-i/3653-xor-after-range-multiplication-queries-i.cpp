#include <vector>

using namespace std;

class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        const int MOD = 1e9 + 7;
        
        // Process each query
        for (const auto& query : queries) {
            int l = query[0];
            int r = query[1];
            int k = query[2];
            int v = query[3];
            
            // Multiply elements in the specified range with a step of k
            for (int idx = l; idx <= r; idx += k) {
                // Use 1LL to cast to long long and prevent integer overflow during multiplication
                nums[idx] = (1LL * nums[idx] * v) % MOD;
            }
        }
        
        // Calculate the bitwise XOR of all modified elements
        int finalXor = 0;
        for (int num : nums) {
            finalXor ^= num;
        }
        
        return finalXor;
    }
};