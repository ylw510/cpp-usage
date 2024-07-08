// unique_lock::try_lock_for example
#include <iostream>       // std::cout
#include <chrono>         // std::chrono::milliseconds
#include <thread>         // std::thread
#include <mutex>          // std::timed_mutex, std::unique_lock, std::defer_lock

std::timed_mutex mtx;

void fireworks () {
  std::unique_lock<std::timed_mutex> lck(mtx,std::defer_lock);
  // waiting to get a lock: each thread prints "-" every 200ms:
  while (!lck.try_lock_until(std::chrono::steady_clock::now() + std::chrono::milliseconds(200))) {
    std::cout << "-";
  }
  // got a lock! - wait for 1s, then this thread prints "*"
  /*sleep_for让其他线程有足够多的机会使try_lock_for 返回false, 如果没有下一行的代码, 这个demo的输出结果就是连续输出10个*
        *
        *
        *
        *
        *
        *
        *
        *
        *
        *
  */
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::cout << "*\n";
}

int main ()
{
  std::thread threads[10];
  // spawn 10 threads:
  for (int i=0; i<10; ++i)
    threads[i] = std::thread(fireworks);

  for (auto& th : threads) th.join();

  return 0;
}