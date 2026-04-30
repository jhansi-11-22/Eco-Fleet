# Eco-Fleet
A hybrid optimization project for fleet management.

Imagine a fleet of delivery drones or vans. Orders arrive every second. 
You cannot run a heavy DP every time a single order comes in, but a purely greedy approach will lead to massive fuel waste over 24 hours.

1. The Greedy Layer (The "First Responder")
Role: Immediate assignment.
When a new delivery request pops up, the Greedy Dispatcher uses a "Nearest Neighbor" or "Minimum Cost Increase" heuristic. 
It assigns the package to the vehicle that can pick it up with the least detour right now.

Why: It keeps the system moving without lag.

2. The DP Layer (The "Constant Re-shuffler")
Role: Global Route Refinement.
As the Greedy layer adds packages to a vehicle’s "to-do list," the vehicle's route becomes messy. 
A background DP Thread continuously runs a Traveling Salesperson Problem (TSP) with Time Windows using DP (Held-Karp variation) for each vehicle.

Why: It takes the "messy" list created by the Greedy dispatcher and rearranges the sequence of stops to find the mathematically perfect shortest path.

## Features
* **Greedy Algorithm**: Handles real-time order arrivals.
* **DP Optimizer**: Refines global routes to find the minimum distance.

# Real-World Use Case:
Uber/Lyft Pool: Greedy decides which rider to pick up immediately so they don't wait for a "Searching..." screen. 
Once 3 riders are in the car, DP calculates the most efficient sequence of drop-offs to minimize total trip time.

## How to Run
1. Ensure `g++` is installed.
2. Compile: `g++ Eco-Fleet.cpp -o Eco-Fleet`
3. Run: `./Eco-Fleet`

