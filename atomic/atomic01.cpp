#include <iostream>       // std::cout
#include <atomic>         // std::atomic
#include <thread>         // std::thread, std::this_thread::yield

//注意这种写法是c++17的写法，编译时加-std=c++17
//std::atomic<int> foo = 0;
std::atomic<int> foo{0};

//std::atomic_int foo = {0};
void set_foo(int x) {
  foo.store(x);
}

void print_foo() {
  int x;
  while ((x = foo.load()) == 0) {  // wait while foo=0
    std::this_thread::yield();
  }
  std::cout << "foo: " << x << '\n';
}

int main ()
{
  std::thread first (print_foo);
  std::thread second (set_foo,10);
  first.join();
  second.join();
  return 0;
}
