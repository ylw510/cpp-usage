future可以帮助在多线程中获取值并进行同步，以避免竞争条件。
它可以由以下函数进行构造。
- async
- promise::get_future
- packaged_task::get_future

`future00.cpp`展示了一个使用future来判断一个数是否为素数的例子
- std::async(is_prime, 444444443)：异步调用 is_prime 函数来检查 444444443 是否为素数。这个函数返回一个 std::future<bool> 对象，代表未来可能产生的 bool 类型的结果。

- fut.wait_for(span) == std::future_status::timeout：在等待异步操作完成时，每隔100毫秒检查一次异步操作的状态。当异步操作完成时，wait_for 将返回 std::future_status::ready。

- fut.get()：获取异步操作的返回值，即调用 is_prime(444444443) 的结果。

最后的输出根据 x 的值（true 或 false）输出相应的信息，表明 444444443 是否为素数。

## future构造函数
### 构造函数原型
```
default (1)	
    future() noexcept;
copy [deleted] (2)	
    future (const future&) = delete;
move (3)	
    future (future&& x) noexcept;
```
```
(1) 默认构造
    构造一个空的 future 对象:该对象没有共享状态（share state）,因此不是有效的,但是可以将其他 future 值赋给它。
(2) 删除了拷贝构造函数
    future对象无法被复制（请参阅shared_future获取可复制的future类）。
(3) 移动构造
    构造的对象获取了 x 的共享状态（如果有的话）。x 不再具有共享状态（不再有效）.
```
### demo编译
```
g++ -pthread future01.cpp -o  future01
```