#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string generateString(string str1, string str2) {
        int n = str1.length();
        int m = str2.length();
        int len = n + m - 1;
        
        string word(len, '?');
        
        // Step 1: Lock down all 'T' conditions.
        for (int i = 0; i < n; ++i) {
            if (str1[i] == 'T') {
                for (int j = 0; j < m; ++j) {
                    if (word[i + j] != '?' && word[i + j] != str2[j]) {
                        return ""; // Irreconcilable conflict between fixed characters
                    }
                    word[i + j] = str2[j];
                }
            }
        }
        
        // Step 2: Initialize trackers for 'F' conditions.
        vector<int> mismatches(n, 0);
        vector<int> head(len, -1);
        vector<int> nxt(n, -1);
        
        for (int k = 0; k < n; ++k) {
            if (str1[k] == 'F') {
                int misses = 0;
                int last_q = -1;
                for (int j = 0; j < m; ++j) {
                    if (word[k + j] != '?') {
                        if (word[k + j] != str2[j]) {
                            misses++;
                        }
                    } else {
                        last_q = k + j; // Identifies the furthest right '?' in window k
                    }
                }
                
                mismatches[k] = misses;
                
                // If there are no '?'s and the string perfectly matches, condition fails.
                if (last_q == -1 && misses == 0) {
                    return "";
                }
                
                // Track where the 'F' condition has its final chance to break the pattern.
                if (last_q != -1) {
                    nxt[k] = head[last_q];
                    head[last_q] = k;
                }
            }
        }
        
        // Step 3: Greedily process characters from left to right.
        for (int idx = 0; idx < len; ++idx) {
            if (word[idx] == '?') {
                bool forbidden[26] = {false};
                
                // Analyze restrictions from all 'F' windows that have their LAST '?' right here.
                for (int curr = head[idx]; curr != -1; curr = nxt[curr]) {
                    int k = curr;
                    if (mismatches[k] == 0) {
                        forbidden[str2[idx - k] - 'a'] = true;
                    }
                }
                
                // Elect the smallest character avoiding any constraints
                char pick = 0;
                for (char c = 'a'; c <= 'z'; ++c) {
                    if (!forbidden[c - 'a']) {
                        pick = c;
                        break;
                    }
                }
                
                if (pick == 0) return ""; // Reached a dead end
                
                word[idx] = pick;
                
                // Broadcast our character assignment decision to all overlapping windows.
                int start_k = max(0, idx - m + 1);
                int end_k = min(n - 1, idx);
                
                for (int k = start_k; k <= end_k; ++k) {
                    if (str1[k] == 'F') {
                        if (pick != str2[idx - k]) {
                            mismatches[k]++;
                        }
                    }
                }
            }
        }
        
        return word;
    }
};