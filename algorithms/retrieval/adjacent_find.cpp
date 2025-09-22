#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Example 1: Basic adjacent duplicate in vector
void example_basic_adjacent() {
    cout << "Example 1: Basic adjacent duplicate in vector" << endl;
    vector<int> v = {1, 3, 3, 2, 2, 4, 5};

    auto it = adjacent_find(v.begin(), v.end());

    if (it != v.end()) {
        cout << "First adjacent duplicate: " << *it 
             << ", position: " << distance(v.begin(), it) << endl;
    } else {
        cout << "No adjacent duplicates found" << endl;
    }
    cout << "-----------------------------" << endl;
}

// Example 2: Custom predicate (difference > 5)
void example_custom_predicate() {
    cout << "Example 2: Custom predicate (difference > 5)" << endl;
    vector<int> v = {1, 3, 10, 12, 15};

    auto it = adjacent_find(v.begin(), v.end(),
                            [](int a, int b){ return b - a > 5; });

    if (it != v.end()) {
        cout << "First pair with difference > 5: " << *it 
             << " and " << *(it + 1) << endl;
    } else {
        cout << "No pair with difference > 5 found" << endl;
    }
    cout << "-----------------------------" << endl;
}

// Example 3: Adjacent duplicates in a string
void example_string() {
    cout << "Example 3: Adjacent duplicates in string" << endl;
    string s = "aabbcdd";

    auto it = adjacent_find(s.begin(), s.end());

    if (it != s.end()) {
        cout << "First adjacent duplicate char: " << *it << endl;
    } else {
        cout << "No adjacent duplicates found" << endl;
    }
    cout << "-----------------------------" << endl;
}

int main() {
    example_basic_adjacent();
    example_custom_predicate();
    example_string();
    return 0;
}
