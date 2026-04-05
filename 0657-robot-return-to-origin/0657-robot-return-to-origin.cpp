// This static block executes before the main program starts, 
// speeding up LeetCode's internal input reading process.
static const int fast_io = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    return 0;
}();

class Solution {
public:
    bool judgeCircle(string moves) {
        // Create an array to act as a hash map for ASCII characters.
        // Size 128 safely covers all standard ASCII characters.
        int counts[128] = {0};
        
        // Unconditionally increment the count for whatever character we see.
        // This is branchless and blazingly fast.
        for (char c : moves) {
            counts[c]++;
        }
        
        // Check if opposites cancel out
        return (counts['U'] == counts['D']) && (counts['L'] == counts['R']);
    }
};