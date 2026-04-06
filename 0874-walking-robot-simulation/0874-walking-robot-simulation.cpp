#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        // Direction vectors mapping to North, East, South, West
        int dx[] = {0, 1, 0, -1};
        int dy[] = {1, 0, -1, 0};
        int dir = 0; // Starts facing North (index 0)
        
        // Use an unordered_set of long long for O(1) obstacle lookups
        unordered_set<long long> obsSet;
        for (const auto& obs : obstacles) {
            // Offset by 30,000 to ensure positive numbers, then pack into 64-bit int
            long long x = obs[0] + 30000;
            long long y = obs[1] + 30000;
            obsSet.insert((x << 16) | y);
        }
        
        int x = 0, y = 0;
        int maxDistSq = 0;
        
        for (int cmd : commands) {
            if (cmd == -2) { 
                // Turn Left (equivalent to +3 modulo 4 to avoid negative values)
                dir = (dir + 3) % 4;
            } else if (cmd == -1) { 
                // Turn Right
                dir = (dir + 1) % 4;
            } else { 
                // Move Forward step by step
                for (int step = 0; step < cmd; ++step) {
                    int nx = x + dx[dir];
                    int ny = y + dy[dir];
                    
                    long long nx_shifted = nx + 30000;
                    long long ny_shifted = ny + 30000;
                    
                    // Check if the next step hits an obstacle
                    if (obsSet.count((nx_shifted << 16) | ny_shifted)) {
                        break; // Stop moving forward for this command
                    }
                    
                    // Move the robot
                    x = nx;
                    y = ny;
                    
                    // Calculate current distance squared and update max
                    maxDistSq = max(maxDistSq, x * x + y * y);
                }
            }
        }
        
        return maxDistSq;
    }
};