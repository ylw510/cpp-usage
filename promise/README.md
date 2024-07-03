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
