// future::get
#include <iostream>       // std::cout, std::ios
#include <future>         // std::async, std::future
#include <exception>      // std::exception
/*
    generic template (1)	
        T get();
    reference specialization (2)	
        R& future<R&>::get();       // when T is a reference type (R&)
    void specialization (3)	
        void future<void>::get();   // when T is void
    当共享状态准备就绪时，返回存储在其中的值（或抛出其异常）。

    如果共享状态尚未准备就绪（即提供者尚未设置其值或异常），该函数将阻塞调用线程，并等待直到共享状态准备就绪。
    一旦共享状态准备就绪，该函数解除阻塞并返回（或抛出异常），释放其共享状态。这使得 future 对象不再有效：每个 future 共享状态，此成员函数最多应调用一次。

    所有可见的副作用在提供者使共享状态准备就绪和该函数返回之间进行同步。

    void specialization (3)	不返回任何值，但仍等待共享状态变为准备就绪，并释放它。    
*/
int get_int() {
  std::cin.exceptions (std::ios::failbit);   // throw on failbit set
  int x;
  std::cin >> x;                             // sets failbit if invalid
  return x;
}

int main ()
{
  std::future<int> fut = std::async (get_int);

  std::cout << "Please, enter an integer value: ";

  try {
    int x = fut.get();
    std::cout << "You entered: " << x << '\n';
    if (fut.valid()) {
        std::cout << "After future::get, the share state is valid" << std::endl;
    } else {
        std::cout << "After future::get, the share state is invalid" << std::endl;
    }
  }
  catch (std::exception&) {
    std::cout << "[exception caught]";
  }

  return 0;
}