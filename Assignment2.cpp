#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<float>> fuzzyUnion(const vector<vector<float>> &R, const vector<vector<float>> &S)
{
    vector<vector<float>> result(R.size(), vector<float>(R[0].size()));

    for (int i = 0; i < R.size(); i++)
    {
        for (int j = 0; j < R[0].size(); j++)
        {
            result[i][j] = max(R[i][j], S[i][j]);
        }
    }
    return result;
}

vector<vector<float>> fuzzyIntersection(const vector<vector<float>> &R, const vector<vector<float>> &S)
{
    vector<vector<float>> result(R.size(), vector<float>(R[0].size()));

    for (int i = 0; i < R.size(); i++)
    {
        for (int j = 0; j < R[0].size(); j++)
        {
            result[i][j] = min(R[i][j], S[i][j]);
        }
    }
    return result;
}

vector<vector<float>> fuzzyComplement(const vector<vector<float>> &R)
{
    vector<vector<float>> result(R.size(), vector<float>(R[0].size()));

    for (int i = 0; i < R.size(); i++)
    {
        for (int j = 0; j < R[0].size(); j++)
        {
            result[i][j] = 1.0 - R[i][j];
        }
    }
    return result;
}

void printRelation(const vector<vector<float>> &R)
{
    for (const auto &row : R)
    {
        cout << "{ ";
        for (float val : row)
        {
            cout << val << " ";
        }
        cout << "}" << endl;
    }
}

int main()
{
    vector<vector<float>> R = {
        {0.2, 0.7, 1.0},
        {0.5, 0.3, 0.9}};

    vector<vector<float>> S = {
        {0.6, 0.4, 0.8},
        {0.1, 0.9, 0.5}};

    cout << "Relation R:" << endl;
    printRelation(R);
    cout << "Relation S:" << endl;
    printRelation(S);

    auto unionRel = fuzzyUnion(R, S);
    auto interRel = fuzzyIntersection(R, S);
    auto compR = fuzzyComplement(R);

    cout << "\nUnion (R ∪ S):" << endl;
    printRelation(unionRel);

    cout << "\nIntersection (R ∩ S):" << endl;
    printRelation(interRel);

    cout << "\nComplement (R'):" << endl;
    printRelation(compR);

    // Define another relation T (3x2 matrix) for composition
    vector<vector<float>> T = {
        {0.3, 0.6},
        {0.8, 0.2},
        {0.4, 0.9}};

    cout << "\nRelation T (for composition):" << endl;
    printRelation(T);

    return 0; // program ends successfully
}
