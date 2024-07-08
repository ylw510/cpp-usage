// unique_lock::try_lock example
#include <iostream>       // std::cout
#include <vector>         // std::vector
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::unique_lock, std::defer_lock

std::mutex mtx;           // mutex for critical section
std::mutex print_mtx;
//因为cout是线程不安全的, 所以使用一个lock_guard来保证输出
void print_star () {
  std::unique_lock<std::mutex> lck(mtx,std::defer_lock);
  
  // print '*' if successfully locked, 'x' otherwise: 
  if (lck.try_lock())
  {
    
    std::lock_guard<std::mutex> print_guard(print_mtx);
    std::cout << "Thread id: " << std::this_thread::get_id() << std::endl << std::flush;
    std::cout << '*' << std::endl << std::flush;
  }
  else
  {
    std::lock_guard<std::mutex> print_guard(print_mtx);    
    std::cout << "Thread id: " << std::this_thread::get_id() << std::endl << std::flush;
    std::cout << 'x' << std::endl << std::flush;
  }
}

int main ()
{
  std::vector<std::thread> threads;
  for (int i=0; i<100; ++i)
    threads.emplace_back(print_star);

  for (auto& x: threads) x.join();

  return 0;
}