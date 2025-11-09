#include <iostream>
#include <vector>
#include <algorithm> // for max and min

using namespace std;

// union
vector<double> fuzzyUnion(const vector<double> &A, const vector<double> &B)
{
    vector<double> result(A.size());
    for (size_t i = 0; i < A.size(); i++)
    {
        result[i] = max(A[i], B[i]);
    }
    return result;
}

//  intersection
vector<double> fuzzyIntersection(const vector<double> &A, const vector<double> &B)
{
    vector<double> result(A.size());
    for (size_t i = 0; i < A.size(); i++)
    {
        result[i] = min(A[i], B[i]);
    }
    return result;
}

// complement
vector<double> fuzzyComplement(const vector<double> &A)
{
    vector<double> result(A.size());
    for (size_t i = 0; i < A.size(); i++)
    {
        result[i] = 1.0 - A[i];
    }
    return result;
}

// Helper to print a fuzzy set
void printSet(const vector<double> &S)
{
    for (double val : S)
    {
        cout << val << " ";
    }
    cout << endl;
}

int main()
{
    // Example fuzzy sets A and B
    vector<double> A = {0.2, 0.5, 0.7, 1.0};
    vector<double> B = {0.4, 0.3, 0.8, 0.6};

    cout << "Set A: ";
    printSet(A);
    cout << "Set B: ";
    printSet(B);

    vector<double> uni = fuzzyUnion(A, B);
    vector<double> inter = fuzzyIntersection(A, B);
    vector<double> compA = fuzzyComplement(A);

    cout << "A union B: ";
    printSet(uni);
    cout << "A intersection B: ";
    printSet(inter);
    cout << "complement A: ";
    printSet(compA);

    return 0;
}
