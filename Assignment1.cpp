#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

// union
vector<float> fuzzyUnion(const vector<float> &A, const vector<float> &B)
{
    vector<float> result(A.size());
    for (int i = 0; i < A.size(); i++)
    {
        result[i] = max(A[i], B[i]);
    }
    return result;
}

//  intersection
vector<float> fuzzyIntersection(const vector<float> &A, const vector<float> &B)
{
    vector<float> result(A.size());
    for (int i = 0; i < A.size(); i++)
    {
        result[i] = min(A[i], B[i]);
    }
    return result;
}

// complement
vector<float> fuzzyComplement(const vector<float> &A)
{
    vector<float> result(A.size());
    for (int i = 0; i < A.size(); i++)
    {
        result[i] = 1.0 - A[i];
    }
    return result;
}

void printSet(const vector<float> &S)
{
    for (float val : S)
    {
        cout << val << " ";
    }
    cout << endl;
}

int main()
{
    vector<float> A = {0.2, 0.5, 0.7, 1.0, 0.9, 0.3, 0.6};
    vector<float> B = {0.4, 0.3, 0.8, 0.6, 0.5, 0.7, 0.2};

    cout << "Set A: ";
    printSet(A);
    cout << "Set B: ";
    printSet(B);

    vector<float> uni = fuzzyUnion(A, B);
    vector<float> inter = fuzzyIntersection(A, B);
    vector<float> compA = fuzzyComplement(A);

    cout << "A union B: ";
    printSet(uni);
    cout << "A intersection B: ";
    printSet(inter);
    cout << "complement A: ";
    printSet(compA);

    return 0;
}
