class Solution {
public:
    bool canBeEqual(string s1, string s2) {
        // Check if even indices (0 and 2) can match
        bool evenMatch = (s1[0] == s2[0] && s1[2] == s2[2]) || 
                         (s1[0] == s2[2] && s1[2] == s2[0]);
        
        // Check if odd indices (1 and 3) can match
        bool oddMatch = (s1[1] == s2[1] && s1[3] == s2[3]) || 
                        (s1[1] == s2[3] && s1[3] == s2[1]);
        
        // Both pairs must be able to match
        return evenMatch && oddMatch;
    }
};