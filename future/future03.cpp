// future::operator=
#include <iostream>       // std::cout
#include <future>         // std::async, std::future

/* function prototype:
move (1)	
    future& operator= (future&& rhs) noexcept;
copy [deleted] (2)	
    future& operator= (const future&) = delete;    
*/
int get_value() { return 10; }

int main ()
{
  std::future<int> fut;           // default-constructed
  fut = std::async (get_value);   // move-assigned

  std::cout << "value: " << fut.get() << '\n';

  return 0;
}