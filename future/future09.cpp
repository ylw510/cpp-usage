#include <iostream>
#include <future>
#include <chrono>

// 异步任务函数，返回一个整数
int asyncTask() {
    //当时间为2秒时会执行成功, status = std::future_status::ready
    //std::this_thread::sleep_for(std::chrono::seconds(2));
    //当时间大于3秒时会超时, status = std::future_status::timeout
    std::this_thread::sleep_for(std::chrono::seconds(4));
    return 42;
}

int main() {
    // 创建一个异步任务，返回一个 future 对象
    std::future<int> fut = std::async(std::launch::async, asyncTask);

    // 使用 wait_until 等待 future 完成，或者等待超时
    auto timeout = std::chrono::steady_clock::now() + std::chrono::seconds(3);
    std::future_status status = fut.wait_until(timeout);

    if (status == std::future_status::ready) {
        // future 已经完成，可以获取其值
        int result = fut.get();
        std::cout << "Result received: " << result << std::endl;
    } else if (status == std::future_status::timeout) {
        // 等待超时
        std::cout << "Timeout occurred!" << std::endl;
    } else {
        // 其他错误
        std::cout << "Error occurred!" << std::endl;
    }

    return 0;
}
