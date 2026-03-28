#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <vector>
#include <string>
#include <iostream>

using namespace std;

// Fast I/O to guarantee 100% execution speed
static const int _ = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();

class Solution {
public:
    string findTheString(vector<vector<int>>& lcp) {
        int n = lcp.size();
        string word(n, ' ');
        char c = 'a';
        
        // Step 1: Greedily construct the lexicographically smallest string
        for (int i = 0; i < n; ++i) {
            if (word[i] == ' ') {
                if (c > 'z') return ""; // We only have 26 lowercase letters available
                word[i] = c;
                for (int j = i + 1; j < n; ++j) {
                    // If lcp > 0, the strings share a prefix, hence the same starting character
                    if (lcp[i][j] > 0) {
                        if (word[j] == ' ') {
                            word[j] = c;
                        }
                    }
                }
                c++;
            }
        }
        
        // Step 2: Validate the constructed string perfectly matches the LCP array
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                int expected = 0;
                
                if (word[i] == word[j]) {
                    expected = 1;
                    // Safely utilize the previously validated diagonal LCP
                    if (i + 1 < n && j + 1 < n) {
                        expected += lcp[i + 1][j + 1];
                    }
                }
                
                // If reality doesn't match the matrix, it's invalid
                if (lcp[i][j] != expected) {
                    return "";
                }
            }
        }
        
        return word;
    }
};