#include <vector>
#include <string>

using namespace std;

class Robot {
private:
    int width;
    int height;
    int p; // Perimeter length
    int pos;
    bool moved;

public:
    Robot(int width, int height) {
        this->width = width;
        this->height = height;
        // Total perimeter steps to complete one full loop
        this->p = 2 * (width - 1) + 2 * (height - 1);
        this->pos = 0;
        this->moved = false;
    }
    
    void step(int num) {
        pos = (pos + num) % p;
        moved = true; // Flag to handle the (0, 0) orientation edge case
    }
    
    vector<int> getPos() {
        if (pos == 0) {
            return {0, 0};
        }
        
        int T1 = width - 1;
        int T2 = T1 + height - 1;
        int T3 = T2 + width - 1;
        
        if (pos <= T1) {
            // Bottom edge
            return {pos, 0};
        } else if (pos <= T2) {
            // Right edge
            return {width - 1, pos - T1};
        } else if (pos <= T3) {
            // Top edge
            return {width - 1 - (pos - T2), height - 1};
        } else {
            // Left edge
            return {0, height - 1 - (pos - T3)};
        }
    }
    
    string getDir() {
        if (pos == 0) {
            // If it hasn't moved, it faces East. If it looped around to 0, it arrived moving South.
            return moved ? "South" : "East";
        }
        
        int T1 = width - 1;
        int T2 = T1 + height - 1;
        int T3 = T2 + width - 1;
        
        if (pos <= T1) {
            return "East";
        } else if (pos <= T2) {
            return "North";
        } else if (pos <= T3) {
            return "West";
        } else {
            return "South";
        }
    }
};

/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->step(num);
 * vector<int> param_2 = obj->getPos();
 * string param_3 = obj->getDir();
 */