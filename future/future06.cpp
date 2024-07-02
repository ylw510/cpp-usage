// future::valid
#include <iostream>       // std::cout
#include <future>         // std::async, std::future
#include <utility>        // std::move
/*
    function prototype:
        bool valid() const noexcept;
*/
int get_value() { return 10; }

int main ()
{
  /*
    future可以被以下几个带有有效share state的函数初始化构造, 例如
        async 
        promise::get_future
        packaged_task::get_future.
  */
  std::future<int> foo,bar;
  foo = std::async (get_value);
  //使用移动构造赋值构造好bar后, foo的share state就会失效
  bar = std::move(foo);
  //检查foo的share state是否有效
  if (foo.valid())
    std::cout << "foo's value: " << foo.get() << '\n';
  else
    std::cout << "foo is not valid\n";

  if (bar.valid())
    std::cout << "bar's value: " << bar.get() << '\n';
  else
    std::cout << "bar is not valid\n";

  return 0;
}