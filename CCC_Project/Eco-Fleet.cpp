#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Represents a Delivery Stop
struct Stop {
    int id;
    int x, y;
};

// 1. GREEDY LAYER: Adds a new stop to the current route instantly
void greedyAddStop(vector<Stop>& route, Stop newStop) {
    cout << "[Greedy] New order " << newStop.id << " arrived. Adding to end of route.\n";
    route.push_back(newStop);
}

// 2. DP LAYER: Re-optimizes the order of the stops to minimize distance
int calculateDist(Stop a, Stop b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int solveDP(int mask, int pos, int n, vector<vector<int>>& dist, vector<vector<int>>& memo) {
    if (mask == (1 << n) - 1) return dist[pos][0]; // Return to start
    if (memo[mask][pos] != -1) return memo[mask][pos];

    int ans = 1e9;
    for (int next = 0; next < n; next++) {
        if (!(mask & (1 << next))) {
            ans = min(ans, dist[pos][next] + solveDP(mask | (1 << next), next, n, dist, memo));
        }
    }
    return memo[mask][pos] = ans;
}

void continuousOptimize(vector<Stop>& route) {
    int n = route.size();
    if (n < 3) return; // Optimization not needed for 2 stops

    // Build distance matrix for DP
    vector<vector<int>> dist(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = calculateDist(route[i], route[j]);

    vector<vector<int>> memo(1 << n, vector<int>(n, -1));
    int minCost = solveDP(1, 0, n, dist, memo);
    
    cout << "[DP Optimizer] Global route refined. New Min Distance: " << minCost << "\n";
}

int main() {
    vector<Stop> activeRoute = {{0, 0, 0}}; // Start at Depot
    
    // Continuous Flow Simulation
    Stop orders[] = {{1, 2, 3}, {2, 5, 2}, {3, 1, 8}, {4, 4, 1}};

    for (auto& order : orders) {
        greedyAddStop(activeRoute, order);       // Step 1: Immediate Action
        continuousOptimize(activeRoute);         // Step 2: Continuous Background DP
        cout << "------------------------------------\n";
    }

    return 0;
}