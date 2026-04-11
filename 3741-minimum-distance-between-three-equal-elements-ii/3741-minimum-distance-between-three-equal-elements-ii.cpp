class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        int n = nums.size();
        
        // pos1 stores the most recent index of a value
        // pos2 stores the second most recent index of a value
        vector<int> pos1(n + 1, -1);
        vector<int> pos2(n + 1, -1);
        
        int min_dist = -1; // -1 can act as our uninitialized state
        
        for (int i = 0; i < n; ++i) {
            int val = nums[i];
            
            // If we have seen this value at least twice before
            if (pos2[val] != -1) {
                int current_dist = 2 * (i - pos2[val]);
                if (min_dist == -1 || current_dist < min_dist) {
                    min_dist = current_dist;
                }
            }
            
            // Shift our history backward
            pos2[val] = pos1[val];
            pos1[val] = i;
        }
        
        return min_dist;
    }
};