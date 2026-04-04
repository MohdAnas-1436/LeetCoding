#include <string>

class Solution {
public:
    std::string decodeCiphertext(std::string encodedText, int rows) {
        int n = encodedText.length();
        if (n == 0) return "";
        
        int cols = n / rows;
        std::string result;
        
        // Pre-allocate memory to optimize performance and prevent reallocations
        result.reserve(n);
        
        // Traverse each diagonal starting from the top row
        for (int c = 0; c < cols; ++c) {
            for (int r = 0; r < rows; ++r) {
                int curr_col = c + r;
                
                // If the column goes out of bounds, this diagonal is done
                if (curr_col >= cols) {
                    break;
                }
                
                // Map the 2D coordinate (r, curr_col) back to the 1D string index
                int idx = r * cols + curr_col;
                result += encodedText[idx];
            }
        }
        
        // Remove trailing spaces as the original text is guaranteed not to have them
        while (!result.empty() && result.back() == ' ') {
            result.pop_back();
        }
        
        return result;
    }
};