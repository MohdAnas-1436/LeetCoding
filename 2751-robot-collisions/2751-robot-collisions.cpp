#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int n = positions.size();
        
        // Array to hold original indices
        vector<int> ids(n);
        iota(ids.begin(), ids.end(), 0); // Fill with 0, 1, ..., n-1
        
        // Sort indices based on their starting positions (left to right)
        sort(ids.begin(), ids.end(), [&](int i, int j) {
            return positions[i] < positions[j];
        });
        
        vector<int> stack; // Will store the original indices of surviving robots
        
        for (int id : ids) {
            // If moving Right, push to stack
            if (directions[id] == 'R') {
                stack.push_back(id);
            } else {
                // If moving Left, handle potential collisions
                bool survived = true;
                while (!stack.empty() && directions[stack.back()] == 'R') {
                    int right_id = stack.back();
                    
                    if (healths[right_id] < healths[id]) {
                        // Right-moving robot is destroyed, Left-moving robot survives but loses 1 health
                        healths[id]--;
                        stack.pop_back(); // Remove the right-moving robot
                    } else if (healths[right_id] > healths[id]) {
                        // Left-moving robot is destroyed, Right-moving robot survives but loses 1 health
                        healths[right_id]--;
                        survived = false; 
                        break; // Left robot is gone, stop checking collisions
                    } else {
                        // Both robots have equal health and are destroyed
                        stack.pop_back();
                        survived = false;
                        break; // Both are gone
                    }
                }
                
                // If the left-moving robot survived all its collisions, push it to the stack
                if (survived) {
                    stack.push_back(id);
                }
            }
        }
        
        // Sort the remaining indices to match the originally given order
        sort(stack.begin(), stack.end());
        
        // Collect the final healths
        vector<int> result;
        for (int id : stack) {
            result.push_back(healths[id]);
        }
        
        return result;
    }
};