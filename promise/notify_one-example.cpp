#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <queue>
/*
    这里
*/
std::queue<int> queue;
std::condition_variable cv;
std::mutex mtx;

void producer() {
    for (int i = 0; i < 10; i++) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            queue.push(i);
            std::cout << "Produced: " << i << std::endl << std::flush;
        }
        cv.notify_one(); // 唤醒一个等待的消费者线程
    }
}

void consumer() {
    while (true) {
        int value;
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, []{return !queue.empty();}); // 等待队列非空
            value = queue.front();
            queue.pop();
            std::cout << "Consumed: " << value << std::endl << std::flush;
        }
    }
}

int main() {
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}
