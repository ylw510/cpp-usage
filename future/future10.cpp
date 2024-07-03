#include <future>
#include <iostream>
int main()
{
    try {
        std::promise<int> pro;
        auto fu = pro.get_future();
        auto fu1 = pro.get_future();
    } 
    catch (std::future_error &e) {
        std::cout << "future_err caught: " << e.code().message() << std::endl;
        std::cout << "future_err caught: " << e.what() << std::endl;;
    }
}