#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1, 3, 3, 2, 2, 4};

    auto it = std::adjacent_find(v.begin(), v.end());
    if (it != v.end())
        std::cout << "First adjacent duplicate: " << *it << "\n"; // 输出: 3
}
