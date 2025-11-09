/*
 * A simple C++ simulation of Ant Colony Optimization (ACO)
 *
 * This program finds the shortest path between a START_NODE and an END_NODE
 * in a hardcoded, weighted graph. It demonstrates the core principles of ACO:
 * 1. Probabilistic path construction based on pheromones and heuristics.
 * 2. Pheromone evaporation (trails fade over time).
 * 3. Pheromone deposition (ants reinforce paths they took, proportional
 * to the quality of the path).
 */

#include <iostream>
#include <vector>
#include <cmath>   // For pow()
#include <cstdlib> // For rand() and RAND_MAX
#include <ctime>   // For time()
#include <iomanip> // For std::setprecision and std::fixed
#include <cfloat>  // For DBL_MAX (a very large number)

// Use standard namespace for simplicity
using namespace std;

// --- Constants ---

// Graph and Problem
const int NUM_NODES = 5; // Number of nodes (cities) in the graph
const int START_NODE = 0;
const int END_NODE = 4;

// ACO Parameters
const int NUM_ANTS = 10;
const int NUM_ITERATIONS = 100;
const double ALPHA = 1.0;            // Pheromone influence
const double BETA = 2.0;             // Heuristic (distance) influence
const double EVAPORATION_RATE = 0.5; // Pheromone evaporation rate (rho)
const double Q = 100.0;              // Pheromone deposit constant

// --- Helper Function ---

// A utility function to print a path (a vector of node indices)
void printPath(const vector<int> &path)
{
    if (path.empty())
    {
        cout << "No path";
        return;
    }
    for (size_t i = 0; i < path.size(); ++i)
    {
        cout << path[i];
        if (i < path.size() - 1)
        {
            cout << " -> ";
        }
    }
}

