#include <iostream>
#include <vector>
#include <cmath>
#include <type_traits>

// Primary template: with custom predicate
template<typename Iterator, typename BinaryPredicate>
Iterator my_adjacent_find(Iterator first, Iterator last, BinaryPredicate pred) {
    if (first == last) return last;
    Iterator next_it = first;
    ++next_it;
    while (next_it != last) {
        if (pred(*first, *next_it))
            return first;
        ++first;
        ++next_it;
    }
    return last;
}

// Overload: default predicate (operator==)
template<typename Iterator>
Iterator my_adjacent_find(Iterator first, Iterator last) {
    using ValueType = typename std::iterator_traits<Iterator>::value_type;
    return my_adjacent_find(first, last,
                            [](const ValueType &a, const ValueType &b){ return a == b; });
}

int main() {
    // ------------------------------
    // Example 1: double, difference > 0.5
    // ------------------------------
    std::vector<double> v1 = {1.0, 1.1, 2.0, 2.5, 3.0};
    auto it1 = my_adjacent_find(v1.begin(), v1.end(),
                                [](double a, double b){ return std::abs(b - a) > 0.5; });
    if (it1 != v1.end()) {
        std::cout << "Example 1: Found adjacent pair with diff > 0.5: " 
                  << *it1 << " and " << *(it1+1) << std::endl;
    } else {
        std::cout << "Example 1: No such pair found" << std::endl;
    }

    // ------------------------------
    // Example 2: default behavior (operator==)
    // ------------------------------
    std::vector<int> v2 = {1, 2, 2, 3, 4};
    auto it2 = my_adjacent_find(v2.begin(), v2.end()); // 默认比较 ==
    if (it2 != v2.end()) {
        std::cout << "Example 2: Found adjacent duplicate (default ==): " 
                  << *it2 << " and " << *(it2+1) << std::endl;
    } else {
        std::cout << "Example 2: No adjacent duplicates found" << std::endl;
    }

    // ------------------------------
    // Example 3: string, default behavior
    // ------------------------------
    std::string s = "aabbc";
    auto it3 = my_adjacent_find(s.begin(), s.end());
    if (it3 != s.end()) {
        std::cout << "Example 3: Found adjacent duplicate char (default ==): '" 
                  << *it3 << "' and '" << *(it3+1) << "'" << std::endl;
    } else {
        std::cout << "Example 3: No adjacent duplicates found in string" << std::endl;
    }

    return 0;
}
