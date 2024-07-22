#include <atomic>
#include <iostream>
#include <thread>

std::atomic<bool> flag(false);
int shared_data = 0;

void threadA() {
    // 模拟一些计算
    shared_data = 42; // 更新共享数据
    flag.store(true, std::memory_order_release); // 设置flag为true，使用release内存顺序
}

void threadB() {
    // 等待flag为true
    while (!flag.load(std::memory_order_acquire)); // 使用acquire内存顺序读取flag
    std::cout << "Shared data: " << shared_data << std::endl; // 读取共享数据
}

int main() {
    std::thread t1(threadA);
    std::thread t2(threadB);
    
    t1.join();
    t2.join();
    
    return 0;
}
