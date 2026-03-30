class Solution {
public:
    bool checkStrings(string s1, string s2) {
        // counts[0] stores frequencies for even indices
        // counts[1] stores frequencies for odd indices
        int counts[2][26] = {0};
        
        // Traverse both strings simultaneously
        for (int i = 0; i < s1.size(); ++i) {
            counts[i % 2][s1[i] - 'a']++;
            counts[i % 2][s2[i] - 'a']--;
        }
        
        // Check if all frequency counts balance out to zero
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 26; ++j) {
                if (counts[i][j] != 0) {
                    return false;
                }
            }
        }
        
        return true;
    }
};