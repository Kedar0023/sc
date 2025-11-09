#include <iostream>
#include <vector>
#include <algorithm> // for std::max and std::min
using namespace std;

int main() {
    const int SIZE = 5;
    
    // Example fuzzy sets A and B
    vector<float> A = {0.2, 0.4, 0.7, 1.0, 0.5};
    vector<float> B = {0.3, 0.6, 0.5, 0.8, 0.4};
    
    vector<float> union_set(SIZE);
    vector<float> intersection_set(SIZE);
    vector<float> complement_A(SIZE);

    // Compute union, intersection, and complement
    for (int i = 0; i < SIZE; ++i) {
        union_set[i] = max(A[i], B[i]);
        intersection_set[i] = min(A[i], B[i]);
        complement_A[i] = 1.0f - A[i];
    }

    // Display results
    cout << "Fuzzy Set A: ";
    for (float val : A) cout << val << " ";
    
    cout << "\nFuzzy Set B: ";
    for (float val : B) cout << val << " ";

    cout << "\n\nUnion (A ∪ B): ";
    for (float val : union_set) cout << val << " ";

    cout << "\nIntersection (A ∩ B): ";
    for (float val : intersection_set) cout << val << " ";

    cout << "\nComplement (¬A): ";
    for (float val : complement_A) cout << val << " ";

    cout << endl;
    return 0;
}
