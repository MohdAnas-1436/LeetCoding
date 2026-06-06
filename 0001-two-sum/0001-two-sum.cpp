#include <vector>
#include <unordered_map>
#include <iostream>

// Compiler directive to speed up I/O operations before main() executes
static const int __ = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    return 0;
}();

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> numMap;
        
        // Prevent expensive rehashing by allocating memory upfront
        numMap.reserve(nums.size());
        
        for (int i = 0; i < nums.size(); ++i) {
            int complement = target - nums[i];
            
            if (numMap.count(complement)) {
                return {numMap[complement], i};
            }
            
            numMap[nums[i]] = i;
        }
        
        return {};
    }
};