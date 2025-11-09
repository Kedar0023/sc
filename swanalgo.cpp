#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    srand(time(0)); // Seed random number generator

    int swarmSize = 5;     // Number of particles
    int dimensions = 3;    // Dimensions of the problem
    double minPos = -10.0; // Minimum position
    double maxPos = 10.0;  // Maximum position

    vector<vector<double>> position(swarmSize, vector<double>(dimensions));
    vector<vector<double>> velocity(swarmSize, vector<double>(dimensions));

    // Initialize positions and velocities
    for (int i = 0; i < swarmSize; i++)
    {
        for (int d = 0; d < dimensions; d++)
        {
            position[i][d] = minPos + (maxPos - minPos) * ((double)rand() / RAND_MAX);
            velocity[i][d] = ((double)rand() / RAND_MAX) * (maxPos - minPos) / 2.0;
        }
    }

    // Print initialized values
    for (int i = 0; i < swarmSize; i++)
    {
        cout << "Particle " << i + 1 << " Position: ";
        for (double p : position[i])
            cout << p << " ";
        cout << " | Velocity: ";
        for (double v : velocity[i])
            cout << v << " ";
        cout << endl;
    }

    return 0;
}
