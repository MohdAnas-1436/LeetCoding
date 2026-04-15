#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    int closestTarget(vector<string>& words, string target, int startIndex) {
        int n = words.size();
        int minDistance = n; // Initialize with a value larger than any possible distance
        
        for (int i = 0; i < n; ++i) {
            if (words[i] == target) {
                // Calculate the direct distance
                int dist = abs(i - startIndex);
                // The shortest distance is the minimum between going direct or wrapping around
                int shortestPath = min(dist, n - dist);
                // Update our global minimum distance
                minDistance = min(minDistance, shortestPath);
            }
        }
        
        // If minDistance hasn't changed, the target was never found
        return minDistance == n ? -1 : minDistance;
    }
};
