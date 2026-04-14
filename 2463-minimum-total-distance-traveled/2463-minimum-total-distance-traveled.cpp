class Solution {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        // Sort both robots and factories by their position to prevent path crossing
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());
        
        int n = robot.size();
        int m = factory.size();
        
        // Memoization table initialized to -1
        vector<vector<long long>> memo(n + 1, vector<long long>(m + 1, -1));
        
        // Define our recursive DP function
        function<long long(int, int)> solve = [&](int i, int j) -> long long {
            // Base cases
            if (i == n) return 0; // All robots repaired
            if (j == m) return 1e18; // Ran out of factories
            
            if (memo[i][j] != -1) return memo[i][j];
            
            // Option 1: Skip this factory entirely
            long long res = solve(i, j + 1);
            long long current_dist = 0;
            
            // Option 2: Try assigning 'k' robots to the current factory
            for (int k = 1; k <= factory[j][1] && i + k - 1 < n; ++k) {
                // Add the distance of moving the current robot to this factory
                // (Cast to long long to prevent integer overflow during subtraction)
                current_dist += abs((long long)robot[i + k - 1] - factory[j][0]);
                
                // Recurse for the remaining robots and next factories
                long long next_dist = solve(i + k, j + 1);
                
                // If it's a valid path, check if it minimizes our total distance
                if (next_dist != 1e18) {
                    res = min(res, current_dist + next_dist);
                }
            }
            
            return memo[i][j] = res;
        };
        
        return solve(0, 0);
    }
};