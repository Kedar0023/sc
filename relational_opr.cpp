#include <iostream>
#include <vector>
#include <algorithm> // for max and min
using namespace std;

typedef vector<float> FuzzySet;
typedef vector<vector<float>> FuzzyRelation;

FuzzySet maxMinComposition(const FuzzySet &A, const FuzzyRelation &R)
{
    int m = A.size();         // Size of set A
    int n = R[0].size();      // Number of columns in relation R
    FuzzySet result(n, 0.0f); // Resulting fuzzy set

    for (int j = 0; j < n; ++j)
    {
        float maxVal = 0.0f;
        for (int i = 0; i < m; ++i)
        {
            maxVal = max(maxVal, min(A[i], R[i][j]));
        }
        result[j] = maxVal;
    }
    return result;
}

void printSet(const FuzzySet &set, const string &label)
{
    cout << label << ": ";
    for (float val : set)
        cout << val << " ";
    cout << endl;
}

int main()
{
    // Fuzzy set A with 3 elements
    FuzzySet A = {0.7, 0.4, 1.0};

    // Fuzzy relation R (3x4 matrix)
    FuzzyRelation R = {
        {0.5, 0.3, 0.9, 0.8},
        {0.7, 0.6, 0.4, 0.2},
        {1.0, 0.9, 0.5, 0.3}};

    // Compute max-min composition A o R
    FuzzySet result = maxMinComposition(A, R);

    // Display results
    printSet(A, "Fuzzy Set A");
    cout << "Fuzzy Relation R:" << endl;
    for (const auto &row : R)
    {
        for (float val : row)
            cout << val << " ";
        cout << endl;
    }

    printSet(result, "Result of A o R (Max-Min)");

    return 0;
}
