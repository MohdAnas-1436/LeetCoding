class Solution {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int i = 0, j = 0;
        int max_dist = 0;
        int n = nums1.size();
        int m = nums2.size();

        while (i < n && j < m) {
            // If the condition is met
            if (nums1[i] <= nums2[j]) {
                // Update the maximum distance found so far
                max_dist = max(max_dist, j - i);
                // Try to increase j to see if we can get a larger distance
                j++;
            } else {
                // nums1[i] is too large, move i forward to get a smaller value
                i++;
                // Optimization: j must be at least i for a valid pair
                if (i > j) {
                    j = i;
                }
            }
        }

        return max_dist;
    }
};