class Solution {
public:
    int maxDistance(vector<int>& colors) {
        int n = colors.size();
        int maxDist = 0;
        
        // Option 1: Compare the first house with houses from the end moving left
        for (int j = n - 1; j > 0; --j) {
            if (colors[0] != colors[j]) {
                maxDist = max(maxDist, j);
                break; // Found the furthest house from the start
            }
        }
        
        // Option 2: Compare the last house with houses from the start moving right
        for (int i = 0; i < n - 1; ++i) {
            if (colors[n - 1] != colors[i]) {
                maxDist = max(maxDist, (n - 1) - i);
                break; // Found the furthest house from the end
            }
        }
        
        return maxDist;
    }
};