int main()
{
    // Seed the random number generator
    srand(static_cast<unsigned>(time(0)));

    // --- 1. Initialize Graph and Data Structures ---

    // distances[i][j] = distance from node i to node j
    // A simple, symmetric, fully-connected graph.
    vector<vector<double>> distances = {
        {0, 10, 20, 30, 15},
        {10, 0, 12, 5, 25},
        {20, 12, 0, 18, 8},
        {30, 5, 18, 0, 22},
        {15, 25, 8, 22, 0}};

    // pheromones[i][j] = pheromone level on edge (i, j)
    // Initialize all pheromone levels to a small constant (1.0)
    vector<vector<double>> pheromones(NUM_NODES, vector<double>(NUM_NODES, 1.0));

    // heuristics[i][j] = 1 / distance(i, j)
    // Pre-calculate heuristics to avoid repeated division
    vector<vector<double>> heuristics(NUM_NODES, vector<double>(NUM_NODES));
    for (int i = 0; i < NUM_NODES; ++i)
    {
        for (int j = 0; j < NUM_NODES; ++j)
        {
            if (i != j)
            {
                // Heuristic value: 1.0 / distance. More desirable for shorter paths.
                heuristics[i][j] = 1.0 / distances[i][j];
            }
            else
            {
                heuristics[i][j] = 0; // No heuristic to move to the same node
            }
        }
    }

    // Variables to track the best path found
    vector<int> overallBestPath;
    double overallBestPathLength = DBL_MAX;

    cout << fixed << setprecision(2);
    cout << "Starting ACO Simulation..." << endl;
    cout << "Finding path from " << START_NODE << " to " << END_NODE << endl;
    cout << "Parameters: Ants=" << NUM_ANTS << ", Iterations=" << NUM_ITERATIONS
         << ", Alpha=" << ALPHA << ", Beta=" << BETA << ", Evap=" << EVAPORATION_RATE << endl;
    cout << "----------------------------------------------------" << endl;

    // --- 2. Main ACO Loop ---
    for (int iter = 0; iter < NUM_ITERATIONS; ++iter)
    {

        // Store paths and lengths for all ants in this iteration
        vector<vector<int>> antPaths(NUM_ANTS);
        vector<double> antPathLengths(NUM_ANTS, DBL_MAX);

        // --- 2a. Ants Construct Paths ---
        for (int ant = 0; ant < NUM_ANTS; ++ant)
        {
            int currentNode = START_NODE;
            vector<int> currentPath;
            currentPath.push_back(currentNode);
            double currentPathLength = 0.0;

            // Keep track of visited nodes for this ant
            vector<bool> visited(NUM_NODES, false);
            visited[START_NODE] = true;

            // Build a path until the ant reaches the END_NODE
            while (currentNode != END_NODE)
            {

                // Calculate probabilities for moving to all unvisited neighbors
                vector<double> moveProbs(NUM_NODES, 0.0);
                double probSum = 0.0;

                for (int nextNode = 0; nextNode < NUM_NODES; ++nextNode)
                {
                    if (!visited[nextNode] && distances[currentNode][nextNode] > 0)
                    {
                        // Calculate the "desirability" of this move
                        double pheromone = pow(pheromones[currentNode][nextNode], ALPHA);
                        double heuristic = pow(heuristics[currentNode][nextNode], BETA);
                        moveProbs[nextNode] = pheromone * heuristic;
                        probSum += moveProbs[nextNode];
                    }
                }

                // Handle dead ends (e.g., stuck with no unvisited neighbors)
                if (probSum == 0.0)
                {
                    // Ant fails, mark path length as max (or very high)
                    currentPathLength = DBL_MAX;
                    break;
                }

                // --- Roulette Wheel Selection ---
                // Choose the next node based on the calculated probabilities
                double randVal = (double)rand() / RAND_MAX * probSum;
                int chosenNode = -1;
                for (int nextNode = 0; nextNode < NUM_NODES; ++nextNode)
                {
                    if (moveProbs[nextNode] > 0)
                    {
                        randVal -= moveProbs[nextNode];
                        if (randVal <= 0.0)
                        {
                            chosenNode = nextNode;
                            break;
                        }
                    }
                }

                // This should not happen if probSum > 0, but as a fallback:
                if (chosenNode == -1)
                {
                    for (int nextNode = 0; nextNode < NUM_NODES; ++nextNode)
                    {
                        if (moveProbs[nextNode] > 0)
                        {
                            chosenNode = nextNode;
                            break;
                        }
                    }
                }

                // Move the ant to the chosen node
                currentNode = chosenNode;
                visited[currentNode] = true;
                currentPath.push_back(currentNode);
                // Note: We'd add path length here, but we'll re-calculate it
                // from the final path vector for simplicity.
            }

            // --- Store this ant's path and calculate its length ---
            if (currentNode == END_NODE)
            { // Ant successfully found the end
                currentPathLength = 0.0;
                for (size_t i = 0; i < currentPath.size() - 1; ++i)
                {
                    currentPathLength += distances[currentPath[i]][currentPath[i + 1]];
                }
                antPaths[ant] = currentPath;
                antPathLengths[ant] = currentPathLength;

                // Check if this ant found a new overall best path
                if (currentPathLength < overallBestPathLength)
                {
                    overallBestPathLength = currentPathLength;
                    overallBestPath = currentPath;
                }
            }
            // If ant failed (currentPathLength == DBL_MAX), it's already set
        }

        // --- 2b. Update Pheromones ---

        // 1. Evaporation: Decrease pheromones on all edges
        for (int i = 0; i < NUM_NODES; ++i)
        {
            for (int j = 0; j < NUM_NODES; ++j)
            {
                pheromones[i][j] *= (1.0 - EVAPORATION_RATE);
            }
        }

        // 2. Deposition: Add new pheromones from ants' paths
        for (int ant = 0; ant < NUM_ANTS; ++ant)
        {
            if (antPathLengths[ant] < DBL_MAX)
            { // If ant was successful
                // Amount of pheromone to deposit is inversely related to path length
                double depositAmount = Q / antPathLengths[ant];

                // Deposit pheromones on each edge of the ant's path
                for (size_t i = 0; i < antPaths[ant].size() - 1; ++i)
                {
                    int u = antPaths[ant][i];
                    int v = antPaths[ant][i + 1];
                    // Add to both directions for a symmetric graph
                    pheromones[u][v] += depositAmount;
                    pheromones[v][u] += depositAmount;
                }
            }
        }

        // --- Optional: Print progress ---
        if ((iter + 1) % 10 == 0)
        {
            cout << "Iteration " << (iter + 1) << ": Best Path Length = " << overallBestPathLength << endl;
        }
    }

    // --- 3. Final Result ---
    cout << "----------------------------------------------------" << endl;
    cout << "Simulation finished." << endl;
    if (overallBestPathLength == DBL_MAX)
    {
        cout << "No path found from " << START_NODE << " to " << END_NODE << "." << endl;
    }
    else
    {
        cout << "Overall Best Path Found:" << endl;
        printPath(overallBestPath);
        cout << endl;
        cout << "Path Length: " << overallBestPathLength << endl;
    }

    return 0;
}