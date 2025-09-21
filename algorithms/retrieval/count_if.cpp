#include <iostream>
#include <algorithm> // for std::count_if
#include <vector>
#include <string>

// 示例1：使用函数作为谓词
// 定义一个判断函数，判断数字是否为偶数
bool isEven(int n) {
    return n % 2 == 0;
}

// 定义一个判断函数，判断字符串是否以某个字母开头
bool startsWithS(const std::string& s) {
    return !s.empty() && s[0] == 's';
}

// 示例3：使用函数对象（Functor）
// 定义一个函数对象，用于判断数字是否在某个区间内
class IsInRange {
private:
    int min_;
    int max_;
public:
    IsInRange(int min, int max) : min_(min), max_(max) {}
    // 重载函数调用运算符 ()
    bool operator()(int n) const {
        return n >= min_ && n <= max_;
    }
};

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<std::string> words = {"apple", "banana", "starfruit", "cherry", "salmon"};
    
    std::cout << "=== 示例1：使用函数作为谓词 ===\n";
    
    // 统计 vector 中偶数的个数
    int countEven = std::count_if(numbers.begin(), numbers.end(), isEven);
    std::cout << "Number of even numbers: " << countEven << std::endl; // 输出: 5

    // 统计 vector 中以 's' 开头的单词个数
    int countS = std::count_if(words.begin(), words.end(), startsWithS);
    std::cout << "Number of words starting with 's': " << countS << std::endl; // 输出: 2

    std::cout << "\n=== 示例2：使用 Lambda 表达式 ===\n";
    
    // 使用 Lambda 表达式统计大于 5 的数字个数
    int countGreaterThan5 = std::count_if(numbers.begin(), numbers.end(),
                                        [](int n) { return n > 5; } // Lambda 谓词
                                        );
    std::cout << "Numbers greater than 5: " << countGreaterThan5 << std::endl; // 输出: 5

    // 使用 Lambda 表达式捕获变量，统计大于某个可变阈值的数字个数
    int threshold = 7;
    int countAboveThreshold = std::count_if(numbers.begin(), numbers.end(),
                                          [threshold](int n) { return n > threshold; } // 捕获外部变量 threshold
                                          );
    std::cout << "Numbers greater than " << threshold << ": " << countAboveThreshold << std::endl; // 输出: 3

    std::cout << "\n=== 示例3：使用函数对象 ===\n";
    
    // 使用函数对象统计在 [3, 7] 区间内的数字个数
    int countInRange = std::count_if(numbers.begin(), numbers.end(), IsInRange(3, 7));
    std::cout << "Numbers in range [3, 7]: " << countInRange << std::endl; // 输出: 5

    return 0;
}
