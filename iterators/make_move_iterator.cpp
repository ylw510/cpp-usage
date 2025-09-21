#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <chrono>

struct BigObject
{
    std::string data;
    BigObject() : data(10'000, 'x') {} // 分配大量内存
    BigObject(const BigObject& other) : data(other.data) { // 拷贝构造
        // 模拟拷贝开销
    }
    BigObject(BigObject&& other) noexcept : data(std::move(other.data)) {} // 移动构造
};

int main() {
    constexpr size_t N = 100000;

    std::vector<BigObject> src(N);
    std::vector<BigObject> dst1;
    std::vector<BigObject> dst2;

    dst1.reserve(N);
    dst2.reserve(N);

    // ----------- 普通拷贝 -----------
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::copy(src.begin(), src.end(), std::back_inserter(dst1)); // 拷贝
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Copy time: "
                  << std::chrono::duration<double>(end - start).count()
                  << " seconds\n";
    }

    // ----------- 移动拷贝 -----------
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::copy(std::make_move_iterator(src.begin()),
                  std::make_move_iterator(src.end()),
                  std::back_inserter(dst2)); // 移动
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Move time: "
                  << std::chrono::duration<double>(end - start).count()
                  << " seconds\n";
    }

    return 0;
}


// g++ -O2 -std=c++17 move_iterator_demo.cpp -o demo
// ./demo

// res
// root@ubantu64:~/test# ./demo
// Copy time: 2.73063 seconds
// Move time: 0.00896041 seconds
