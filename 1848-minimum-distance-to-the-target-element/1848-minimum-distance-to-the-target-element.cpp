#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int getMinDistance(vector<int>& nums, int target, int start) {
        int min_dist = INT_MAX;
        
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == target) {
                // Calculate absolute distance and update the minimum
                min_dist = min(min_dist, abs(i - start));
            }
        }
        
        return min_dist;
    }
};