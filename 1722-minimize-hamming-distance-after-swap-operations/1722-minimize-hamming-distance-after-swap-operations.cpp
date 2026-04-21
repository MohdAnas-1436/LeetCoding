#include <vector>
#include <numeric>
#include <unordered_map>

using namespace std;

class DSU {
public:
    vector<int> parent;
    DSU(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) parent[root_i] = root_j;
    }
};

class Solution {
public:
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        int n = source.size();
        DSU dsu(n);

        // 1. Union the indices
        for (auto& swap : allowedSwaps) {
            dsu.unite(swap[0], swap[1]);
        }

        // 2. Group source values by their component root
        unordered_map<int, unordered_map<int, int>> components;
        for (int i = 0; i < n; ++i) {
            int root = dsu.find(i);
            components[root][source[i]]++;
        }

        int hammingDistance = 0;

        // 3. Compare with target
        for (int i = 0; i < n; ++i) {
            int root = dsu.find(i);
            int targetVal = target[i];
            
            // Check if the target value exists in the source elements of this component
            if (components[root][targetVal] > 0) {
                components[root][targetVal]--;
            } else {
                // If not found, this position will contribute to Hamming distance
                hammingDistance++;
            }
        }

        return hammingDistance;
    }
};