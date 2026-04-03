#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    struct Robot {
        int pos;
        int dist;
        bool operator<(const Robot& other) const {
            return pos < other.pos;
        }
    };

public:
    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
        int n = robots.size();
        vector<Robot> arr(n);
        for(int i = 0; i < n; ++i) {
            arr[i] = {robots[i], distance[i]};
        }
        
        // Sort both robots and walls by position
        sort(arr.begin(), arr.end());
        sort(walls.begin(), walls.end());

        vector<int> V; // Array to hold strictly "interior" walls
        int base_walls = 0;
        
        // Find walls directly on top of robots (unconditionally destroyed)
        // and push the rest into V
        int i = 0, j = 0;
        int m = walls.size();
        while(i < n && j < m) {
            if (arr[i].pos == walls[j]) {
                base_walls++;
                j++; 
            } else if (arr[i].pos < walls[j]) {
                i++;
            } else {
                V.push_back(walls[j]);
                j++;
            }
        }
        while(j < m) {
            V.push_back(walls[j]);
            j++;
        }

        // Helper lambda to count walls in range [L, R] in O(log M) time
        auto count_walls = [&](long long L, long long R) -> int {
            if (L > R) return 0;
            auto it1 = lower_bound(V.begin(), V.end(), L);
            auto it2 = upper_bound(V.begin(), V.end(), R);
            return it2 - it1;
        };

        // Initialize DP for the 0-th robot
        long long dp_L = count_walls((long long)arr[0].pos - arr[0].dist, (long long)arr[0].pos - 1);
        long long dp_R = 0;

        // Iterate through adjacent pairs of robots to calculate DP transitions
        for (int k = 1; k < n; ++k) {
            long long R_prev = arr[k-1].pos;
            long long D_prev = arr[k-1].dist;
            long long R_curr = arr[k].pos;
            long long D_curr = arr[k].dist;

            // Maximum reach bounds within the current interval
            long long P_max = min(R_curr, R_prev + D_prev);
            long long S_min = max(R_prev, R_curr - D_curr);

            long long total_S = count_walls(R_prev + 1, R_curr - 1);

            long long cost_L_L = count_walls(S_min, R_curr - 1);
            long long cost_L_R = 0;
            
            long long cost_R_L = 0;
            if (P_max < S_min) {
                // The ranges don't overlap; subtract the untouched gap from the total.
                long long missed = count_walls(P_max + 1, S_min - 1);
                cost_R_L = total_S - missed;
            } else {
                // The ranges overlap or touch; all available walls in the interval are destroyed.
                cost_R_L = total_S;
            }

            long long cost_R_R = count_walls(R_prev + 1, P_max);

            // DP Transitions
            long long next_L = max(dp_L + cost_L_L, dp_R + cost_R_L);
            long long next_R = max(dp_L + cost_L_R, dp_R + cost_R_R);

            dp_L = next_L;
            dp_R = next_R;
        }

        // Add the tail-end contribution of the final robot firing right
        long long extra_L = 0;
        long long extra_R = count_walls(arr[n-1].pos + 1, (long long)arr[n-1].pos + arr[n-1].dist);

        long long ans = max(dp_L + extra_L, dp_R + extra_R);

        return base_walls + ans;
    }
};