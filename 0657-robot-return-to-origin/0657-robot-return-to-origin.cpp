class Solution {
public:
    bool judgeCircle(string moves) {
        int x = 0;
        int y = 0;
        
        for (char move : moves) {
            switch (move) {
                case 'U': y++; break;
                case 'D': y--; break;
                case 'R': x++; break;
                case 'L': x--; break;
            }
        }
        
        // If both x and y are back to 0, the robot is at the origin
        return x == 0 && y == 0;
    }
};