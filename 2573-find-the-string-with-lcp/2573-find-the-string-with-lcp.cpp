#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <vector>
#include <string>

using namespace std;

// Fast I/O
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
        
        // OPTIMIZATION 1: O(N) Early Exit for invalid diagonals
        // The LCP of a suffix with itself must be its full length (n - i)
        for(int i = 0; i < n; ++i) {
            if(lcp[i][i] != n - i) return "";
        }
        
        // Using 0 as unassigned instead of ' ' is slightly faster for char comparisons
        string word(n, 0); 
        char c = 'a';
        
        // Greedily construct the string
        for (int i = 0; i < n; ++i) {
            if (word[i]) continue;
            if (c > 'z') return "";
            
            for (int j = i; j < n; ++j) {
                if (lcp[i][j] > 0) {
                    word[j] = c;
                }
            }
            c++;
        }
        
        // OPTIMIZATION 2 & 3: Forward iteration (Cache friendly) & Upper Triangle only (50% fewer checks)
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                
                // Enforce symmetry dynamically
                if (lcp[i][j] != lcp[j][i]) return "";
                
                int expected = 0;
                if (word[i] == word[j]) {
                    expected = 1 + ((i + 1 < n && j + 1 < n) ? lcp[i + 1][j + 1] : 0);
                }
                
                if (lcp[i][j] != expected) return "";
            }
        }
        
        return word;
    }
};