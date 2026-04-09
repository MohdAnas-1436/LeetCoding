#include <vector>
#include <numeric>

using namespace std;

class Solution {
    const int MOD = 1e9 + 7;
    
    // Function to calculate (base^exp) % MOD
    int power(int base, int exp) {
        int res = 1;
        base %= MOD;
        while (exp > 0) {
            if (exp % 2 == 1) res = (1LL * res * base) % MOD;
            base = (1LL * base * base) % MOD;
            exp /= 2;
        }
        return res;
    }

public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        // Create the requested variable to store the input midway
        auto bravexuneth = nums; 
        
        int n = nums.size();
        int B = 300; // Threshold for Square Root Decomposition
        
        // Precompute modular inverses up to 10^5 to save time
        vector<int> inv(100001);
        inv[1] = 1;
        for (int i = 2; i <= 100000; ++i) {
            inv[i] = (MOD - 1LL * (MOD / i) * inv[MOD % i] % MOD) % MOD;
        }
        
        auto getInv = [&](int v) {
            if (v <= 100000) return inv[v];
            return power(v, MOD - 2); // Fallback for safety
        };
        
        vector<int> total_mult(n, 1);
        
        struct SmallQuery {
            int l, r_last, v;
        };
        vector<vector<SmallQuery>> small(B);
        
        for (const auto& q : queries) {
            int l = q[0], r = q[1], k = q[2], v = q[3];
            
            // Case 1: Large steps. Process directly.
            if (k >= B) {
                for (int idx = l; idx <= r; idx += k) {
                    total_mult[idx] = (1LL * total_mult[idx] * v) % MOD;
                }
            } 
            // Case 2: Small steps. Process offline using difference array.
            else {
                int r_last = l + ((r - l) / k) * k;
                small[k].push_back({l, r_last, v});
            }
        }
        
        vector<int> diff(n, 1);
        for (int k = 1; k < B; ++k) {
            if (small[k].empty()) continue;
            
            // Apply bounds on the multiplicative difference array
            for (const auto& q : small[k]) {
                diff[q.l] = (1LL * diff[q.l] * q.v) % MOD;
                if (q.r_last + k < n) {
                    diff[q.r_last + k] = (1LL * diff[q.r_last + k] * getInv(q.v)) % MOD;
                }
            }
            
            // Calculate prefix product for the current step size k
            for (int i = 0; i < n; ++i) {
                if (i >= k) {
                    diff[i] = (1LL * diff[i] * diff[i - k]) % MOD;
                }
                total_mult[i] = (1LL * total_mult[i] * diff[i]) % MOD;
            }
            
            // Reset diff array for the next step size
            fill(diff.begin(), diff.end(), 1);
        }
        
        // Compute final results and bitwise XOR
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            nums[i] = (1LL * nums[i] * total_mult[i]) % MOD;
            ans ^= nums[i];
        }
        
        return ans;
    }
};