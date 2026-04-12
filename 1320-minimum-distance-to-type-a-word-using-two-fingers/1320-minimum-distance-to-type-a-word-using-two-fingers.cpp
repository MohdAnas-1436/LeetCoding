#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumDistance(string word) {
        int n = word.length();
        // dp[27]: stores the min cost to finish the word given the 'other' finger's position.
        // Index 0-25 represent 'A'-'Z'. Index 26 represents an uninitialized finger.
        vector<int> dp(27, 0);
        
        // Helper lambda to calculate Manhattan distance on a 6-column keyboard
        auto dist = [](int a, int b) {
            if (a == 26) return 0; // The first placement of a finger is free
            return abs(a / 6 - b / 6) + abs(a % 6 - b % 6);
        };
        
        // Process the word backwards
        for (int i = n - 2; i >= 0; --i) {
            int prev = word[i] - 'A';
            int curr = word[i + 1] - 'A';
            vector<int> next_dp(27, 0);
            
            // Evaluate for every possible position of the 'other' finger
            for (int other = 0; other <= 26; ++other) {
                // Option 1: Move the finger currently at 'prev' to 'curr'
                int cost1 = dist(prev, curr) + dp[other];
                
                // Option 2: Move the 'other' finger to 'curr'
                int cost2 = dist(other, curr) + dp[prev];
                
                next_dp[other] = min(cost1, cost2);
            }
            // Move to the next step
            dp = next_dp;
        }
        
        // The first character is virtually typed by the first finger (cost 0), 
        // while the second finger remains uninitialized (state 26).
        return dp[26];
    }
};
