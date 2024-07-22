```
template <class T> struct atomic;
```
原子类型的对象包含特定类型 (T) 的值。

原子对象的主要特点是,从不同线程访问该包含的值不会导致数据竞争(即这种行为是定义良好的,访问会正确排序)。通常对于其他对象,在并发访问同一对象时可能会导致数据竞争,这样的操作就会导致未定义行为。

此外,原子对象还具有通过指定不同的内存顺序来同步访问其他非原子对象的能力。

关于内存顺序的说明(memory order)。
1. memory_order_relaxed
说明：不提供任何同步或顺序保证，仅保证原子操作的原子性。
使用场景：适用于不需要同步其他操作的情况，例如只需要保证某个值的更新是原子的，而不关心它与其他操作的顺序。
2. memory_order_consume
说明：保证对依赖于该原子操作的所有读取操作在此操作之后执行。
使用场景：通常用于生产者-消费者模式，确保消费者在读取某个值后，能看到生产者所做的所有更新。注意，现代编译器对memory_order_consume的支持可能不够完善，建议使用memory_order_acquire作为替代。
3. memory_order_acquire
说明：确保当前线程在此操作之前的所有读取操作在此操作之后可见。
使用场景：通常用于读取操作，比如从一个原子变量读取值，确保在读取之前的所有写入都对当前线程可见。常用于锁的获取。
4. memory_order_release
说明：确保当前线程在此操作之前的所有写入操作在此操作之后可见。
使用场景：通常用于写入操作，比如在释放锁之前更新共享数据，以确保在锁释放后，其他线程能看到这些更新。
5. memory_order_acq_rel
说明：结合了memory_order_acquire和memory_order_release的特性，确保在此操作之前的所有写入对其他线程可见，同时也确保当前线程的后续操作能看到此操作之前的所有读取。
使用场景：通常用于需要同时进行读取和写入的场景，例如在某些自定义的锁实现中。
6. memory_order_seq_cst
说明：提供最强的顺序保证，确保所有线程对所有原子操作的顺序一致。
使用场景：适用于需要严格顺序的场景，虽然性能开销较大，但它是最简单和安全的选择。

示例参考`atomic/memory_order.cpp`

## atomic 相关接口
| 函数名 | 函数介绍 | 访问权限 | 示例demo |
|---------|----------|--------|---------|
| (constructor)   | 构造函数   |public | atomic00.cpp |
| (destructor)   | 析构函数   |public | 
| operator=   | 移动构造函数   |public | atomic01.cpp |
| is_lock_free   | 是否无锁化   |public |
| store   | 修改存储的值   |public | atomic02.cpp |
| load   | 读取值   |public |
| operator T   |访问存储的值   |public |
| exchange   | 访问以及修改值 |public | atomic03.cpp |
| compare_exchange_weak   |    |public | atomic04.cpp
