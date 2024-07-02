/*
std::future::~future

~future();

析构函数销毁future对象
如果对象是有效的（也就是能够访问shared state）,解关联。
如果对象唯一关联shared state, 则shared state 也被销毁。

Exception safety
No-throw guarantee: never throws exceptions.
*/
// future::share
#include <iostream>       // std::cout
#include <future>         // std::async, std::future, std::shared_future

int get_value() { return 10; }

int main ()
{
  std::future<int> fut = std::async (get_value);
  std::shared_future<int> shfut = fut.share();
  std::shared_future<int> shfut1 = fut.share();
  // shared futures can be accessed multiple times:
  std::cout << "value: " << shfut.get() << '\n';
  std::cout << "its double: " << shfut.get()*2 << '\n';
  if (shfut1.valid()) {
    std::cout << "After future::share(), shfut1's share state is valid" << std::endl;
  } else {
    std::cout << "After future::share(), shfut1's share state is invalid" << std::endl;
  }
  if (fut.valid()) {
    std::cout << "After future::share(), fut's share state is valid" << std::endl;
  } else {
    std::cout << "After future::share(), fut's share state is invalid" << std::endl;
  }
  return 0;
}