// unique_lock constructor example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::lock, std::unique_lock
                          // std::adopt_lock, std::defer_lock

/*
    default (1)	
        unique_lock() noexcept;
    locking (2)	
        explicit unique_lock (mutex_type& m);
    try-locking (3)	
        unique_lock (mutex_type& m, try_to_lock_t tag);
    deferred (4)	
        unique_lock (mutex_type& m, defer_lock_t tag) noexcept;
    adopting (5)	
        unique_lock (mutex_type& m, adopt_lock_t tag);
    locking for (6)	
        template <class Rep, class Period>unique_lock (mutex_type& m, const chrono::duration<Rep,Period>& rel_time);
    locking until (7)	
        template <class Clock, class Duration>unique_lock (mutex_type& m, const chrono::time_point<Clock,Duration>& abs_time);
    copy [deleted] (8)	
        unique_lock (const unique_lock&) = delete;
    move (9)	
        unique_lock (unique_lock&& x);
    以上及为构造unique_lock的8种方式, 拷贝构造声明为delete。

(1) default constructor
    对象不拥有mutex
(2) locking initialization
    对象管理mutex, 并且上锁(unique_lock::lock())
(3) try-locking initialization
    对象管理mutex, 并且通过(unique_lock::try_lock())尝试去上锁
(4) deferred initialization
    对象管理mutex，但是不上锁。m应当是一个不被构造的线程上锁的mutex
(5) adopting initialization
    对象管理mutex, 该mutex是一个被构造当前对象的线程上锁的mutex
(6) locking for duration
The object manages m, and attempts to lock it during rel_time by calling m.try_lock_for(rel_time).
(7) locking until time point
The object manages m, and attempts to lock it before abs_time by calling m.try_lock_until(abs_time).
(8) copy construction [deleted]
    拷贝构造被删除
(9) move construction
    对象获取由x管理的mutex，包括其当前的拥有状态。
    x的状态与默认构造一样，即不引用任何互斥对象。

unique_lock通过保留对互斥对象的引用以及拥有对其的锁的信息，来管理互斥对象的状态。
使用(2)和(5)构造的对象始终拥有对互斥对象的锁。
而使用(1)和(4)构造的对象永远不拥有锁。
对于(3)、(6)和(7)，如果锁定尝试成功，它们将拥有锁。(unique_lock对象不能被复制)
*/



std::mutex foo,bar;

void task_a () {
  std::lock (foo,bar);         // simultaneous lock (prevents deadlock)
  std::unique_lock<std::mutex> lck1 (foo,std::adopt_lock);
  std::unique_lock<std::mutex> lck2 (bar,std::adopt_lock);
  std::cout << "task a\n";
  // (unlocked automatically on destruction of lck1 and lck2)
}

void task_b () {
  // foo.lock(); bar.lock(); // replaced by:
  std::unique_lock<std::mutex> lck1, lck2;
  lck1 = std::unique_lock<std::mutex>(bar,std::defer_lock);
  lck2 = std::unique_lock<std::mutex>(foo,std::defer_lock);
  std::lock (lck1,lck2);       // simultaneous lock (prevents deadlock)
  std::cout << "task b\n";
  // (unlocked automatically on destruction of lck1 and lck2)
}


int main ()
{
  std::thread th1 (task_a);
  std::thread th2 (task_b);

  th1.join();
  th2.join();

  return 0;
}