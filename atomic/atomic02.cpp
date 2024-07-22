// atomic::load/store example
#include <iostream>       // std::cout
#include <atomic>         // std::atomic, std::memory_order_relaxed
#include <thread>         // std::thread

std::atomic<int> foo (0);

void set_foo(int x) {
  std::this_thread::sleep_for(std::chrono::seconds(3));
  foo.store(x,std::memory_order_relaxed);     // set value atomically
}

void print_foo(int i) {
  int x;
  auto start = std::chrono::high_resolution_clock::now();
  do {
    x = foo.load(std::memory_order_relaxed);  // get value atomically
  } while (x==0);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;
  std::cout << "Tread " << i << "is waiting for " << duration.count() << " seconds." <<std::endl << std::flush;
  std::cout << "foo: " << x << '\n';
}

int main ()
{
  std::thread first (print_foo,1);
  std::thread second (set_foo,10);
  first.join();
  second.join();
  return 0;
}