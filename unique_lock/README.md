# unique_lock简介
独占锁是一个在锁定和解锁两种状态下具有唯一所有权的对象，用于管理互斥对象。

在构造时（或通过移动分配给它），该对象获取一个互斥对象，对其锁定和解锁操作负责。

该对象支持两种状态：锁定和未锁定。

这个类保证在销毁时解锁状态（即使未显式调用）。因此，它特别适用于具有自动持续时间的对象，因为它保证互斥对象在抛出异常时能够正确解锁。

需要注意的是，独占锁对象以任何方式都不管理互斥对象的生存期：互斥对象的持续时间至少要延伸到管理它的独占锁被销毁。

# 相关函数接口
| 函数名 | 函数介绍 | 访问权限 | 示例demo |
|---------|----------|--------|----------|
| (constructor)   | 构造函数   |public | unique_lock01.cpp|
| (destructor)   | 析构函数   |public |
| lock   | 给mutex上锁   |public | unique_lock02.cpp |
| try_lock   | 如果没有上锁，进行上锁   |public |
| try_lock_for   | 在时间范围内尝试上锁   |public |
| try_lock_until   | 在某一个时间点之前尝试上锁   |public |
| unlock   | 解锁  |public |
| operator=	   | 移动构造 |public | unique_lock03.cpp |
| swap   | 交换unique_lock |public |
| release   | 释放锁的所有权 |public | unqiue_lock05.cpp |
| owns_lock   | 返回是否拥有一个锁 |public | unqiue_lock05.cpp |
| operator bool   | 返回是否拥有一个锁 |public |
| mutex   | 获取mutex |public | unqiue_lock04.cpp |

`owns_lock`是 `unique_lock::operator bool`的一个别名。这两个函数做的事情是一样的。

通过源码可以发现`unique_lock`在构造的时候会调用`unique_lock::lock`进行上锁
```
      explicit unique_lock(mutex_type& __m)
      : _M_device(&__m), _M_owns(false)
      {
	lock();
	_M_owns = true;
      }
```

`release`会释放返回一个对象拥有的mutex的指针,并释放所有权
```
      release() noexcept
      {
	mutex_type* __ret = _M_device;
	_M_device = 0;
	_M_owns = false;
	return __ret;
      }
```