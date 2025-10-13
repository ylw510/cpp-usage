### 1. 迭代过程中删除的陷阱
```
std::map<int, std::string> my_map = {{1, "a"}, {2, "b"}, {3, "c"}};

// 错误：在基于范围的for循环中erase
for (auto& [key, value] : my_map) {
    if (key == 2) {
        my_map.erase(key);  // 迭代器失效！
    }
}

// 错误：在传统迭代器中直接erase后继续使用
for (auto it = my_map.begin(); it != my_map.end(); ++it) {
    if (it->first == 2) {
        my_map.erase(it);  // it失效，但++it仍会执行！
    }
}
```

```
#include <iostream>
#include <unordered_map>
#include <string>
#include <thread>
#include <vector>
#include <chrono>

// 模拟有问题的代码
void problematicMapIteration() {
    std::unordered_map<std::string, int> map;

    // 填充一些测试数据
    for (int i = 0; i < 10; ++i) {
        map["partition_" + std::to_string(i)] = i * 100;
    }

    std::cout << "Map size before iteration: " << map.size() << std::endl;

    // 这是有问题的迭代方式 - 在循环中erase会导致迭代器失效
    for (auto& [key, value] : map) {
        std::cout << "Processing key: " << key << ", value: " << value << std::endl;

        // 模拟条件删除：删除偶数的分区
        if (value % 200 == 0) {
            std::cout << "Deleting key: " << key << std::endl;
            map.erase(key);  // 这里会导致迭代器失效！

            // 在某些情况下可能会立即崩溃，在某些情况下可能会继续运行但行为异常
        }

        // 在erase后继续访问map，可能导致SIGSEGV
        std::cout << "Map size after potential delete: " << map.size() << std::endl;
    }

    std::cout << "Map size after iteration: " << map.size() << std::endl;
}

// 多线程版本，更容易触发崩溃
void problematicMultiThreaded() {
    std::unordered_map<std::string, int> shared_map;

    // 初始化共享map
    for (int i = 0; i < 20; ++i) {
        shared_map["data_" + std::to_string(i)] = i;
    }

    auto worker = [&shared_map](int thread_id) {
        std::cout << "Thread " << thread_id << " starting" << std::endl;

        // 有问题的迭代和删除
        for (auto& [key, value] : shared_map) {
            std::cout << "Thread " << thread_id << " processing: " << key << std::endl;

            // 随机决定是否删除
            if (value % 3 == thread_id) {
                std::cout << "Thread " << thread_id << " deleting: " << key << std::endl;
                shared_map.erase(key);  // 多线程竞争 + 迭代器失效
            }

            // 给其他线程运行的机会
            std::this_thread::sleep_for(std::chrono::microseconds(10));
        }
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back(worker, i);
    }

    for (auto& t : threads) {
        t.join();
    }
}

// 模拟场景
void simulateOriginalBug() {
    struct Buffer {
        std::unordered_map<std::string, int> selected_to_flush_;
        std::unordered_map<std::string, std::string> map_;

        Buffer() {
            // 初始化一些数据
            for (int i = 0; i < 5; ++i) {
                std::string partition_id = "partition_" + std::to_string(i);
                map_[partition_id] = "data_block_" + std::to_string(i);

                // 预先设置一些分区已经在刷新
                if (i % 2 == 0) {
                    selected_to_flush_.insert({partition_id, 1});
                }
            }
        }
    };

    Buffer buffer;

    std::cout << "=== 开始模拟原始bug ===" << std::endl;
    std::cout << "初始状态 - selected_to_flush_.size(): " << buffer.selected_to_flush_.size() << std::endl;
    std::cout << "初始状态 - map_.size(): " << buffer.map_.size() << std::endl;

    // 模拟有问题的flushSomeBuffer逻辑
    int iteration_count = 0;
    for (auto& [partition_id, block_data] : buffer.map_) {
        std::cout << "迭代 " << ++iteration_count << ": 处理分区 " << partition_id << std::endl;
        std::cout << "  selected_to_flush_.size(): " << buffer.selected_to_flush_.size() << std::endl;

        if (buffer.selected_to_flush_.contains(partition_id)) {
            std::cout << "  分区 " << partition_id << " 已经在刷新中，跳过并删除" << std::endl;

            // 导致SIGSEGV的代码！
            buffer.map_.erase(partition_id);

            std::cout << "  删除后 selected_to_flush_.size(): " << buffer.selected_to_flush_.size() << std::endl;
            std::cout << "  删除后 map_.size(): " << buffer.map_.size() << std::endl;

            continue;
        } else {
            std::cout << "  选择分区 " << partition_id << " 进行刷新" << std::endl;
            buffer.selected_to_flush_[partition_id] = 1;
        }

        // 这里可能会因为迭代器失效而崩溃
        std::cout << "  继续处理下一个分区..." << std::endl;
    }

    std::cout << "=== 模拟完成 ===" << std::endl;
}

int main() {
    std::cout << "选择测试模式:" << std::endl;
    std::cout << "1. 单线程迭代器失效测试" << std::endl;
    std::cout << "2. 多线程竞争测试" << std::endl;
    std::cout << "3. 精确模拟原始bug" << std::endl;
    std::cout << "请输入选择 (1-3): ";

    int choice;
    std::cin >> choice;

    try {
        switch (choice) {
            case 1:
                std::cout << "\n运行单线程测试..." << std::endl;
                problematicMapIteration();
                break;
            case 2:
                std::cout << "\n运行多线程测试..." << std::endl;
                problematicMultiThreaded();
                break;
            case 3:
                std::cout << "\n运行原始bug模拟..." << std::endl;
                simulateOriginalBug();
                break;
            default:
                std::cout << "无效选择" << std::endl;
                return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "捕获到异常: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "捕获到未知异常" << std::endl;
        return 1;
    }

    std::cout << "程序正常结束" << std::endl;
    return 0;
}

```
