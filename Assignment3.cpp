#include <bits/stdc++.h>
using namespace std;

// Objective function: Sphere function f(x) = x^2
double sphereFn(double x)
{
    return x * x;
}

double randomDouble(double min, double max)
{
    return min + (max - min) * ((double)rand() / RAND_MAX);
}

int main()
{
    srand(time(0));

    // User input
    int numWolves, maxIter;
    double lowerBound, upperBound;
    cout << "Enter number of wolves: ";
    cin >> numWolves;
    cout << "Enter number of iterations: ";
    cin >> maxIter;
    cout << "Enter search space lower bound: ";
    cin >> lowerBound;
    cout << "Enter search space upper bound: ";
    cin >> upperBound;

    // Initialize wolf positions
    vector<double> wolves(numWolves);
    for (int i = 0; i < numWolves; i++)
        wolves[i] = randomDouble(lowerBound, upperBound);

    double alpha, beta, delta;  // best three wolves
    alpha = beta = delta = 1e9; // very large number

    double alphaPos = 0, betaPos = 0, deltaPos = 0;

    // Optimization loop
    for (int t = 0; t < maxIter; t++)
    {
        // Update alpha, beta, delta wolves
        for (int i = 0; i < numWolves; i++)
        {
            double fitness = sphereFn(wolves[i]);
            if (fitness < alpha)
            {
                delta = beta;
                deltaPos = betaPos;
                beta = alpha;
                betaPos = alphaPos;
                alpha = fitness;
                alphaPos = wolves[i];
            }
            else if (fitness < beta)
            {
                delta = beta;
                deltaPos = betaPos;
                beta = fitness;
                betaPos = wolves[i];
            }
            else if (fitness < delta)
            {
                delta = fitness;
                deltaPos = wolves[i];
            }
        }

        // Parameter 'a' decreases from 2 to 0
        double a = 2.0 - (2.0 * t / maxIter);

        // Update positions of wolves
        for (int i = 0; i < numWolves; i++)
        {
            double r1 = randomDouble(0, 1);
            double r2 = randomDouble(0, 1);

            double A1 = 2 * a * r1 - a;
            double C1 = 2 * r2;

            double D_alpha = fabs(C1 * alphaPos - wolves[i]);
            double X1 = alphaPos - A1 * D_alpha;

            r1 = randomDouble(0, 1);
            r2 = randomDouble(0, 1);
            double A2 = 2 * a * r1 - a;
            double C2 = 2 * r2;

            double D_beta = fabs(C2 * betaPos - wolves[i]);
            double X2 = betaPos - A2 * D_beta;

            r1 = randomDouble(0, 1);
            r2 = randomDouble(0, 1);
            double A3 = 2 * a * r1 - a;
            double C3 = 2 * r2;

            double D_delta = fabs(C3 * deltaPos - wolves[i]);
            double X3 = deltaPos - A3 * D_delta;

            // New position
            wolves[i] = (X1 + X2 + X3) / 3.0;

            // Bound check
            if (wolves[i] < lowerBound)
                wolves[i] = lowerBound;
            if (wolves[i] > upperBound)
                wolves[i] = upperBound;
        }
    }

    cout << "Best solution found: x = " << alphaPos
         << ", f(x) = " << alpha << endl;

    return 0;
}
