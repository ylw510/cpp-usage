#include <iostream>
#include <future>

int main() {
    // 创建两个 promise 对象
    std::promise<int> promise1, promise2;

    // 获取两个 promise 对应的 future 对象
    std::future<int> future1 = promise1.get_future();
    std::future<int> future2 = promise2.get_future();

    // 交换两个 promise 对象
    promise1.swap(promise2);

    // 设置 promise2 的值
    promise2.set_value(42);

    // 获取 promise1 对应的值
    int value = future1.get();
    std::cout << "Value from promise1: " << value << std::endl; // 输出 42

    return 0;
}
