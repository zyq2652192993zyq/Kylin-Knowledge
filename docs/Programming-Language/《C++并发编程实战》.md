> # 《C++并发编程实战》

[TOC]

---

# 第一章 C++并发世界

```c++
#include <iostream>
#include <thread>
using namespace std;

void hello()
{
    cout << "Hello, world!" << endl;
}

int main()
{
    thread t(hello);
    t.join();
}
```

初始线程始于`main()`而新线程始于`hello()`，如果没有`join`，则很可能初始线程不等新线程执行就结束了。

# 第二章 管理线程

