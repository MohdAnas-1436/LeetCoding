#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minMirrorPairDistance(vector<int>& nums) {
        // Maps a reversed value to the latest index it was seen at
        unordered_map<int, int> last_seen_reverse;
        int min_dist = INT_MAX;
        
        for (int j = 0; j < nums.size(); ++j) {
            // Check if current number matches any previously computed reversed number
            if (last_seen_reverse.count(nums[j])) {
                min_dist = min(min_dist, j - last_seen_reverse[nums[j]]);
            }
            
            // Compute the reverse of the current number
            int x = nums[j];
            int rev = 0;
            while (x > 0) {
                rev = rev * 10 + x % 10;
                x /= 10;
            }
            
            // Store or update the latest index where this reversed value can be formed
            last_seen_reverse[rev] = j;
        }
        
        // If min_dist wasn't updated, no valid pair was found
        return min_dist == INT_MAX ? -1 : min_dist;
    }
};