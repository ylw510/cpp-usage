// constructing atomics
#include <iostream>       // std::cout
#include <atomic>         // std::atomic, std::atomic_flag, ATOMIC_FLAG_INIT
#include <thread>         // std::thread, std::this_thread::yield
#include <vector>         // std::vector

std::atomic<bool> ready (false);
std::atomic_flag winner = ATOMIC_FLAG_INIT;

void count1m (int id) {
  while (!ready) { /*std::this_thread::yield();*/ }      // wait for the ready signal
  for (volatile int i=0; i<1000000; ++i) {}          // go!, count to 1 million
  if (!winner.test_and_set()) { std::cout << "thread #" << id << " won!\n"; }
};

int main ()
{
  std::vector<std::thread> threads;
  std::cout << "spawning 10 threads that count to 1 million...\n";
  //生成10个线程，之后会因为ready没有设置为true, 10个线程会阻塞到 while (!ready) { std::this_thread::yield(); }
  //std::this_thread::yield() 用于让出当前线程的执行时间,让其他线程有机会运行。
  //当主线程设置原子变量为true之后，OS继续线程调度, 最先得到调度的线程开始运行（这里取决于cpu核心数）
  for (int i=1; i<=10; ++i) threads.push_back(std::thread(count1m,i));
  ready = true;
  for (auto& th : threads) th.join();

  return 0;
}