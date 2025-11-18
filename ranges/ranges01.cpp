#include <ranges>
#include <iostream>
#include <vector>
// 方法1：C++20 新版本写法（使用 std::views）
void modern_ranges_approach() {
    std::cout << "=== C++20 Ranges 写法 ===" << std::endl;

    for (int i : std::views::iota(1)
        | std::views::transform([](int i) { return i * i; })
        | std::views::filter([](int i) { return i % 4 == 0; })
        | std::views::take(5)) {
        std::cout << i << ' ';
    }
    std::cout << '\n' << std::endl;
}

// 方法2：传统写法（使用容器）
void traditional_with_container() {
    std::cout << "=== 传统写法（使用容器）===" << std::endl;

    std::vector<int> result;
    int count = 0;

    for (int i = 1; count < 5; ++i) {
        int squared = i * i;
        if (squared % 4 == 0) {
            result.push_back(squared);
            ++count;
        }
    }

    for (int num : result) {
        std::cout << num << ' ';
    }
    std::cout << '\n' << std::endl;
}

int main() {
    std::cout << "C++20 Ranges vs 传统写法对比\n" << std::endl;

    modern_ranges_approach();      // C++20 新写法
    traditional_with_container();  // 传统写法

    std::cout << "所有方法都产生相同的结果: 取前5个能被4整除的平方数" << std::endl;
    std::cout << "即: 4(2²), 16(4²), 36(6²), 64(8²), 100(10²)" << std::endl;

    return 0;
}