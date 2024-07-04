# promise 简介
1. promise 是一个可以存储类型为 T 的值的对象,该值可由 future 对象(可能在另一个线程中)取得,从而提供一个同步点。
2. promise 对象在构建时会关联到一个新的共享状态,可以在该状态上存储类型为 T 的值或从 std::exception 派生的异常。
3. 通过调用 promise 对象的 get_future 成员函数,可以将该共享状态关联到一个 future 对象。这样两个对象就共享同一个共享状态:
   - promise 对象作为异步提供者,应该在某个时候为共享状态设置一个值。
   - future 对象作为异步返回对象,可以获取共享状态的值,如有必要可以等待直到它准备就绪。

# 函数接口
| 函数名 | 函数介绍 | 访问权限 |
|---------|----------|--------|
| (constructor)   | 构造函数   |public |
| (destructor)   | 析构函数   |public |
| operator=   | 移动构造函数   |public |
| get_future   | 获取future   |public |
| set_value   | 设置值   |public |
| set_exception   | 设置异常   |public |
| set_value_at_thread_exit   | 设置线程退出时的值  |public |
| set_exception_at_thread_exit	   | 设置线程退出时的异常 |public |
| swap   | 交换共享状态 |public |

# 重点函数接口说明
在多线程场景做同步处理时，谁作为provider谁的参数为`std::promise &`，谁作为接收者，谁的参数就为`std::future &`，并且这里需要注意的是  
需要引用传参，不然使用promise::set_value时也只是拷贝品set_value。

`std::promise::swap`交换两个promise的shared state  
c++ 4.8.2关于对`promise`的定义，发现成员有`shared_ptr<_State>`和`_Ptr_type`
```
    class promise
    {
      typedef __future_base::_State_base 	_State;
      typedef __future_base::_Result<_Res>	_Res_type;
      typedef __future_base::_Ptr<_Res_type>	_Ptr_type;
      template<typename, typename> friend class _State::_Setter;

      shared_ptr<_State>                        _M_future;
      _Ptr_type                                 _M_storage;
      ...
    }
```
其中`_M_storage`存储传入`promise`的模板的值，关于`_State`的定义为
```
typedef __future_base::_State_base 	_State;

    class _State_base
    {
      typedef _Ptr<_Result_base> _Ptr_type;

      _Ptr_type			_M_result;
      mutex               	_M_mutex;
      condition_variable  	_M_cond;
      atomic_flag         	_M_retrieved;
      once_flag			_M_once;
      ...
    }
```
可见shared state是由`mutex`, `condition_variable`等一系列c++原生线程控制的方式组成的。  
也可以理解为`future`内部由`mutex`, `condition_variable`来实现的。

# 参考
## unique_lock
```
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void worker_function() {
    // 使用 std::unique_lock 获取互斥量的独占访问
    std::unique_lock<std::mutex> lock(mtx);
    
    // 在互斥量锁定期间执行一些操作
    std::cout << "Worker thread is running." << std::endl;
    
    // 离开作用域时,unique_lock 会自动释放互斥量
}

int main() {
    // 创建两个线程
    std::thread worker1(worker_function);
    std::thread worker2(worker_function);
    
    // 等待两个线程执行完毕
    worker1.join();
    worker2.join();
    
    return 0;
}

```
## std::lock_guard
`std::lock_guard` 是 C++ 标准库中提供的一种RAII(Resource Acquisition Is Initialization)风格的锁管理类,主要用于确保在一个作用域内,一个互斥量(mutex)被正确地加锁和解锁。

`lock_guard` 的作用如下:

自动加锁和解锁:

- 在 lock_guard 对象构造时,会自动获取传入的互斥量的锁。
- 在 lock_guard 对象析构时(通常是作用域结束时),会自动释放互斥量的锁。
这样可以确保在任何情况下(包括异常情况)互斥量都会被正确地解锁。
防止忘记解锁:

使用手动加锁和解锁的方式容易出现忘记解锁的情况,从而导致死锁等问题。
lock_guard 通过RAII机制自动处理加锁和解锁,避免了这种问题的发生。
```
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void worker() {
    {
        std::lock_guard<std::mutex> lock(mtx);
        // 临界区代码
        std::cout << "Worker thread is in the critical section." << std::endl;
    }
    // 临界区外
    std::cout << "Worker thread is out of the critical section." << std::endl;
}

int main() {
    std::thread t1(worker);
    std::thread t2(worker);

    t1.join();
    t2.join();

    return 0;
}

```

## std::condition_variable::notify_one()
std::notify_one() 是 C++ 标准库中 std::condition_variable 类的一个成员函数,它的主要作用是:

唤醒一个等待的线程:

当一个线程调用 std::notify_one() 时,它会唤醒在该 std::condition_variable 上等待的一个线程。
被唤醒的线程可以继续执行它在等待前准备的操作。
选择性唤醒:

std::notify_one() 不会唤醒所有等待的线程,而是只唤醒其中的一个。
这种选择性唤醒可以帮助提高系统的性能和效率,因为不需要唤醒所有的等待线程。
与 std::condition_variable 配合使用:

std::notify_one() 通常与 std::condition_variable 一起使用,以实现线程间的同步和通信。
当某个条件满足时,生产者线程可以调用 std::notify_one() 来唤醒一个等待该条件的消费者线程。
```
#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <queue>

std::queue<int> queue;
std::condition_variable cv;
std::mutex mtx;

void producer() {
    for (int i = 0; i < 10; i++) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            queue.push(i);
            std::cout << "Produced: " << i << std::endl;
        }
        cv.notify_one(); // 唤醒一个等待的消费者线程
    }
}

void consumer() {
    while (true) {
        int value;
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, []{return !queue.empty();}); // 等待队列非空
            value = queue.front();
            queue.pop();
            std::cout << "Consumed: " << value << std::endl;
        }
    }
}

int main() {
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}

```