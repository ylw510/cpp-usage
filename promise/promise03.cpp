#include <iostream>
#include <thread>
#include <mutex>            //std::lock_guard
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void worker_thread() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []{return ready;});
    std::cout << "Worker thread is running." << std::endl;
}

void main_thread() {
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_one();
    std::cout << "Main thread has notified the worker thread." << std::endl;
}

int main() {
    std::thread worker(worker_thread);
    std::thread main(main_thread);
    worker.join();
    main.join();
    return 0;
}
