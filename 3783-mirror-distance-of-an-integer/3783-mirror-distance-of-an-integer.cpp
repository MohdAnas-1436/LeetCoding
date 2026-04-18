#include <cmath>

class Solution {
public:
    int mirrorDistance(int n) {
        int original = n;
        int rev = 0;
        
        // Reverse the integer
        while (n > 0) {
            rev = rev * 10 + n % 10;
            n /= 10;
        }
        
        // Return the absolute distance
        return std::abs(original - rev);
    }
};